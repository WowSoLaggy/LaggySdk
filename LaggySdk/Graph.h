#pragma once


namespace Sdk
{
  // A generic graph with data attached to every node and every edge.
  //
  // Nodes and edges are referred to by integer handles (NodeId / EdgeId) that index
  // into internal vectors. Removal is supported: removeNode / removeEdge mark an
  // element dead and unwire it, so every query (getEdgesAt, getNodeIds, getEdgeIds,
  // degree counting) immediately stops reporting it. Handles stay stable across
  // removals — a removed slot is left tombstoned rather than erased — so ids the
  // caller is holding remain valid. cleanup() physically erases the dead slots and
  // remaps every surviving handle; it therefore invalidates ALL outstanding ids and
  // must only be called when the caller holds none.
  //
  // Edges are stored directed (from -> to) but every query that asks "what touches
  // this node" treats them as undirected, because an edge connects both its ends.
  //
  // NodeData / EdgeData are arbitrary payloads (e.g. a crossroad descriptor on a
  // node, a Road on an edge). std::* and the CONTRACT_* macros come in via the PCH,
  // matching the other SDK headers; this header deliberately includes nothing.

  using NodeId = size_t;
  using EdgeId = size_t;


  template <class NodeData, class EdgeData>
  class Graph
  {
  public:
    // Appends a node carrying i_data; returns its handle.
    NodeId addNode(NodeData i_data)
    {
      const NodeId id = d_nodes.size();
      d_nodes.push_back(Node{ std::move(i_data), {}, true });
      return id;
    }

    // Appends an edge i_from -> i_to carrying i_data; returns its handle. The edge
    // is registered on both endpoints so getEdgesAt sees it from either side.
    EdgeId addEdge(const NodeId i_from, const NodeId i_to, EdgeData i_data)
    {
      CONTRACT_EXPECT(i_from < d_nodes.size());
      CONTRACT_EXPECT(i_to < d_nodes.size());

      const EdgeId id = d_edges.size();
      d_edges.push_back(Edge{ i_from, i_to, std::move(i_data), true });
      d_nodes[i_from].edges.push_back(id);
      if (i_to != i_from)
        d_nodes[i_to].edges.push_back(id);
      return id;
    }

    // Marks the edge dead and unwires it from both endpoints' adjacency lists, so its
    // degree contribution and getEdgesAt visibility vanish at once. Idempotent.
    void removeEdge(const EdgeId i_edge)
    {
      CONTRACT_EXPECT(i_edge < d_edges.size());
      Edge& edge = d_edges[i_edge];
      if (!edge.alive)
        return;

      edge.alive = false;
      unregisterEdgeAt(edge.from, i_edge);
      if (edge.to != edge.from)
        unregisterEdgeAt(edge.to, i_edge);
    }

    // Marks the node dead, first removing every still-alive edge incident to it so the
    // graph stays consistent. Idempotent.
    void removeNode(const NodeId i_node)
    {
      CONTRACT_EXPECT(i_node < d_nodes.size());
      Node& node = d_nodes[i_node];
      if (!node.alive)
        return;

      // removeEdge mutates node.edges, so work off a copy.
      const std::vector<EdgeId> incident = node.edges;
      for (const EdgeId e : incident)
        removeEdge(e);

      node.alive = false;
    }

    bool hasNode(const NodeId i_node) const
    {
      return i_node < d_nodes.size() && d_nodes[i_node].alive;
    }
    bool hasEdge(const EdgeId i_edge) const
    {
      return i_edge < d_edges.size() && d_edges[i_edge].alive;
    }

    size_t getNodesCount() const { return d_nodes.size(); }
    size_t getEdgesCount() const { return d_edges.size(); }

    // Handles of all alive nodes / edges, for range-for iteration without a manual
    // dead-skip at the call site.
    std::vector<NodeId> getNodeIds() const
    {
      std::vector<NodeId> ids;
      for (NodeId n = 0; n < d_nodes.size(); ++n)
        if (d_nodes[n].alive)
          ids.push_back(n);
      return ids;
    }
    std::vector<EdgeId> getEdgeIds() const
    {
      std::vector<EdgeId> ids;
      for (EdgeId e = 0; e < d_edges.size(); ++e)
        if (d_edges[e].alive)
          ids.push_back(e);
      return ids;
    }

    NodeData& getNodeData(const NodeId i_node)
    {
      CONTRACT_EXPECT(i_node < d_nodes.size());
      return d_nodes[i_node].data;
    }
    const NodeData& getNodeData(const NodeId i_node) const
    {
      CONTRACT_EXPECT(i_node < d_nodes.size());
      return d_nodes[i_node].data;
    }

    EdgeData& getEdgeData(const EdgeId i_edge)
    {
      CONTRACT_EXPECT(i_edge < d_edges.size());
      return d_edges[i_edge].data;
    }
    const EdgeData& getEdgeData(const EdgeId i_edge) const
    {
      CONTRACT_EXPECT(i_edge < d_edges.size());
      return d_edges[i_edge].data;
    }

    NodeId getEdgeFrom(const EdgeId i_edge) const
    {
      CONTRACT_EXPECT(i_edge < d_edges.size());
      return d_edges[i_edge].from;
    }
    NodeId getEdgeTo(const EdgeId i_edge) const
    {
      CONTRACT_EXPECT(i_edge < d_edges.size());
      return d_edges[i_edge].to;
    }

    // Handles of the alive edges touching i_node, from either end. Its size is the
    // node's (alive) degree.
    const std::vector<EdgeId>& getEdgesAt(const NodeId i_node) const
    {
      CONTRACT_EXPECT(i_node < d_nodes.size());
      return d_nodes[i_node].edges;
    }

    // Physically erases all dead nodes and edges, compacts both vectors and remaps the
    // surviving handles to their new indices. INVALIDATES every NodeId / EdgeId the
    // caller may be holding — only call when none are outstanding.
    void cleanup()
    {
      // old index -> new index, or npos for a dropped element.
      constexpr size_t npos = static_cast<size_t>(-1);
      std::vector<NodeId> nodeRemap(d_nodes.size(), npos);
      std::vector<EdgeId> edgeRemap(d_edges.size(), npos);

      std::vector<Node> newNodes;
      for (size_t n = 0; n < d_nodes.size(); ++n)
      {
        if (!d_nodes[n].alive)
          continue;
        nodeRemap[n] = newNodes.size();
        newNodes.push_back(std::move(d_nodes[n]));
      }

      std::vector<Edge> newEdges;
      for (size_t e = 0; e < d_edges.size(); ++e)
      {
        if (!d_edges[e].alive)
          continue;
        edgeRemap[e] = newEdges.size();
        Edge edge = std::move(d_edges[e]);
        edge.from = nodeRemap[edge.from];
        edge.to = nodeRemap[edge.to];
        CONTRACT_ASSERT(edge.from != npos && edge.to != npos);
        newEdges.push_back(std::move(edge));
      }

      // Remap each surviving node's adjacency list (all its entries are alive edges).
      for (Node& node : newNodes)
        for (EdgeId& e : node.edges)
        {
          e = edgeRemap[e];
          CONTRACT_ASSERT(e != npos);
        }

      d_nodes = std::move(newNodes);
      d_edges = std::move(newEdges);
    }

  private:
    struct Node
    {
      NodeData data;
      std::vector<EdgeId> edges; // every alive edge with this node as an endpoint
      bool alive = true;
    };

    struct Edge
    {
      NodeId from = 0;
      NodeId to = 0;
      EdgeData data;
      bool alive = true;
    };

    // Drops i_edge from i_node's adjacency list (called when the edge is removed).
    void unregisterEdgeAt(const NodeId i_node, const EdgeId i_edge)
    {
      std::vector<EdgeId>& edges = d_nodes[i_node].edges;
      edges.erase(std::remove(edges.begin(), edges.end(), i_edge), edges.end());
    }

    std::vector<Node> d_nodes;
    std::vector<Edge> d_edges;
  };

} // ns Sdk

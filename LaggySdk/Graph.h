#pragma once


namespace Sdk
{
  // A generic graph with data attached to every node and every edge.
  //
  // Nodes and edges are referred to by stable integer handles (NodeId / EdgeId)
  // rather than pointers: a handle is the element's index in an append-only vector,
  // so it stays valid for the life of the graph (the graph never removes elements).
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
      d_nodes.push_back(Node{ std::move(i_data), {} });
      return id;
    }

    // Appends an edge i_from -> i_to carrying i_data; returns its handle. The edge
    // is registered on both endpoints so getEdgesAt sees it from either side.
    EdgeId addEdge(const NodeId i_from, const NodeId i_to, EdgeData i_data)
    {
      CONTRACT_EXPECT(i_from < d_nodes.size());
      CONTRACT_EXPECT(i_to < d_nodes.size());

      const EdgeId id = d_edges.size();
      d_edges.push_back(Edge{ i_from, i_to, std::move(i_data) });
      d_nodes[i_from].edges.push_back(id);
      if (i_to != i_from)
        d_nodes[i_to].edges.push_back(id);
      return id;
    }

    size_t getNodesCount() const { return d_nodes.size(); }
    size_t getEdgesCount() const { return d_edges.size(); }

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

    // Handles of all edges touching i_node, from either end. Its size is the node's
    // degree.
    const std::vector<EdgeId>& getEdgesAt(const NodeId i_node) const
    {
      CONTRACT_EXPECT(i_node < d_nodes.size());
      return d_nodes[i_node].edges;
    }

  private:
    struct Node
    {
      NodeData data;
      std::vector<EdgeId> edges; // every edge with this node as an endpoint
    };

    struct Edge
    {
      NodeId from = 0;
      NodeId to = 0;
      EdgeData data;
    };

    std::vector<Node> d_nodes;
    std::vector<Edge> d_edges;
  };

} // ns Sdk

#include "stdafx.h"
#include "TreeNode.h"

#include "Contracts.h"


namespace Sdk
{
  TreeNode* TreeNode::getParent() { return d_parent; }
  const TreeNode* TreeNode::getParent() const { return d_parent; }

  std::vector<std::shared_ptr<TreeNode>>& TreeNode::getChildren() { return d_children; }
  const std::vector<std::shared_ptr<TreeNode>>& TreeNode::getChildren() const { return d_children; }


  void TreeNode::setParent(TreeNode* i_parent)
  {
    if (i_parent == d_parent)
      return;

    if (d_parent)
      d_parent->removeChild(*this);
    if (i_parent)
      i_parent->addChild(shared_from_this());

    d_parent = i_parent;
  }


  void TreeNode::sendToFront()
  {
    if (auto* parent = getParent())
    {
      auto& children = parent->getChildren();
      if (children.size() > 1)
      {
        auto it = std::find_if(children.rbegin(), children.rend(), [&](const auto ptr) {
          return ptr.get() == this;
          });
        CONTRACT_EXPECT(it != children.rend());

        if (it != children.rbegin())
          std::iter_swap(it, children.rbegin());
      }
    }
  }

  void TreeNode::sendToBack()
  {
    if (auto* parent = getParent())
    {
      auto& children = parent->getChildren();
      if (children.size() > 1)
      {
        auto it = std::find_if(children.begin(), children.end(), [&](const auto ptr) {
          return ptr.get() == this;
          });
        CONTRACT_EXPECT(it != children.end());

        if (it != children.begin())
          std::iter_swap(it, children.begin());
      }
    }
  }


  void TreeNode::addChild(std::shared_ptr<TreeNode> i_child)
  {
    d_children.push_back(i_child);
    i_child->d_parent = this;
  }

  void TreeNode::removeChild(TreeNode& i_child)
  {
    i_child.d_parent = nullptr;

    const auto it = std::find_if(d_children.cbegin(), d_children.cend(),
                                 [&](const auto i_childPtr) { return i_childPtr.get() == &i_child; });
    if (it != d_children.cend())
      d_children.erase(it);
  }

  void TreeNode::removeChildren()
  {
    while (!d_children.empty())
      removeChild(*d_children.front());
  }

} // ns Sdk

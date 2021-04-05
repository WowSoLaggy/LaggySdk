#include "stdafx.h"
#include "TreeNode.h"


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
      removeChild(*this);
    if (i_parent)
      addChild(shared_from_this());
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

} // ns Sdk

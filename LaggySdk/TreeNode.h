#pragma once


namespace Sdk
{
  class TreeNode : public std::enable_shared_from_this<TreeNode>
  {
  public:
    virtual ~TreeNode() = default;

    [[nodiscard]] TreeNode* getParent();
    [[nodiscard]] const TreeNode* getParent() const;

    [[nodiscard]] std::vector<std::shared_ptr<TreeNode>>& getChildren();
    [[nodiscard]] const std::vector<std::shared_ptr<TreeNode>>& getChildren() const;

    void setParent(TreeNode* i_parent);

    void addChild(std::shared_ptr<TreeNode> i_child);
    void removeChild(TreeNode& i_child);

  private:
    TreeNode* d_parent = nullptr;
    std::vector<std::shared_ptr<TreeNode>> d_children;
  };

} // ns Sdk

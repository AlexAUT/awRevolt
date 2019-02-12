#pragma once

#include <aw/gui/string.hpp>
#include <aw/gui/widgets/widget.hpp>

#include <aw/gui/widgets/linearContainer.hpp>

namespace aw::gui
{
class TreeView : public Widget
{
public:
  AW_GUI_CLASS_NAME(TreeView)
  using SPtr = std::shared_ptr<TreeView>;

public:
  class TreeNode
  {
  public:
    using SPtr = std::shared_ptr<TreeNode>;

  public:
    TreeNode(Widget::SPtr widget, bool collapsed = true);

    void addChild(TreeNode::SPtr child);
    bool removeChild(TreeNode* child);
    void removeAllChilds();

    void collapsed(bool newValue);
    bool collapsed() const { return mCollapsed; }

    const Widget::SPtr& getWidget() const { return mWidget; }
    const std::vector<TreeNode::SPtr>& getChildren() const { return mChildren; }

    void setWidgetContainer(LinearContainer* ptr) { mWidgetContainer = ptr; }

  private:
    LinearContainer* mWidgetContainer{nullptr};
    Widget::SPtr mWidget{nullptr};
    bool mCollapsed{true};
    std::vector<TreeNode::SPtr> mChildren;
  };

public:
  TreeView(const GUI& gui);
  virtual ~TreeView() = default;

  TreeNode* addNodeToRoot(TreeNode::SPtr newNode);
  void removeAllNodes();

  virtual void update(float delta) override;
  virtual bool processEvent(const WindowEvent& event) override;
  virtual void render() override;

  virtual void updateLayout(Vec2 parentPos) override;
  virtual Vec2 getMinimalSize() const override;
  virtual void invalidateLayout() override;

private:
  void updateTreeNode(TreeNode* node, int level, bool parentVisible);

private:
  LinearContainer::SPtr mChildContainer;

  TreeNode mRootNode;
};
} // namespace aw::gui

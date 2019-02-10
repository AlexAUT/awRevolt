#include <aw/gui/widgets/treeView.hpp>

#include <aw/gui/utils/eventConvert.hpp>
#include <aw/gui/widgets/label.hpp>
#include <aw/utils/log.hpp>

namespace aw::gui
{
TreeView::TreeView(const GUI& gui) :
    Widget(gui),
    mChildContainer(std::make_shared<LinearContainer>(gui, Orientation::Vertical)),
    mRootNode(nullptr, false)
{
  mRootNode.setWidgetContainer(mChildContainer.get());
}

TreeView::TreeNode::TreeNode(Widget::SPtr widget, bool collapsed) : mWidget(std::move(widget)), mCollapsed(collapsed) {}

void TreeView::TreeNode::addChild(TreeNode::SPtr child)
{
  mChildren.push_back(child);
  child->setWidgetContainer(mWidgetContainer);
  if (mWidget)
    mWidget->invalidateLayout();
  if (mWidgetContainer)
    mWidgetContainer->invalidateLayout();
}

bool TreeView::TreeNode::removeChild(TreeNode* child)
{
  auto toDelete = std::find_if(mChildren.begin(), mChildren.end(), [=](const auto& e) { return e.get() == child; });
  if (toDelete != mChildren.end())
  {
    // Also remove his childs!
    (*toDelete)->removeAllChilds();

    if (mWidgetContainer)
      mWidgetContainer->removeChild((*toDelete)->getWidget().get());
    mChildren.erase(toDelete);
    return true;
  }
  return false;
}

void TreeView::TreeNode::removeAllChilds()
{
  if (mWidgetContainer)
  {
    for (auto& it : mChildren)
    {
      it->removeAllChilds();
      mWidgetContainer->removeChild(it->getWidget().get());
    }
    mWidgetContainer->invalidateLayout();
  }
  mChildren.clear();
}

void TreeView::TreeNode::collapsed(bool newValue)
{
  mCollapsed = newValue;
  if (mWidget)
    mWidget->invalidateLayout();
}

TreeView::TreeNode* TreeView::addNodeToRoot(TreeNode::SPtr newNode)
{
  if (mChildContainer->getParent().expired())
    mChildContainer->setParent(getSharedPtr());

  mRootNode.addChild(newNode);
  invalidateLayout();
  return nullptr;
}

void TreeView::update(float delta)
{
  mChildContainer->update(delta);
}

bool TreeView::processEvent(const WindowEvent& event)
{
  return mChildContainer->processEvent(convertToLocalEvent(event, *this));
}

void TreeView::render()
{
  mChildContainer->render();
}

void TreeView::updateLayout(Vec2 parentPos)
{
  if (!isLayoutDirty())
    return;

  // Check if nodes changed
  updateTreeNode(&mRootNode, 0, true);

  mChildContainer->setRelativePosition(getPadding().leftTop());
  mChildContainer->setSize(getContentSize());
  mChildContainer->updateLayout(parentPos + getRelativePosition());

  Widget::updateLayout(parentPos);
}

Vec2 TreeView::getMinimalSize() const
{
  return mChildContainer->getMinimalSize();
}

void TreeView::invalidateLayout()
{
  Widget::invalidateLayout();
  mChildContainer->invalidateLayout();
}

void TreeView::updateTreeNode(TreeNode* node, int level, bool parentVisible)
{
  if (!node)
    return;

  auto& widget = node->getWidget();
  auto collapsed = node->collapsed();

  // Iterate reverse over childs, so we insert the first child directly after the parent element
  for (auto rIt = node->getChildren().rbegin(); rIt != node->getChildren().rend(); ++rIt)
  {
    auto& child = *rIt;

    auto& childWidget = child->getWidget();
    if (childWidget)
    {
      bool hasParent = !childWidget->getParent().expired();
      if (hasParent && (collapsed || !parentVisible))
      {
        auto removed = mChildContainer->removeChild(childWidget.get());
        assert(removed);
      }
      else if (parentVisible && !collapsed && !hasParent)
        mChildContainer->addChildAfter(widget.get(), childWidget, 0.f);
    }
    updateTreeNode(child.get(), level + 1, parentVisible && !collapsed);
  }
}

} // namespace aw::gui

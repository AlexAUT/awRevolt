#include <aw/runtime/scene/sceneNode.hpp>

namespace aw
{
SceneNode::SceneNode() : mLocalTransform(std::bind(&SceneNode::invalidGlobalTransformCache, this))
{
}

SceneNode::~SceneNode()
{
  for (auto& child : mChildren)
    delete child;
}

void SceneNode::setName(const std::string& name)
{
  mName = name;
}

const std::string& SceneNode::getName() const
{
  return mName;
}

void SceneNode::setParent(SceneNode* parent)
{
  mParent = parent;
  if (mParent)
    mParent->mChildren.push_back(this);
  invalidGlobalTransformCache();
}

void SceneNode::addChild(SceneNode* child)
{
  assert(child);
  child->setParent(this);
}

SceneNode* SceneNode::getParent() const
{
  return mParent;
}

const std::vector<SceneNode*>& SceneNode::getChildren() const
{
  return mChildren;
}

SceneNode* SceneNode::findNodeByName(const std::string& name) const
{
  for (auto& child : mChildren)
  {
    if (child->getName() == name)
      return child;
  }
  return nullptr;
}
void SceneNode::traverseChilds(const std::function<void(SceneNode*)>& callback)
{
  callback(this);
  for (auto& child : mChildren)
    child->traverseChilds(callback);
}

void SceneNode::traverseChilds(const std::function<void(const SceneNode*)>& callback) const
{
  callback(this);
  for (const auto* child : mChildren)
    child->traverseChilds(callback);
}

Transform& SceneNode::localTransform()
{
  return mLocalTransform;
}

const Transform& SceneNode::localTransform() const
{
  return mLocalTransform;
}

const Mat4& SceneNode::getGlobalTransform() const
{
  if (!mParent)
    return mLocalTransform.getTransform();

  // Check if local transform has changed
  if (mIsGlobalTransformDirty)
  {
    mGlobalTransform = mParent->getGlobalTransform() * mLocalTransform.getTransform();
    mIsGlobalTransformDirty = false;
  }
  return mGlobalTransform;
}

void SceneNode::invalidGlobalTransformCache()
{
  if (!mIsGlobalTransformDirty)
  {
    mIsGlobalTransformDirty = true;
    for (auto child : mChildren)
      child->invalidGlobalTransformCache();
  }
}

} // namespace aw

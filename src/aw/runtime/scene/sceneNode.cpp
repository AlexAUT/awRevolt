#include <aw/runtime/scene/sceneNode.hpp>

namespace aw
{
SceneNode::SceneNode() : mLocalTransform(std::bind(&SceneNode::invalidGlobalTransformCache, this))
{
}

SceneNode::~SceneNode()
{
}

void SceneNode::setParent(SceneNode* parent)
{
  assert(parent);
  mParent = parent;
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
  auto currentVersion = mLocalTransform.getVersionNumber();
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

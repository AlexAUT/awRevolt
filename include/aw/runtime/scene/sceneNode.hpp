#pragma once

#include <aw/graphics/3d/transform.hpp>

#include <aw/utils/math/matrix.hpp>
#include <aw/utils/types.hpp>

#include <vector>

namespace aw
{
class SceneNode
{
public:
  SceneNode();
  virtual ~SceneNode();
  // Tree
  void setParent(SceneNode* parent);
  void addChild(SceneNode* child);

  SceneNode* getParent() const;
  const std::vector<SceneNode*>& getChildren() const;

  // Transform
  Transform& localTransform();
  const Transform& localTransform() const;
  const Mat4& getGlobalTransform() const;

private:
  void invalidGlobalTransformCache();

private:
  SceneNode* mParent{nullptr};
  std::vector<SceneNode*> mChildren;

  Transform mLocalTransform;

  mutable Mat4 mGlobalTransform;
  mutable bool mIsGlobalTransformDirty{true};
};

} // namespace aw

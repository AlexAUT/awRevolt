#pragma once

#include <aw/utils/math/vector.hpp>

#include <memory>

namespace sf
{
class Event;
}
namespace aw
{
using WindowEvent = sf::Event;
}

namespace aw::gui
{
class NanovgRenderer;

class Widget : public std::enable_shared_from_this<Widget>
{
public:
  using SPtr = std::shared_ptr<Widget>;
  using CSPtr = std::shared_ptr<const Widget>;

public:
  virtual ~Widget() = default;

  SPtr getSharedPtr() { return shared_from_this(); }
  CSPtr getConstSharedPtr() { return shared_from_this(); }

  virtual void update(float delta) {}
  virtual void render(NanovgRenderer& renderer, Vec2 parentPos)
  {
    setGlobalPosition(getRelativePosition() + parentPos);
  }

  virtual bool processEvent(const WindowEvent& event) { return false; }

  void setParent(SPtr parent) { mParent = parent; }
  void setPreferedSize(Vec2 size) { mPreferedSize = size; }

  SPtr getParent() const { return mParent; }
  Vec2 getSize() const { return mSize; }
  Vec2 getPreferedSize() const { return mPreferedSize; }
  Vec2 getRelativePosition() const { return mRelativePosition; }
  Vec2 getGlobalPosition() const { return mGlobalPosition; }

public:
  // These should be called by the layouter, calling them may result in wrong rendering
  void setSize(Vec2 size) { mSize = size; }
  void setRelativePosition(Vec2 pos) { mRelativePosition = pos; }
  void setGlobalPosition(Vec2 pos) { mGlobalPosition = pos; }

private:
private:
  SPtr mParent{nullptr};

  Vec2 mPreferedSize{0.f};
  Vec2 mSize{0.f};

  Vec2 mRelativePosition{0.f};
  Vec2 mGlobalPosition{0.f};
};
} // namespace aw::gui

#include <aw/gui/widgets/floatingContainer.hpp>

namespace aw::gui
{
void FloatingContainer::updateLayout()
{
  if (!isLayoutDirty() || mBoundsPolicy == BoundsPolicy::NoChecks)
    return;

  // Update child elemens
  Container::updateLayout();

  // Do bounds checks
  for (auto& child : mChildren)
  {
    auto relPos = child->getRelativePosition();
    auto size = child->getSize();
    if (mBoundsPolicy == BoundsPolicy::Strict)
    {
      // Do size checks for strict policy
      size.x = std::min(size.x, getSize().x);
      size.y = std::min(size.y, getSize().y);
      // Do not let the element escpe the container
      relPos.x = std::max(std::min(relPos.x, getSize().x - size.x), 0.f);
      relPos.y = std::max(std::min(relPos.y, getSize().y - size.y), 0.f);
    }
    else
    {
      // Always keep tol pixels inside the window (the user can access it)
      const float tol = 5.f;
      relPos.x = std::max(std::min(relPos.x, getSize().x - tol), tol - size.x);
      relPos.y = std::max(std::min(relPos.y, getSize().y - tol), tol - size.y);
    }

    bool updateLayoutOfChild = false;
    if (child->getRelativePosition() != relPos)
    {
      child->setRelativePosition(relPos);
      updateLayoutOfChild = true;
    }
    if (child->getSize() != size)
    {
      child->setSize(size);
      updateLayoutOfChild = true;
    }
    if (updateLayoutOfChild)
      child->updateLayout();
  }

  Widget::updateLayout();
}

void FloatingContainer::setBoundsPolicy(BoundsPolicy policy)
{
  mBoundsPolicy = policy;
  invalidateLayout();
}

} // namespace aw::gui

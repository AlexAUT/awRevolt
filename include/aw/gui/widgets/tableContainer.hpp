#pragma once

#include <aw/gui/widgets/container.hpp>

namespace aw::gui
{
class TableContainer : public Container
{
public:
  TableContainer(const GUI& gui);

  void addElement(unsigned collumn, unsigned row);

private:
private:
};
} // namespace aw::gui

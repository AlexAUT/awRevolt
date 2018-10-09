#pragma once

namespace aw::gui
{
enum class AlignmentHorizontal
{
  Left,
  Center,
  Right
};
using AlignmentH = AlignmentHorizontal;

enum class AlignmentVertical
{
  Top,
  Middle,
  Bottom
};
using AlignmentV = AlignmentVertical;

struct Alignment
{
  AlignmentH horizontal{AlignmentH::Left};
  AlignmentV vertical{AlignmentV::Middle};
};

} // namespace aw::gui

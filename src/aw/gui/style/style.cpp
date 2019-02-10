#include <aw/gui/style/style.hpp>

namespace aw::gui
{
#define ADD_IF(propName)                                                                                               \
  if (styleTemplate.propName)                                                                                          \
  {                                                                                                                    \
    propName = *styleTemplate.propName;                                                                                \
  }

Style& Style::operator+=(const StyleTemplate& styleTemplate)
{
  // Body
  ADD_IF(backgroundColor);
  // Text
  ADD_IF(fontName)
  ADD_IF(fontSize)
  ADD_IF(fontColor)

  return *this;
}
} // namespace aw::gui

#pragma once

#include <aw/gui/widgets/checkedTextBox.hpp>
#include <aw/utils/regex.hpp>
#include <aw/utils/stringConverter.hpp>
#include <aw/utils/stringFormat.hpp>

#include <sstream>

namespace aw::gui
{
template <typename Type, typename ConvOp = aw::StringConverter<Type>>
class TypedTextBox;

// Typedefs
using TextBoxInt = TypedTextBox<int>;
using TextBoxFloat = TypedTextBox<float>;
using TextBoxDouble = TypedTextBox<double>;

template <typename Type, typename ConvOp>
class TypedTextBox final : public CheckedTextBox
{
public:
  TypedTextBox(const aw::gui::GUI& gui, Type value) : CheckedTextBox(gui, stringFormat::toPrettyString(value)) {}
  ~TypedTextBox() = default;

  Type getValue() const { return mValue; }

protected:
  void updateValue() override
  {
    auto match = regex::checkStringForType<Type>(getText());
    changeValidState(match);
    if (match)
    {
      mValue = ConvOp()(getText());
    }
  }

private:
  Type mValue;
};

} // namespace aw::gui

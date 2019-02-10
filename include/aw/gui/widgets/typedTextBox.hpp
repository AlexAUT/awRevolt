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
  using SPtr = std::shared_ptr<TypedTextBox<Type, ConvOp>>;

public:
  TypedTextBox(const aw::gui::GUI& gui, Type value) : CheckedTextBox(gui, stringFormat::toPrettyString(value)) {}
  ~TypedTextBox() = default;

  void setValue(const Type& value) { setText(stringFormat::toPrettyString(value)); }
  Type getValue() const { return mValue; }

protected:
  virtual void updateValue(aw::Vec2 parentPos) override
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

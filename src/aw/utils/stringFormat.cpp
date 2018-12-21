#include <aw/utils/stringFormat.hpp>

namespace aw::stringFormat
{
template <>
void makeNumberStringPretty<float>(std::string& number)
{
  auto signPos = number.find_first_of('-');
  std::size_t searchFrom = signPos == std::string::npos ? 0 : signPos + 1;
  // First remove prefix 0's
  auto firstNonZero = number.find_first_not_of('0', searchFrom);
  if (firstNonZero == std::string::npos)
    number.erase(searchFrom + 1);
  else if (number[firstNonZero] == '.')
    number.erase(searchFrom, firstNonZero - 1);
  else
    number.erase(searchFrom, firstNonZero - searchFrom);
  // Secondly remove suffix 0's
  auto commaPos = number.find_last_of('.');
  if (commaPos != std::string::npos)
  {
    auto lastDigitAfterComma = number.find_last_not_of('0');
    if (lastDigitAfterComma == commaPos)
      number.erase(commaPos + 2);
    else
      number.erase(lastDigitAfterComma + 1);
  }
}

template <>
void makeNumberStringPretty<int>(std::string& number)
{
  // Just remove zeros in front of number
  auto signPos = number.find_first_of('-');
  std::size_t searchFrom = signPos == std::string::npos ? 0 : signPos + 1;
  auto firstNonZero = number.find_first_not_of('0', searchFrom);
  if (firstNonZero != std::string::npos)
    number.erase(searchFrom, firstNonZero - searchFrom);
  else
  {
    // Remove 0's if there are multiple
    number.erase(searchFrom + 1);
  }
}

template <>
std::string toPrettyString(const float& value)
{
  auto str = std::to_string(value);
  makeNumberStringPretty<float>(str);
  return str;
}

template <>
std::string toPrettyString(const int& value)
{
  auto str = std::to_string(value);
  makeNumberStringPretty<int>(str);
  return str;
}

} // namespace aw::stringFormat

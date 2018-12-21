#pragma once

#include <regex>

namespace aw::regex
{
template <typename Type>
inline const char* getRegexString();

template <typename Type>
inline bool checkStringForType(const std::string& toCheck);

// Specializations
template <typename Type>
inline bool checkStringForType(const std::string& toCheck)
{
  return std::regex_match(toCheck, std::regex(getRegexString<Type>()));
}

template <>
inline const char* getRegexString<int>()
{
  return "^(0|[1-9][0-9]*)$";
}

template <>
inline const char* getRegexString<float>()
{
  return "[+-]?(?=[.]?[0-9])[0-9]*(?:[.][0-9]*)?(?:[Ee][+-]?[0-9]+)?";
}
template <>
inline const char* getRegexString<double>()
{
  return getRegexString<float>();
}
} // namespace aw::regex

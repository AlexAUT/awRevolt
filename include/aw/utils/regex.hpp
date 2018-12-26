#pragma once

#include <regex>

namespace aw::regex
{
template <typename Type>
inline const std::regex& getRegex();

template <typename Type>
inline const char* getRegexString();

template <typename Type>
inline bool checkStringForType(const std::string& toCheck);

// Implementations/Specializations
template <typename Type>
inline bool checkStringForType(const std::string& toCheck)
{
  return std::regex_match(toCheck, getRegex<Type>());
}

template <typename Type>
inline const std::regex& getRegex()
{
  static std::regex regex(getRegexString<Type>());
  return regex;
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

#pragma once

#include <string>

namespace aw
{
template <typename Type>
struct StringConverter
{
  inline Type operator()(const std::string& s);
};

template <>
inline int StringConverter<int>::operator()(const std::string& s)
{
  return std::stoi(s.c_str());
}

template <>
inline float StringConverter<float>::operator()(const std::string& s)
{
  return std::stof(s.c_str());
}

template <>
inline double StringConverter<double>::operator()(const std::string& s)
{
  return std::stod(s.c_str());
}
} // namespace aw

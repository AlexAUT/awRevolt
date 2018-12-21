#pragma once

#include <string>

namespace aw::stringFormat
{
template <typename Type>
void makeNumberStringPretty(std::string& number);

template <typename Type>
std::string toPrettyString(const Type& value);
} // namespace aw::stringFormat

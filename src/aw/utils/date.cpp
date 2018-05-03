#include <aw/utils/date.hpp>

#include <iomanip>
#include <sstream>

namespace aw
{
namespace date
{
inline std::string priv_put_time(const std::string& format)
{
  std::time_t t = std::time(nullptr);
  std::tm tm = *std::localtime(&t);
  std::stringstream sstr;
  sstr << std::put_time(&tm, format.c_str());
  return sstr.str();
}

std::string getYear()
{
  return priv_put_time("%Y");
}

std::string getMonth()
{
  return priv_put_time("%m");
}

std::string getDay()
{
  return priv_put_time("%d");
}

std::string getHour()
{
  return priv_put_time("%H");
}

std::string getMinute()
{
  return priv_put_time("%M");
}

std::string getSeconds()
{
  return priv_put_time("%S");
}

std::string getDateTime()
{
  return priv_put_time("%d/%m/%y %H:%M:%S");
}

} // namespace date
} // namespace aw

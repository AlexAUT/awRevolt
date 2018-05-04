#include <aw/utils/path.hpp>

#ifdef AW_ANDROID
#include <SFML/System/NativeActivity.hpp>
#include <android/native_activity.h>
#endif

namespace aw
{
namespace path
{
std::string getInternal()
{
#ifdef AW_DESKTOP
  return "";
#elif AW_ANDROID
  ANativeActivity* activity = sf::getNativeActivity();
  return std::string(activity->internalDataPath) + "/";
#endif
  return "";
}
std::string getExternal()
{
#ifdef AW_DESKTOP
  return "";
#elif AW_ANDROID
  ANativeActivity* activity = sf::getNativeActivity();
  return std::string(activity->externalDataPath) + "/";
#endif
  return "";
}

} // namespace path
} // namespace aw

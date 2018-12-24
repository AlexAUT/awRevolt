#include <aw/engine/settings.hpp>

#include <aw/engine/logCategories.hpp>
#include <aw/utils/log.hpp>

#include <fstream>

#include <json/json.h>

namespace aw
{
Settings Settings::loadFromFile(const std::string& path)
{
  Settings settings;

  std::ifstream configFile(path.c_str());
  if (configFile.is_open())
  {
    Json::CharReaderBuilder builder;
    Json::Value rootNode;
    std::string error;
    auto parseResult = Json::parseFromStream(builder, configFile, &rootNode, &error);
    if (parseResult)
    {
      settings.applicationName = rootNode.get("applicationName", settings.applicationName).asString();
      settings.resolution.x = rootNode.get("resolutionX", settings.resolution.x).asUInt();
      settings.resolution.y = rootNode.get("resolutionY", settings.resolution.y).asUInt();
      settings.bitsPerPixel = rootNode.get("bitsPerPixel", settings.bitsPerPixel).asUInt();
      settings.depthBits = rootNode.get("depthBits", settings.depthBits).asUInt();
      settings.stencilBits = rootNode.get("stencilBits", settings.stencilBits).asUInt();
      settings.antialiasing = rootNode.get("antialiasing", settings.antialiasing).asUInt();
      settings.openglMajor = rootNode.get("openglMajor", settings.openglMajor).asUInt();
      settings.openglMinor = rootNode.get("openglMinor", settings.openglMinor).asUInt();
      settings.coreContext = rootNode.get("coreContext", settings.coreContext).asBool();
      settings.debugContext = rootNode.get("debugContext", settings.debugContext).asBool();
      settings.vsync = rootNode.get("vsync", settings.vsync).asBool();
      settings.frameLimit = rootNode.get("frameLimit", settings.frameLimit).asUInt();
      settings.grabCursor = rootNode.get("grabCursor", settings.grabCursor).asBool();
      settings.cursorVisible = rootNode.get("cursorVisible", settings.cursorVisible).asBool();
      settings.sleepOnFocusLossAndroid =
          rootNode.get("sleepOnFocusLossAndroid", settings.sleepOnFocusLossAndroid).asFloat();
    }
    else
    {
      LogEngineW() << "Config file could not be parsed fallback to "
                      "default settings, error: "
                   << error;
    }
  }
  else
  {
    LogEngineW() << "Config file could not be opened fallback to default settings";
  }
  return settings;
}

bool Settings::save(const std::string& path) const
{
  std::fstream configFile(path.c_str(), std::ios::out | std::ios::trunc);
  if (configFile.is_open())
  {
    Json::Value config;
    config["applicationName"] = applicationName;
    config["resolutionX"] = resolution.x;
    config["resolutionY"] = resolution.y;
    config["bitsPerPixel"] = bitsPerPixel;
    config["depthBits"] = depthBits;
    config["stencilBits"] = stencilBits;
    config["antialiasing"] = antialiasing;
    config["openglMajor"] = openglMajor;
    config["openglMinor"] = openglMinor;
    config["coreContext"] = coreContext;
    config["debugContext"] = debugContext;
    config["vsync"] = vsync;
    config["frameLimit"] = frameLimit;
    config["grabCursor"] = grabCursor;
    config["cursorVisible"] = cursorVisible;

    configFile << config << std::endl;
    return true;
  }
  return false;
}
} // namespace aw

std::ostream& operator<<(std::ostream& stream, const aw::Settings& settings)
{
#define PRINT_MEMBER(x) "\tx: " << settings.x
  stream << PRINT_MEMBER(applicationName);
  stream << PRINT_MEMBER(resolution);
  stream << PRINT_MEMBER(bitsPerPixel);
  stream << PRINT_MEMBER(depthBits);
  stream << PRINT_MEMBER(stencilBits);
  stream << PRINT_MEMBER(antialiasing);
  stream << PRINT_MEMBER(openglMajor);
  stream << PRINT_MEMBER(openglMinor);
  stream << PRINT_MEMBER(coreContext);
  stream << PRINT_MEMBER(debugContext);
  stream << PRINT_MEMBER(vsync);
  stream << PRINT_MEMBER(frameLimit);
  stream << PRINT_MEMBER(grabCursor);
  stream << PRINT_MEMBER(cursorVisible);
  stream << PRINT_MEMBER(sleepOnFocusLossAndroid);

  return stream;
}

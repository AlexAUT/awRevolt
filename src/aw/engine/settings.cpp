#include <aw/engine/settings.hpp>

#include <aw/engine/logCategories.hpp>
#include <aw/utils/log.hpp>

#include <fstream>

#include <json/json.h>

namespace aw
{

void logSettings(const Settings& settings)
{
}

namespace priv
{
Settings loadSettings()
{
  Settings settings;

  std::ifstream configFile("config/engine.json");
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

bool saveSettings(const Settings& settings)
{
  std::fstream configFile("config/engine.json", std::ios::out | std::ios::trunc);
  if (configFile.is_open())
  {
    Json::Value config;
    config["applicationName"] = settings.applicationName;
    config["resolutionX"] = settings.resolution.x;
    config["resolutionY"] = settings.resolution.y;
    config["bitsPerPixel"] = settings.bitsPerPixel;
    config["depthBits"] = settings.depthBits;
    config["stencilBits"] = settings.stencilBits;
    config["antialiasing"] = settings.antialiasing;
    config["openglMajor"] = settings.openglMajor;
    config["openglMinor"] = settings.openglMinor;
    config["coreContext"] = settings.coreContext;
    config["debugContext"] = settings.debugContext;
    config["vsync"] = settings.vsync;
    config["frameLimit"] = settings.frameLimit;
    config["grabCursor"] = settings.grabCursor;
    config["cursorVisible"] = settings.cursorVisible;

    configFile << config << std::endl;
    return true;
  }
  return false;
}

} // namespace priv

} // namespace aw

#include <aw/utils/log.hpp>

#include <aw/utils/time/date.hpp>

#include <cassert>
#include <fstream>
#include <memory>
#include <sstream>

#include <SFML/Network/Http.hpp>

#ifdef AW_ANDROID
#include <aw/utils/impl/androidStreamBuffer.hpp>
#endif

namespace aw
{

bool initialized = false;
log::LogLevel logOutputLevelConsole = log::Debug;
log::LogLevel logOutputLevelFile = log::Verbose;
log::LogLevel logOutputLevelRemote = log::Error;

std::ostream* consoleStream{nullptr};
std::ostream* fileStream{nullptr};

sf::Http httpClient;

namespace log
{

std::string colorPrefix(LogLevel level)
{
#ifdef AW_DESKTOP
  switch (level)
  {
  case Error:
    return "\033[0;31m";
  case Warning:
    return "\033[0;33m";
  case Verbose:
    return "\033[0m";
  case Debug:
    return "\033[0;34m";
  default:
    return "\033[0m";
  }
#else
  return "";
#endif
}

std::string logLevelToString(LogLevel level)
{
  switch (level)
  {
  case Error:
    return "(E) ";
  case Warning:
    return "(W) ";
  case Verbose:
    return "(V) ";
  case Debug:
    return "(D) ";
  default:
    return "(U) ";
  }
}

LogInstance::LogInstance(LogLevel level, const std::string& module, std::ostream& console, std::ostream& file) :
    mWriteToConsole(level <= logOutputLevelConsole),
    mWriteToFileSystem(level <= logOutputLevelFile),
    mWriteToRemoteServer(level <= logOutputLevelRemote),
    mConsoleStream(console),
    mFileStream(file)
{
  auto prefix = colorPrefix(level) + logLevelToString(level);
  auto timestamp = date::getDateTime();
  if (mWriteToConsole)
    mConsoleStream << prefix << timestamp << " (" << module << "): ";
  if (mWriteToFileSystem)
    mFileStream << timestamp << " (" << module << "): ";
}

LogInstance::~LogInstance()
{
  if (mWriteToConsole)
    mConsoleStream << std::endl;
  if (mWriteToFileSystem)
    mFileStream << std::endl;
}

void LogInstance::writeToServer(std::string text) const
{
  sf::Http::Request getAll;
  getAll.setUri("/logSessions");
  getAll.setMethod(sf::Http::Request::Method::Post);
  getAll.setHttpVersion(1, 1);
  getAll.setBody("content=" + text);

  auto response = httpClient.sendRequest(getAll);

  LogTemp() << "Response: " << response.getStatus();
  LogTemp() << "Content: " << response.getBody();
}

} // namespace log

bool LOG_INITIALIZE(log::LogLevel console, log::LogLevel filesystem, std::string logFilePath, log::LogLevel remote,
                    std::string address, int port)
{
  assert(!initialized && "For now you can only call initialize once!");
  initialized = true;

  logOutputLevelConsole = console;
  logOutputLevelFile = filesystem;
  logOutputLevelRemote = remote;

#ifdef AW_ANDROID
  // Redirect cout to logcat on android
  std::cout.rdbuf(new AndroidStreamBuffer);
#endif

  consoleStream = &std::cout;

  if (logOutputLevelFile != log::None)
  {
    std::ofstream* file = new std::ofstream(logFilePath.c_str(), std::ios::app);
    if (file->is_open())
    {
      fileStream = file;
    }
    else
    {
      logOutputLevelFile = log::None;
      std::cout << "Failed to open log output file!" << std::endl;
    }
  }
  if (logOutputLevelFile != log::None)
  {
    httpClient.setHost(address, port);
  }
  return true;
}

aw::log::LogInstance LOG(log::LogLevel level, std::string moduleName)
{
  assert(initialized && "You have to call LOG_INITIALIZE before you can use LOG!");

  return {level, moduleName, *consoleStream, *fileStream};
}

aw::log::LogInstance LOG(const log::LogModule& logModule)
{
  return LOG(logModule.level, logModule.moduleName);
}

} // namespace aw

const aw::log::LogModule logModuleTemp{aw::log::Debug, "LogTemp"};
aw::log::LogInstance LogTemp()
{
  return aw::LOG(logModuleTemp);
}

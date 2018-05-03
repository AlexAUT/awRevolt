#include <aw/utils/log.hpp>

#include <aw/utils/date.hpp>

#include <cassert>
#include <fstream>
#include <memory>

namespace aw
{

bool initialized = false;
log::LogLevel logOutputLevelConsole = log::Debug;
log::LogLevel logOutputLevelFile = log::Verbose;

std::ostream* consoleStream{nullptr};
std::ostream* fileStream{nullptr};

namespace log
{

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

LogInstance::LogInstance(LogLevel level, const std::string& module, std::ostream& console, std::ostream& file)
    : mWriteToConsole(level <= logOutputLevelConsole), mWriteToFileSystem(level <= logOutputLevelFile),
      mConsoleStream(console), mFileStream(file)
{
  auto prefix = logLevelToString(level);
  auto timestamp = date::getDateTime();
  if (mWriteToConsole)
    mConsoleStream << prefix << timestamp << " (" << module << "): ";
  if (mWriteToFileSystem)
    mFileStream << prefix << timestamp << " (" << module << "): ";
}

LogInstance::~LogInstance()
{
  if (mWriteToConsole)
    mConsoleStream << std::endl;
  if (mWriteToFileSystem)
    mFileStream << std::endl;
}

} // namespace log

bool LOG_INITIALIZE(log::LogLevel console, log::LogLevel filesystem, std::string logFilePath)
{
  assert(!initialized && "For now you can only call initialize once!");
  initialized = true;

  logOutputLevelConsole = console;
  logOutputLevelFile = filesystem;

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

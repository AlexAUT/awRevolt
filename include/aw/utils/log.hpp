#pragma once

#include <aw/utils/file/path.hpp>

#include <functional>
#include <iostream>
#include <sstream>
#include <string>

namespace aw
{
namespace log
{
enum LogLevel
{
  None, // Should only be used for output level, not for logging itself
  Error,
  Warning,
  Debug,
  Verbose,
};
struct LogModule
{
  const LogLevel level;
  const std::string moduleName;
};

class LogInstance
{
public:
  LogInstance(LogLevel level, const std::string& module, std::ostream& console, std::ostream& file);
  ~LogInstance();

  template <typename T>
  LogInstance& operator<<(const T& toOutput);

private:
  void writeToServer(std::string text);

private:
  bool mWriteToConsole;
  bool mWriteToFileSystem;
  bool mWriteToRemoteServer;
  std::ostream& mConsoleStream;
  std::ostream& mFileStream;
};

// This macro will create a log module for easier use
// LOG_CATEGORY(Test, Warning, TestPretty)
// ...
// LogTest() << "Hallo welt";
// This will create a log entry with module Name: Test, Type: Error
// Output will look like: (E) DATE (TestPretty): Hallo Welt
#define DEFINE_LOG_CATEGORY(Name, Type, DisplayName)                                                                   \
  const aw::log::LogModule logModule##Name{Type, #DisplayName};                                                        \
  aw::log::LogInstance Log##Name() { return aw::LOG(logModule##Name); }
} // namespace log

bool LOG_INITIALIZE(log::LogLevel console = log::Debug, log::LogLevel filesystem = log::Verbose,
                    std::string logFilePath = Path::getInternal() + "log.txt", log::LogLevel remote = log::None,
                    std::string address = "188.68.48.23", int port = 15909);
aw::log::LogInstance LOG(log::LogLevel level, std::string moduleName);
aw::log::LogInstance LOG(const log::LogModule& logModule);
} // namespace aw

// Inline definitions
namespace aw
{
namespace log
{
template <class T>
LogInstance& LogInstance::operator<<(const T& toOutput)
{
  if (mWriteToConsole)
    mConsoleStream << toOutput;
  if (mWriteToFileSystem)
    mFileStream << toOutput;
  if (mWriteToRemoteServer)
  {
    std::stringstream sstr;
    sstr << toOutput;
    writeToServer(sstr.str());
  }
  return *this;
}
} // namespace log

} // namespace aw

aw::log::LogInstance LogTemp();

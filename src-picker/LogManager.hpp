#ifndef PICKER_LOGMANAGER_HPP
#define PICKER_LOGMANAGER_HPP

#include <memory>
#include <string_view>

#include "Logger.hpp"

namespace picker {

void setGlobalLogger(std::unique_ptr<Logger>&& inLogger);

void logTrace(std::string_view message);

void logDebug(std::string_view message);

void logInfo(std::string_view message);

void logWarning(std::string_view message);

void logError(std::string_view message);

void logCritical(std::string_view message);

class LogManager
{
public:
  static LogManager& getInstance( );

  void setLogger(std::unique_ptr<Logger>&& inLogger);

  void trace(std::string_view message) const;

  void debug(std::string_view message) const;

  void info(std::string_view message) const;

  void warning(std::string_view message) const;

  void error(std::string_view message) const;

  void critical(std::string_view message) const;

private:
  LogManager( ) = default;

  std::unique_ptr<Logger> logger{ };
};

}// namespace picker

#endif

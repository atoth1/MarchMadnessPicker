#ifndef PICKER_LOGGER_HPP
#define PICKER_LOGGER_HPP

#include <string_view>

namespace picker {

enum class LogLevel { TRACE, DEBUG, INFO, WARNING, ERROR, CRITICAL, OFF };

class Logger
{
public:
  virtual ~Logger( ) = default;

  Logger(const Logger&) = delete;

  Logger(Logger&&) = delete;

  Logger& operator=(const Logger&) = delete;

  Logger& operator=(Logger&&) = delete;

  virtual void trace(std::string_view message) = 0;

  virtual void debug(std::string_view message) = 0;

  virtual void info(std::string_view message) = 0;

  virtual void warning(std::string_view message) = 0;

  virtual void error(std::string_view message) = 0;

  virtual void critical(std::string_view message) = 0;

protected:
  Logger( ) = default;
};

}// namespace picker

#endif

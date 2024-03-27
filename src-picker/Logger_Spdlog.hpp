#ifndef PICKER_LOGGER_SPDLOG_HPP
#define PICKER_LOGGER_SPDLOG_HPP

#include <memory>
#include <string_view>

#include "spdlog/logger.h"

#include "Logger.hpp"

namespace picker {
class SpdlogLogger : public Logger
{
public:
  struct LogLevels
  {
    LogLevel screenLevel{ };
    LogLevel fileLevel{ };
  };

  static constexpr std::string_view LOG_FILE_NAME = "log.txt";

  explicit SpdlogLogger(LogLevels levels);

  void trace(std::string_view message) override;

  void debug(std::string_view message) override;

  void info(std::string_view message) override;

  void warning(std::string_view message) override;

  void error(std::string_view message) override;

  void critical(std::string_view message) override;

private:
  std::unique_ptr<spdlog::logger> logger{ };
};

}// namespace picker

#endif

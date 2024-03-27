#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "spdlog/common.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "Logger.hpp"
#include "Logger_Spdlog.hpp"

picker::SpdlogLogger::SpdlogLogger(picker::SpdlogLogger::LogLevels levels)
{
  auto toSpdlogLevel = [](LogLevel level) { return static_cast<spdlog::level::level_enum>(static_cast<int>(level)); };

  std::vector<spdlog::sink_ptr> sinks{ };

  if (levels.screenLevel != LogLevel::OFF) {
    auto stdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>( );
    stdoutSink->set_level(toSpdlogLevel(levels.screenLevel));
    sinks.push_back(stdoutSink);
  }

  if (levels.fileLevel != LogLevel::OFF) {
    auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(std::string{ LOG_FILE_NAME });
    fileSink->set_level(toSpdlogLevel(levels.fileLevel));
    sinks.push_back(fileSink);
  }

  logger = std::make_unique<spdlog::logger>("picker_log", sinks.begin( ), sinks.end( ));
  // Set to trace so that output is limited by individual sink level.
  logger->set_level(spdlog::level::trace);
}

void picker::SpdlogLogger::trace(std::string_view message) { logger->trace(message); }

void picker::SpdlogLogger::debug(std::string_view message) { logger->debug(message); }

void picker::SpdlogLogger::info(std::string_view message) { logger->info(message); }

void picker::SpdlogLogger::warning(std::string_view message) { logger->warn(message); }

void picker::SpdlogLogger::error(std::string_view message) { logger->error(message); }

void picker::SpdlogLogger::critical(std::string_view message) { logger->critical(message); }

#include <fstream>
#include <memory>
#include <string>
#include <string_view>

#include "catch2/catch_test_macros.hpp"

#include "LogManager.hpp"
#include "Logger.hpp"
#include "Logger_Spdlog.hpp"
#include "PickerConfig.hpp"
#include "TestUtils.hpp"

// NOLINTNEXTLINE(misc-use-anonymous-namespace, readability-function-cognitive-complexity)
TEST_CASE("Logging - global interface", "[Logging]")
{
  MockLogger::Counts counts{ };
  picker::setGlobalLogger(std::make_unique<MockLogger>(&counts));
  static constexpr std::string_view msg{ "unused" };

  static constexpr int traceCount = picker::enableLogging ? 1 : 0;
  for (int repeat = 0; repeat < traceCount; ++repeat) { picker::logTrace(msg); }
  CHECK(counts.trace == traceCount);// NOLINT(cppcoreguidelines-avoid-do-while)

  static constexpr int debugCount = picker::enableLogging ? 2 : 0;
  for (int repeat = 0; repeat < debugCount; ++repeat) { picker::logDebug(msg); }
  CHECK(counts.debug == debugCount);// NOLINT(cppcoreguidelines-avoid-do-while)

  static constexpr int infoCount = picker::enableLogging ? 3 : 0;
  for (int repeat = 0; repeat < infoCount; ++repeat) { picker::logInfo(msg); }
  CHECK(counts.info == infoCount);// NOLINT(cppcoreguidelines-avoid-do-while)

  static constexpr int warningCount = picker::enableLogging ? 4 : 0;
  for (int repeat = 0; repeat < warningCount; ++repeat) { picker::logWarning(msg); }
  CHECK(counts.warning == warningCount);// NOLINT(cppcoreguidelines-avoid-do-while)

  static constexpr int errorCount = picker::enableLogging ? 5 : 0;
  for (int repeat = 0; repeat < errorCount; ++repeat) { picker::logError(msg); }
  CHECK(counts.error == errorCount);// NOLINT(cppcoreguidelines-avoid-do-while)

  static constexpr int criticalCount = picker::enableLogging ? 6 : 0;
  for (int repeat = 0; repeat < criticalCount; ++repeat) { picker::logCritical(msg); }
  CHECK(counts.critical == criticalCount);// NOLINT(cppcoreguidelines-avoid-do-while)
}

TEST_CASE("Logging - spdlog file creation", "[Logging]")// NOLINT(misc-use-anonymous-namespace)
{
  const auto logger = std::make_unique<picker::SpdlogLogger>(
    picker::SpdlogLogger::LogLevels{ picker::LogLevel::OFF, picker::LogLevel::DEBUG });
  const std::string logFileName{ picker::SpdlogLogger::LOG_FILE_NAME };
  const std::ifstream logFile{ logFileName };
  logger->debug("test log message.");
  CHECK(logFile.is_open( ));// NOLINT(cppcoreguidelines-avoid-do-while)
}

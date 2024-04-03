#include <array>
#include <memory>
#include <utility>

#include "catch2/catch_test_macros.hpp"

#include "CommandLineParser.hpp"
#include "CommandLineParser_CLI.hpp"
#include "Constants.hpp"
#include "Logger.hpp"

TEST_CASE("CommandLineParser - missing required input file name", "[CLP]")// NOLINT(misc-use-anonymous-namespace)
{
  constexpr std::array argv = { "program_name" };
  constexpr auto argc = static_cast<int>(argv.size( ));

  const std::unique_ptr<picker::CommandLineParser> clp = std::make_unique<picker::CLIParser>( );
  const auto parseResult = clp->parse(argc, argv.data( ));

  CHECK(!parseResult.has_value( ));// NOLINT(cppcoreguidelines-avoid-do-while)
}

TEST_CASE("CommandLineParser - successful parse with defaults", "[CLP]")// NOLINT(misc-use-anonymous-namespace)
{
  constexpr std::array argv = { "program_name", "-i", "input.json" };
  constexpr auto argc = static_cast<int>(argv.size( ));
  constexpr int inFileId = 2;

  const std::unique_ptr<picker::CommandLineParser> clp = std::make_unique<picker::CLIParser>( );
  const auto parseResult = clp->parse(argc, argv.data( ));

  // NOLINTBEGIN(cppcoreguidelines-avoid-do-while, bugprone-unchecked-optional-access)
  REQUIRE(parseResult.has_value( ));
  CHECK(parseResult->inputFile == argv[inFileId]);
  CHECK(parseResult->screenLogLevel == picker::LogLevel::WARNING);
  CHECK(parseResult->fileLogLevel == picker::LogLevel::OFF);
  // NOLINTEND(cppcoreguidelines-avoid-do-while, bugprone-unchecked-optional-access)
}

// NOLINTNEXTLINE(misc-use-anonymous-namespace, readability-function-cognitive-complexity)
TEST_CASE("CommandLineParser - successful parse no defaults", "[CLP]")
{
  std::array argv{ "program_name", "-i", "input.json", "-f", "", "-s", "" };
  constexpr auto argc = static_cast<int>(argv.size( ));
  constexpr int inFileId = 2;
  constexpr int fileLogLevelId = 4;
  constexpr int screenLogLevelId = 6;

  const std::unique_ptr<picker::CommandLineParser> clp = std::make_unique<picker::CLIParser>( );

  constexpr std::array logLevels{ std::pair{ picker::TRACE_LABEL, picker::LogLevel::TRACE },
    std::pair{ picker::DEBUG_LABEL, picker::LogLevel::DEBUG },
    std::pair{ picker::INFO_LABEL, picker::LogLevel::INFO },
    std::pair{ picker::WARNING_LABEL, picker::LogLevel::WARNING },
    std::pair{ picker::ERROR_LABEL, picker::LogLevel::ERROR },
    std::pair{ picker::CRITICAL_LABEL, picker::LogLevel::CRITICAL },
    std::pair{ picker::OFF_LABEL, picker::LogLevel::OFF } };
  for (const auto& [screenLevelLabel, screenLevel] : logLevels) {
    for (const auto& [fileLevelLabel, fileLevel] : logLevels) {
      argv[screenLogLevelId] = screenLevelLabel.data( );
      argv[fileLogLevelId] = fileLevelLabel.data( );
      const auto parseResult = clp->parse(argc, argv.data( ));

      // NOLINTBEGIN(cppcoreguidelines-avoid-do-while, bugprone-unchecked-optional-access)
      REQUIRE(parseResult.has_value( ));
      CHECK(parseResult->inputFile == argv[inFileId]);
      CHECK(parseResult->screenLogLevel == screenLevel);
      CHECK(parseResult->fileLogLevel == fileLevel);
      // NOLINTEND(cppcoreguidelines-avoid-do-while, bugprone-unchecked-optional-access)
    }
  }
}
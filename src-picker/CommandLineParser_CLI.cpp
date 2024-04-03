#include <map>
#include <optional>
#include <string>

#include "CLI/CLI.hpp"// NOLINT(misc-include-cleaner)

#include "CommandLineParser.hpp"
#include "CommandLineParser_CLI.hpp"
#include "Constants.hpp"
#include "Logger.hpp"

std::optional<picker::CommandLineParseResult> picker::CLIParser::parse(int argc, const char* const* argv) const
{
  CLI::App app{ "Simulator for producing March Madness brackets.", "picker" };// NOLINT(misc-include-cleaner)
  CommandLineParseResult result{ };

  app.add_option("-i, --input", result.inputFile, "Path for JSON input file")->required( );

  const std::map<std::string, picker::LogLevel> logLevelMap{ { std::string{ picker::TRACE_LABEL },
                                                               picker::LogLevel::TRACE },
    { std::string{ picker::DEBUG_LABEL }, picker::LogLevel::DEBUG },
    { std::string{ picker::INFO_LABEL }, picker::LogLevel::INFO },
    { std::string{ picker::WARNING_LABEL }, picker::LogLevel::WARNING },
    { std::string{ picker::ERROR_LABEL }, picker::LogLevel::ERROR },
    { std::string{ picker::CRITICAL_LABEL }, picker::LogLevel::CRITICAL },
    { std::string{ picker::OFF_LABEL }, picker::LogLevel::OFF } };
  app.add_option("-s,--screen-log-level", result.screenLogLevel, "Screen log output level")
    ->transform(CLI::CheckedTransformer(logLevelMap, CLI::ignore_case));// NOLINT(misc-include-cleaner)
  app.add_option("-f,--file-log-level", result.fileLogLevel, "File log output level")
    ->transform(CLI::CheckedTransformer(logLevelMap, CLI::ignore_case));// NOLINT(misc-include-cleaner)

  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError& e) {// NOLINT(misc-include-cleaner)
    app.exit(e);
    return std::nullopt;
  }
  return result;
}

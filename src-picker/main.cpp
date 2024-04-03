#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "CLI/CLI.hpp"// NOLINT(misc-include-cleaner)

#include "LogManager.hpp"
#include "Logger.hpp"
#include "Logger_Spdlog.hpp"
#include "Problem.hpp"


int main(int argc, char** argv)
{
  try {
    std::string jsonInput{ };
    picker::LogLevel screenLogLevel{ picker::LogLevel::WARNING };
    picker::LogLevel fileLogLevel{ picker::LogLevel::OFF };

    auto parseCommandLine = [&]( ) {
      CLI::App app{ "Simulator for producing March Madness brackets.", "picker" };// NOLINT(misc-include-cleaner)

      app.add_option("-i, --input", jsonInput, "Path for JSON input file")->required( );

      const std::map<std::string, picker::LogLevel> logLevelMap{ { "trace", picker::LogLevel::TRACE },
        { "debug", picker::LogLevel::DEBUG },
        { "info", picker::LogLevel::INFO },
        { "warning", picker::LogLevel::WARNING },
        { "error", picker::LogLevel::ERROR },
        { "critical", picker::LogLevel::CRITICAL },
        { "off", picker::LogLevel::OFF } };
      app.add_option("-s,--screen-log-level", screenLogLevel, "Screen log output level")
        ->transform(CLI::CheckedTransformer(logLevelMap, CLI::ignore_case));// NOLINT(misc-include-cleaner)
      app.add_option("-f,--file-log-level", fileLogLevel, "File log output level")
        ->transform(CLI::CheckedTransformer(logLevelMap, CLI::ignore_case));// NOLINT(misc-include-cleaner)

      bool success = true;
      try {
        app.parse(argc, argv);
      } catch (const CLI::ParseError& e) {// NOLINT(misc-include-cleaner)
        app.exit(e);
        success = false;
      }
      return success;
    };
    if (!parseCommandLine( )) { return 0; }

    picker::setGlobalLogger(
      std::make_unique<picker::SpdlogLogger>(picker::SpdlogLogger::LogLevels{ screenLogLevel, fileLogLevel }));
    picker::Problem problem(jsonInput);
    problem.setup( );
    problem.run( );
  } catch (const std::exception& e) {
    std::cerr << "Caught exception: " << e.what( ) << '\n';
  }
}

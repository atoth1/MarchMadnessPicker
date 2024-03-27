#include <exception>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "CLI/CLI.hpp"// NOLINT(misc-include-cleaner)

#include "Constants.hpp"
#include "LogManager.hpp"
#include "Logger.hpp"
#include "Logger_Spdlog.hpp"
#include "OutputStrategy_FileOut.hpp"
#include "OutputStrategy_StdOut.hpp"
#include "Problem.hpp"
#include "RandomizationStrategy_MersenneTwister.hpp"
#include "RandomizationStrategy_MinStdRand.hpp"
#include "RandomizationStrategy_StdRand.hpp"
#include "SelectionStrategy_CoinFlip.hpp"
#include "SelectionStrategy_RankDeterministic.hpp"
#include "SelectionStrategy_SpreadBased.hpp"

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

    auto registerRandomizationStrategyFactories = [&]( ) {
      picker::logDebug("Registering randomization strategy factories.");
      problem.registerRandomizationStrategyFactory(
        picker::MERSENNE_TWISTER_STRATEGY_LABEL, std::make_unique<picker::MersenneTwisterStrategyFactory>( ));
      problem.registerRandomizationStrategyFactory(
        picker::MINSTD_RAND_STRATEGY_LABEL, std::make_unique<picker::MinStdRandStrategyFactory>( ));
      problem.registerRandomizationStrategyFactory(
        picker::STD_RAND_STRATEGY_LABEL, std::make_unique<picker::StdRandStrategyFactory>( ));
    };
    registerRandomizationStrategyFactories( );

    auto registerSelectionStrategyFactories = [&]( ) {
      picker::logDebug("Registering selection strategy factories");
      problem.registerSelectionStrategyFactory(
        picker::COIN_FLIP_STRATEGY_LABEL, std::make_unique<picker::CoinFlipStrategyFactory>( ));
      problem.registerSelectionStrategyFactory(
        picker::RANK_DETERMINISTIC_STRATEGY_LABEL, std::make_unique<picker::RankDeterministicStrategyFactory>( ));
      problem.registerSelectionStrategyFactory(
        picker::SPREAD_BASED_STRATEGY_LABEL, std::make_unique<picker::SpreadBasedStrategyFactory>( ));
    };
    registerSelectionStrategyFactories( );

    auto registerOutputStrategyFactories = [&]( ) {
      picker::logDebug("Registering output strategy factories");
      problem.registerOutputStrategyFactory(
        picker::FILE_OUT_STRATEGY_LABEL, std::make_unique<picker::FileOutStrategyFactory>( ));
      problem.registerOutputStrategyFactory(
        picker::STD_OUT_STRATEGY_LABEL, std::make_unique<picker::StdOutStrategyFactory>( ));
    };
    registerOutputStrategyFactories( );

    problem.setup( );
    problem.run( );
  } catch (const std::exception& e) {
    std::cerr << "Caught exception: " << e.what( ) << '\n';
  }
}

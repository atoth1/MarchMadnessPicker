#include <fstream>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "fmt/core.h"
#include "nlohmann/json.hpp"

#include "Bracket.hpp"
#include "Constants.hpp"
#include "LogManager.hpp"
#include "OutputStrategy_Factory.hpp"
#include "OutputStrategy_FileOut.hpp"
#include "OutputStrategy_StdOut.hpp"
#include "Problem.hpp"
#include "ProblemData.hpp"
#include "RandomizationStrategy_Factory.hpp"
#include "RandomizationStrategy_MersenneTwister.hpp"
#include "RandomizationStrategy_MinStdRand.hpp"
#include "RandomizationStrategy_StdRand.hpp"
#include "SelectionStrategy_CoinFlip.hpp"
#include "SelectionStrategy_Factory.hpp"
#include "SelectionStrategy_RankDeterministic.hpp"
#include "SelectionStrategy_SpreadBased.hpp"

picker::Problem::Problem(const std::string& inputFileName)
{
  std::ifstream inputFile(inputFileName);
  const auto parsedInput = nlohmann::json::parse(inputFile);// NOLINT(misc-include-cleaner)
  parsedInput.get_to(problemData);
  problemData.validate( );
}

void picker::Problem::registerOutputStrategyFactory(std::string_view name,
  std::unique_ptr<OutputStrategyFactory::FactoryType>&& factory)
{
  outputStrategyFactory.registerFactory(name, std::move(factory));
  logDebug(fmt::format("Registered factory for output strategy: {}.", name));
}

void picker::Problem::registerRandomizationStrategyFactory(std::string_view name,
  std::unique_ptr<RandomizationStrategyFactory::FactoryType>&& factory)
{
  randomizationStrategyFactory.registerFactory(name, std::move(factory));
  logDebug(fmt::format("Registered factory for randomization strategy: {}.", name));
}

void picker::Problem::registerSelectionStrategyFactory(std::string_view name,
  std::unique_ptr<SelectionStrategyFactory::FactoryType>&& factory)
{
  selectionStrategyFactory.registerFactory(name, std::move(factory));
  logDebug(fmt::format("Registered factory for selection strategy: {}.", name));
}

void picker::Problem::setup( )
{
  logDebug("Setting up problem.");

  registerStandardStrategyFactories( );

  const auto randomizationStrategy =
    randomizationStrategyFactory.create(problemData.randomizationStrategy, problemData.randomizationStrategyParams);

  selectionStrategyFactory.setRandomizationStrategy(randomizationStrategy);
  selectionStrategyFactory.setTeamDataLookup(problemData.teamDataLookup);
  selectionStrategy =
    selectionStrategyFactory.create(problemData.selectionStrategy, problemData.selectionStrategyParams);

  outputStrategy = outputStrategyFactory.create(problemData.outputStrategy, problemData.outputStrategyParams);
}

void picker::Problem::run( ) const
{
  logDebug("Running problem.");

  if (!selectionStrategy) {
    logWarning("Selection strategy is null, returning without running.");
  } else if (!outputStrategy) {
    logWarning("Output strategy is null, returning without running.");
  } else {
    outputStrategy->writeOutput(makeBracket(problemData.bracketData, selectionStrategy));
  }
}

std::vector<std::string_view> picker::Problem::getRegisteredOutputStrategyNames( ) const
{
  return outputStrategyFactory.getRegisteredNames( );
}

std::vector<std::string_view> picker::Problem::getRegisteredRandomizationStrategyNames( ) const
{
  return randomizationStrategyFactory.getRegisteredNames( );
}

std::vector<std::string_view> picker::Problem::getRegisteredSelectionStrategyNames( ) const
{
  return selectionStrategyFactory.getRegisteredNames( );
}

void picker::Problem::registerStandardStrategyFactories( )
{
  auto registerRandomizationStrategyFactories = [this]( ) {
    registerRandomizationStrategyFactory(
      picker::MERSENNE_TWISTER_STRATEGY_LABEL, std::make_unique<picker::MersenneTwisterStrategyFactory>( ));
    registerRandomizationStrategyFactory(
      picker::MINSTD_RAND_STRATEGY_LABEL, std::make_unique<picker::MinStdRandStrategyFactory>( ));
    registerRandomizationStrategyFactory(
      picker::STD_RAND_STRATEGY_LABEL, std::make_unique<picker::StdRandStrategyFactory>( ));
  };
  registerRandomizationStrategyFactories( );

  auto registerSelectionStrategyFactories = [this]( ) {
    registerSelectionStrategyFactory(
      picker::COIN_FLIP_STRATEGY_LABEL, std::make_unique<picker::CoinFlipStrategyFactory>( ));
    registerSelectionStrategyFactory(
      picker::RANK_DETERMINISTIC_STRATEGY_LABEL, std::make_unique<picker::RankDeterministicStrategyFactory>( ));
    registerSelectionStrategyFactory(
      picker::SPREAD_BASED_STRATEGY_LABEL, std::make_unique<picker::SpreadBasedStrategyFactory>( ));
  };
  registerSelectionStrategyFactories( );

  auto registerOutputStrategyFactories = [this]( ) {
    registerOutputStrategyFactory(picker::FILE_OUT_STRATEGY_LABEL, std::make_unique<picker::FileOutStrategyFactory>( ));
    registerOutputStrategyFactory(picker::STD_OUT_STRATEGY_LABEL, std::make_unique<picker::StdOutStrategyFactory>( ));
  };
  registerOutputStrategyFactories( );
}

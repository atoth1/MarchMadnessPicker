#include <fstream>
#include <memory>
#include <string>
#include <string_view>
#include <utility>

#include "fmt/core.h"
#include "nlohmann/json.hpp"

#include "Bracket.hpp"
#include "LogManager.hpp"
#include "OutputStrategy.hpp"// NOLINT(misc-include-cleaner)
#include "OutputStrategy_Factory.hpp"
#include "Problem.hpp"
#include "ProblemData.hpp"
#include "RandomizationStrategy_Factory.hpp"
#include "SelectionStrategy_Factory.hpp"

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

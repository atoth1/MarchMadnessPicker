#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include "nlohmann/json.hpp"

#include "Bracket.hpp"
#include "OutputStrategy.hpp"
#include "OutputStrategy_Factory.hpp"
#include "Problem.hpp"
#include "ProblemData.hpp"
#include "RandomizationStrategy_Factory.hpp"
#include "SelectionStrategy_Factory.hpp"

picker::Problem::Problem(const std::string& inputFileName)
{
  std::ifstream inputFile(inputFileName);
  const auto parsedInput = nlohmann::json::parse(inputFile);
  parsedInput.get_to(problemData);
  problemData.validate( );
}

void picker::Problem::registerOutputStrategyFactory(std::string_view name,
  std::unique_ptr<OutputStrategyFactory::FactoryType>&& factory)
{
  outputStrategyFactory.registerFactory(name, std::move(factory));
}

void picker::Problem::registerRandomizationStrategyFactory(std::string_view name,
  std::unique_ptr<RandomizationStrategyFactory::FactoryType>&& factory)
{
  randomizationStrategyFactory.registerFactory(name, std::move(factory));
}

void picker::Problem::registerSelectionStrategyFactory(std::string_view name,
  std::unique_ptr<SelectionStrategyFactory::FactoryType>&& factory)
{
  selectionStrategyFactory.registerFactory(name, std::move(factory));
}

void picker::Problem::setup( )
{
  const auto randomizationStrategy =
    randomizationStrategyFactory.create(problemData.randomizationStrategy, problemData.randomizationStrategyParams);
  selectionStrategy =
    selectionStrategyFactory.create(problemData.selectionStrategy, problemData.selectionStrategyParams);
  outputStrategy = outputStrategyFactory.create(problemData.outputStrategy, problemData.outputStrategyParams);
}

void picker::Problem::run( ) const
{
  if (!selectionStrategy) { throw std::runtime_error("ERROR - selection strategy is null."); }
  if (!outputStrategy) { throw std::runtime_error("ERROR - output strategy is null."); }
  outputStrategy->writeOutput(makeBracket(problemData.bracketData, selectionStrategy));
}

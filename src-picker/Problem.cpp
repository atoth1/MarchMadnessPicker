#include <fstream>
#include <memory>
#include <string>
#include <string_view>
#include <utility>

#include "nlohmann/json.hpp"

#include "Bracket.hpp"
#include "OutputStrategy.hpp"
#include "Problem.hpp"
#include "ProblemData.hpp"

picker::Problem::Problem(const std::string& inputFileName)
{
  std::ifstream inputFile(inputFileName);
  const auto parsedInput = nlohmann::json::parse(inputFile);
  parsedInput.get_to(problemData);
  problemData.validate( );
}

const picker::ProblemData& picker::Problem::getProblemData( ) const { return problemData; }

void picker::Problem::registerOutputStrategyFactory(std::string_view name,
  std::unique_ptr<GenericFactory<OutputStrategy>>&& factory)
{
  outputStrategyFactory.registerFactory(name, std::move(factory));
}

void picker::Problem::createOutputStrategy( )
{
  outputStrategy = outputStrategyFactory.create(problemData.outputStrategy, problemData.outputStrategyParams);
}

std::shared_ptr<picker::OutputStrategy> picker::Problem::getOutputStrategy( ) const { return outputStrategy; }

void picker::Problem::registerRandomizationStrategyFactory(std::string_view name,
  std::unique_ptr<GenericFactory<RandomizationStrategy>>&& factory)
{
  randomizationStrategyFactory.registerFactory(name, std::move(factory));
}

void picker::Problem::createRandomizationStrategy( )
{
  randomizationStrategy =
    randomizationStrategyFactory.create(problemData.randomizationStrategy, problemData.randomizationStrategyParams);
}

std::shared_ptr<picker::RandomizationStrategy> picker::Problem::getRandomizationStrategy( ) const
{
  return randomizationStrategy;
}

void picker::Problem::registerSelectionStrategyFactory(std::string_view name,
  std::unique_ptr<GenericFactory<SelectionStrategy>>&& factory)
{
  selectionStrategyFactory.registerFactory(name, std::move(factory));
}

void picker::Problem::createSelectionStrategy( )
{
  selectionStrategy =
    selectionStrategyFactory.create(problemData.selectionStrategy, problemData.selectionStrategyParams);
}

std::shared_ptr<picker::SelectionStrategy> picker::Problem::getSelectionStrategy( ) const { return selectionStrategy; }

void picker::Problem::run( ) const
{
  if (!outputStrategy || !randomizationStrategy || !selectionStrategy) {
    throw std::runtime_error("ERROR - one or more strategy is null.");
  }
  outputStrategy->writeOutput(makeBracket(problemData.bracketData, selectionStrategy));
}

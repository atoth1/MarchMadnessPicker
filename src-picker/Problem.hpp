#ifndef PICKER_PROBLEM_HPP
#define PICKER_PROBLEM_HPP

#include <memory>
#include <string>

#include "Bracket.hpp"
#include "OutputStrategy_Factory.hpp"
#include "ProblemData.hpp"
#include "RandomizationStrategy_Factory.hpp"
#include "SelectionStrategy_Factory.hpp"

namespace picker {

template <class Created> class GenericFactory;

class OutputStrategy;

class RandomizationStrategy;

class SelectionStrategy;

class Problem
{
public:
  explicit Problem(const std::string& inputFileName);

  const ProblemData& getProblemData( ) const;

  void registerOutputStrategyFactory(std::string_view name, std::unique_ptr<GenericFactory<OutputStrategy>>&& factory);

  void createOutputStrategy( );

  std::shared_ptr<OutputStrategy> getOutputStrategy( ) const;

  void registerRandomizationStrategyFactory(std::string_view name,
    std::unique_ptr<GenericFactory<RandomizationStrategy>>&& factory);

  void createRandomizationStrategy( );

  std::shared_ptr<RandomizationStrategy> getRandomizationStrategy( ) const;

  void registerSelectionStrategyFactory(std::string_view name,
    std::unique_ptr<GenericFactory<SelectionStrategy>>&& factory);

  void createSelectionStrategy( );

  std::shared_ptr<SelectionStrategy> getSelectionStrategy( ) const;

  void run( ) const;

private:
  ProblemData problemData{ };

  OutputStrategyFactory outputStrategyFactory{ };
  std::shared_ptr<OutputStrategy> outputStrategy{ };

  RandomizationStrategyFactory randomizationStrategyFactory{ };
  std::shared_ptr<RandomizationStrategy> randomizationStrategy{ };

  SelectionStrategyFactory selectionStrategyFactory{ };
  std::shared_ptr<SelectionStrategy> selectionStrategy{ };
};

}// namespace picker

#endif

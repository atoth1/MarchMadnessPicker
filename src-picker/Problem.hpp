#ifndef PICKER_PROBLEM_HPP
#define PICKER_PROBLEM_HPP

#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "OutputStrategy_Factory.hpp"
#include "ProblemData.hpp"
#include "RandomizationStrategy_Factory.hpp"
#include "SelectionStrategy_Factory.hpp"

namespace picker {

class OutputStrategy;

class SelectionStrategy;

class Problem
{
public:
  explicit Problem(const std::string& inputFileName);

  void registerOutputStrategyFactory(std::string_view name,
    std::unique_ptr<OutputStrategyFactory::FactoryType>&& factory);

  void registerRandomizationStrategyFactory(std::string_view name,
    std::unique_ptr<RandomizationStrategyFactory::FactoryType>&& factory);

  void registerSelectionStrategyFactory(std::string_view name,
    std::unique_ptr<SelectionStrategyFactory::FactoryType>&& factory);

  void setup( );

  void run( ) const;

  std::vector<std::string_view> getRegisteredOutputStrategyNames( ) const;

  std::vector<std::string_view> getRegisteredRandomizationStrategyNames( ) const;

  std::vector<std::string_view> getRegisteredSelectionStrategyNames( ) const;

private:
  void registerStandardStrategyFactories( );

  ProblemData problemData{ };

  OutputStrategyFactory outputStrategyFactory{ };
  RandomizationStrategyFactory randomizationStrategyFactory{ };
  SelectionStrategyFactory selectionStrategyFactory{ };

  std::shared_ptr<OutputStrategy> outputStrategy{ };
  std::shared_ptr<SelectionStrategy> selectionStrategy{ };
};

}// namespace picker

#endif

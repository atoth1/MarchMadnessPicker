#ifndef PICKER_OUTPUT_STRATEGY_STDOUT_HPP
#define PICKER_OUTPUT_STRATEGY_STDOUT_HPP

#include <memory>

#include "GenericFactory.hpp"
#include "OutputStrategy.hpp"
#include "OutputStrategy_Factory.hpp"

namespace picker {

struct Bracket;

class StdOutStrategy : public picker::OutputStrategy
{
public:
  StdOutStrategy( ) = default;

  void writeOutput(const Bracket& bracket) const override;
};

class StdOutStrategyFactory : public OutputStrategyFactory::FactoryType
{
public:
  std::shared_ptr<OutputStrategy> create(const nlohmann::json& params) const override;
};

}// namespace picker

#endif
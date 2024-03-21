#ifndef PICKER_RANDOMIZATION_STRATEGY_STD_RAND_HPP
#define PICKER_RANDOMIZATION_STRATEGY_STD_RAND_HPP

#include <memory>

#include "nlohmann/json_fwd.hpp"

#include "GenericFactory.hpp"
#include "RandomizationStrategy.hpp"
#include "RandomizationStrategy_Factory.hpp"

namespace picker {

class StdRandStrategy : public RandomizationStrategy
{
public:
  StdRandStrategy(unsigned seed);

  double getRandom( ) override;
};

class StdRandStrategyFactory : public RandomizationStrategyFactory::FactoryType
{
public:
  std::shared_ptr<RandomizationStrategy> create(const nlohmann::json& params) const override;
};

}// namespace picker

#endif
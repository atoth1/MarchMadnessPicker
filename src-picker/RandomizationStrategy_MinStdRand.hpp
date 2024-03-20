#ifndef PICKER_RANDOMIZATION_STRATEGY_MINSTD_RAND_HPP
#define PICKER_RANDOMIZATION_STRATEGY_MINSTD_RAND_HPP

#include <memory>
#include <random>

#include "nlohmann/json_fwd.hpp"

#include "GenericFactory.hpp"
#include "RandomizationStrategy.hpp"

namespace picker {

class MinStdRandStrategy : public RandomizationStrategy
{
public:
  explicit MinStdRandStrategy(std::minstd_rand::result_type seed);

  double getRandom( ) override;

private:
  std::minstd_rand generator;

  std::uniform_real_distribution<double> dist;
};

class MinStdRandStrategyFactory : public GenericFactory<RandomizationStrategy>
{
public:
  std::shared_ptr<RandomizationStrategy> create(const nlohmann::json& params) const override;
};

}// namespace picker

#endif
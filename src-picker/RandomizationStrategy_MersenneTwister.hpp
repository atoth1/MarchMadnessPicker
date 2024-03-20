#ifndef PICKER_RANDOMIZATION_STRATEGY_MERSENNE_TWISTER_HPP
#define PICKER_RANDOMIZATION_STRATEGY_MERSENNE_TWISTER_HPP

#include <memory>
#include <random>

#include "nlohmann/json_fwd.hpp"

#include "GenericFactory.hpp"
#include "RandomizationStrategy.hpp"

namespace picker {

class MersenneTwisterStrategy : public RandomizationStrategy
{
public:
  explicit MersenneTwisterStrategy(std::mt19937::result_type seed);

  double getRandom( ) override;

private:
  std::mt19937 generator;

  std::uniform_real_distribution<double> dist;
};

class MersenneTwisterStrategyFactory : public GenericFactory<RandomizationStrategy>
{
public:
  std::shared_ptr<RandomizationStrategy> create(const nlohmann::json& params) const override;
};

}// namespace picker

#endif
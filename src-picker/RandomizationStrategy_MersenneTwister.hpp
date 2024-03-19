#ifndef PICKER_RANDOMIZATION_STRATEGY_MERSENNE_TWISTER_HPP
#define PICKER_RANDOMIZATION_STRATEGY_MERSENNE_TWISTER_HPP

#include <random>

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

}// namespace picker

#endif
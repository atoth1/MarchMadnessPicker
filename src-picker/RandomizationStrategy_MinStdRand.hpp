#ifndef PICKER_RANDOMIZATION_STRATEGY_MINSTD_RAND_HPP
#define PICKER_RANDOMIZATION_STRATEGY_MINSTD_RAND_HPP

#include <random>

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

}// namespace picker

#endif
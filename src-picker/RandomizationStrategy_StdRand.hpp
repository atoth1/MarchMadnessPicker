#ifndef PICKER_RANDOMIZATION_STRATEGY_STD_RAND_HPP
#define PICKER_RANDOMIZATION_STRATEGY_STD_RAND_HPP

#include "RandomizationStrategy.hpp"

namespace picker {

class StdRandStrategy : public RandomizationStrategy
{
public:
  StdRandStrategy(unsigned seed);

  double getRandom( ) override;
};

}// namespace picker

#endif
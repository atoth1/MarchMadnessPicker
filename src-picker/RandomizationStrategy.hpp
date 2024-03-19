#ifndef PICKER_RANDOMIZATION_STRATEGY_HPP
#define PICKER_RANDOMIZATION_STRATEGY_HPP

namespace picker {

class RandomizationStrategy
{
public:
  virtual ~RandomizationStrategy( ) = default;

  RandomizationStrategy(const RandomizationStrategy&) = delete;

  RandomizationStrategy(RandomizationStrategy&&) = delete;

  RandomizationStrategy& operator=(const RandomizationStrategy&) = delete;

  RandomizationStrategy& operator=(RandomizationStrategy&&) = delete;

  virtual double getRandom( ) = 0;

protected:
  RandomizationStrategy( ) = default;
};

}// namespace picker

#endif
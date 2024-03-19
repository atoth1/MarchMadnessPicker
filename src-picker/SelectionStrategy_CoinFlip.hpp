#ifndef PICKER_SELECTION_STRATEGY_COIN_FLIP_HPP
#define PICKER_SELECTION_STRATEGY_COIN_FLIP_HPP

#include <memory>
#include <string>

#include "SelectionStrategy.hpp"

namespace picker {

class RandomizationStrategy;

class CoinFlipStrategy : public SelectionStrategy
{
public:
  explicit CoinFlipStrategy(std::unique_ptr<RandomizationStrategy>&& inRand);

  std::string selectWinner(const std::string& team1, const std::string& team2) const override;

private:
  static constexpr double THRESH = 0.5;

  std::unique_ptr<RandomizationStrategy> rand;
};

}// namespace picker

#endif
#ifndef PICKER_SELECTION_STRATEGY_COIN_FLIP_HPP
#define PICKER_SELECTION_STRATEGY_COIN_FLIP_HPP

#include <memory>
#include <string>

#include "nlohmann/json_fwd.hpp"

#include "GenericFactory.hpp"
#include "SelectionStrategy.hpp"

namespace picker {

class RandomizationStrategy;

class CoinFlipStrategy : public SelectionStrategy
{
public:
  explicit CoinFlipStrategy(const std::shared_ptr<RandomizationStrategy>& inRand);

  std::string selectWinner(const std::string& team1, const std::string& team2) const override;

private:
  static constexpr double THRESH = 0.5;

  std::shared_ptr<RandomizationStrategy> rand;
};

class CoinFlipStrategyFactory : public GenericFactory<SelectionStrategy>
{
public:
  explicit CoinFlipStrategyFactory(const std::shared_ptr<RandomizationStrategy>& inRand);

  std::shared_ptr<SelectionStrategy> create(const nlohmann::json& params) const override;

private:
  std::shared_ptr<RandomizationStrategy> rand;
};

}// namespace picker

#endif

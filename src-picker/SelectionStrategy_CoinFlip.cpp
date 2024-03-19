#include <memory>
#include <string>
#include <utility>

#include "RandomizationStrategy.hpp"
#include "SelectionStrategy_CoinFlip.hpp"

picker::CoinFlipStrategy::CoinFlipStrategy(std::unique_ptr<RandomizationStrategy>&& inRand) : rand(std::move(inRand)) {}

std::string picker::CoinFlipStrategy::selectWinner(const std::string& team1, const std::string& team2)
{
  return rand->getRandom( ) < THRESH ? team1 : team2;
}
#ifndef PICKER_TEST_UTILS_HPP
#define PICKER_TEST_UTILS_HPP

#include <string>

#include "BracketData.hpp"
#include "RandomizationStrategy.hpp"
#include "SelectionStrategy.hpp"

class DeterministicStrategy : public picker::RandomizationStrategy
{
public:
  explicit DeterministicStrategy(double inVal);

  double getRandom( ) override;

private:
  double val;
};

class LexicographicCompareStrategy : public picker::SelectionStrategy
{
public:
  LexicographicCompareStrategy( ) = default;

  std::string selectWinner(const std::string& team1, const std::string& team2) const override;
};

picker::BracketData getTestBracketData( );

#endif
#ifndef PICKER_TEST_UTILS_HPP
#define PICKER_TEST_UTILS_HPP

#include <string>

// #include "OutputStrategy.hpp"
#include "RandomizationStrategy.hpp"
#include "SelectionStrategy.hpp"

/*class StringOutputStrategy : public picker::OutputStrategy
{
public:
  StringOutputStrategy( ) = default;

  void writeOutput( ) override;

  std::string getOutput( ) const { return output; };

private:
  std::string output{ };
};*/

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

  std::string selectWinner(const std::string& team1, const std::string& team2) override;
};

#endif
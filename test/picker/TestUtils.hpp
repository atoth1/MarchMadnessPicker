#ifndef PICKER_TEST_UTILS_HPP
#define PICKER_TEST_UTILS_HPP

#include <sstream>
#include <string>

#include "nlohmann/json_fwd.hpp"

#include "BracketData.hpp"
#include "GenericFactory.hpp"
#include "OutputStrategy.hpp"
#include "OutputStrategy_Factory.hpp"
#include "RandomizationStrategy.hpp"
#include "RandomizationStrategy_Factory.hpp"
#include "SelectionStrategy.hpp"
#include "SelectionStrategy_Factory.hpp"

namespace picker {
struct Bracket;
}

picker::BracketData getTestBracketData( );

std::string getExpectedOutput( );

class StringstreamOutStrategy : public picker::OutputStrategy
{
public:
  explicit StringstreamOutStrategy(std::shared_ptr<std::ostringstream> inOut);

  void writeOutput(const picker::Bracket& bracket) const override;

private:
  std::shared_ptr<std::ostringstream> out{ };
};

class StringstreamOutStrategyFactory : public picker::OutputStrategyFactory::FactoryType
{
public:
  explicit StringstreamOutStrategyFactory(std::shared_ptr<std::ostringstream> inOut);

  std::shared_ptr<picker::OutputStrategy> create(const nlohmann::json& params) const override;

private:
  std::shared_ptr<std::ostringstream> out{ };
};

class DeterministicStrategy : public picker::RandomizationStrategy
{
public:
  explicit DeterministicStrategy(double inVal);

  double getRandom( ) override;

private:
  double val;
};

class DeterministicStrategyFactory : public picker::RandomizationStrategyFactory::FactoryType
{
public:
  std::shared_ptr<picker::RandomizationStrategy> create(const nlohmann::json& params) const override;
};

class LexicographicCompareStrategy : public picker::SelectionStrategy
{
public:
  std::string selectWinner(const std::string& team1, const std::string& team2) const override;
};

class LexicographicCompareStrategyFactory : public picker::SelectionStrategyFactory::FactoryType
{
public:
  using RandomizationStrategyPtr = picker::SelectionStrategyFactory::RandomizationStrategyPtr;

  using TeamDataLookupPtr = picker::SelectionStrategyFactory::TeamDataLookupPtr;

  std::shared_ptr<picker::SelectionStrategy> create(const nlohmann::json& params,
    const RandomizationStrategyPtr& randomizationStrategy,
    const TeamDataLookupPtr& teamDataLookup) const override;
};

#endif

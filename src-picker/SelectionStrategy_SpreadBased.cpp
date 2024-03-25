#include <memory>
#include <string>
#include <utility>

#include "nlohmann/json.hpp"// NOLINT(misc-include-cleaner)

#include "RandomizationStrategy.hpp"// NOLINT(misc-include-cleaner)
#include "SelectionStrategy.hpp"
#include "SelectionStrategy_SpreadBased.hpp"
#include "TeamData.hpp"

picker::SpreadBasedStrategy::SpreadBasedStrategy(RandomizationStrategyPtr inRand, TeamDataLookupPtr inTeamDataLookup)
  : rand(std::move(inRand)), teamDataLookup(std::move(inTeamDataLookup))
{}

namespace {
// NOLINTBEGIN(*-magic-numbers)
double computePredictedSpread(const picker::TeamData& favorite, const picker::TeamData& underdog)
{
  const double predictedPossessions = 0.5 * (favorite.adjTempo + underdog.adjTempo);
  const double predictedSpreadFor100Possessions = favorite.adjEff - underdog.adjEff;
  return predictedSpreadFor100Possessions * predictedPossessions / 100;
}

double computeWinProbability(const double predictedSpread)// NOLINT(readability-function-cognitive-complexity)
{
  // I completely forget where I got data for this from, but it's a linear fit
  // based on some data somewhere.
  if (predictedSpread < 1.) {
    return 0.5 + 0.0193 * predictedSpread;
  } else if (predictedSpread < 2.) {
    return 0.5193 + 0.0363 * (predictedSpread - 1.);
  } else if (predictedSpread < 3.) {
    return 0.5556 + 0.0591 * (predictedSpread - 2.);
  } else if (predictedSpread < 4.) {
    return 0.6147 + 0.0241 * (predictedSpread - 3.);
  } else if (predictedSpread < 5.) {
    return 0.6388 + 0.0366 * (predictedSpread - 4.);
  } else if (predictedSpread < 6.) {
    return 0.6754 + 0.0397 * (predictedSpread - 5.);
  } else if (predictedSpread < 7.) {
    return 0.7151 + 0.0355 * (predictedSpread - 6.);
  } else if (predictedSpread < 8.) {
    return 0.7506 + 0.0188 * (predictedSpread - 7.);
  } else if (predictedSpread < 9.) {
    return 0.7694 + 0.0384 * (predictedSpread - 8.);
  } else if (predictedSpread < 10.) {
    return 0.8078 + 0.0238 * (predictedSpread - 9.);
  } else if (predictedSpread < 11.) {
    return 0.8316 + 0.0355 * (predictedSpread - 10.);
  } else if (predictedSpread < 12.) {
    return 0.8671 + 0.0121 * (predictedSpread - 11.);
  } else if (predictedSpread < 13.) {
    return 0.8792 + 0.0201 * (predictedSpread - 12.);
  } else if (predictedSpread < 14.) {
    return 0.8872 + 0.0331 * (predictedSpread - 13.);
  } else if (predictedSpread < 15.) {
    return 0.9203 + 0.0251 * (predictedSpread - 14.);
  } else if (predictedSpread < 16.) {
    return 0.9454 + 0.0204 * (predictedSpread - 15.);
  } else if (predictedSpread < 17.) {
    return 0.9658 - 0.0179 * (predictedSpread - 16.);
  } else if (predictedSpread < 18.) {
    return 0.9479 + 0.0198 * (predictedSpread - 17.);
  } else if (predictedSpread < 19.) {
    return 0.9677 + 0.0156 * (predictedSpread - 18.);
  } else if (predictedSpread < 20.) {
    return 0.9833 - 0.0045 * (predictedSpread - 19.);
  } else if (predictedSpread < 21.) {
    return 0.9788 - 0.0061 * (predictedSpread - 20.);
  } else if (predictedSpread < 22.) {
    return 0.9727 + 0.0059 * (predictedSpread - 21.);
  } else if (predictedSpread < 23.) {
    return 0.9786 + 0.0133 * (predictedSpread - 22.);
  } else if (predictedSpread < 24.) {
    return 0.9919 + 0.0081 * (predictedSpread - 23.);
  }
  return 0.9999;
}
// NOLINTEND(*-magic-numbers)

}// namespace

std::string picker::SpreadBasedStrategy::selectWinner(const std::string& team1, const std::string& team2) const
{
  const picker::TeamData& data1 = teamDataLookup->at(team1);
  const picker::TeamData& data2 = teamDataLookup->at(team2);
  const bool team1Favored = data1.adjEff >= data2.adjEff;
  const picker::TeamData& favorite = team1Favored ? data1 : data2;
  const picker::TeamData& underdog = team1Favored ? data2 : data1;
  const double predictedSpread = computePredictedSpread(favorite, underdog);
  return rand->getRandom( ) < computeWinProbability(predictedSpread) ? favorite.teamName : underdog.teamName;
}

std::shared_ptr<picker::SelectionStrategy> picker::SpreadBasedStrategyFactory::create(
  const nlohmann::json& /*params*/,// NOLINT(misc-include-cleaner)
  const RandomizationStrategyPtr& randomizationStrategy,
  const TeamDataLookupPtr& teamDataLookup) const
{
  return std::make_shared<SpreadBasedStrategy>(randomizationStrategy, teamDataLookup);
}

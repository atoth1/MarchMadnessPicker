#ifndef PICKER_BRACKET_HPP
#define PICKER_BRACKET_HPP

#include <array>
#include <memory>
#include <ostream>
#include <string>
#include <variant>

#include "BracketData.hpp"

namespace picker {

class SelectionStrategy;

class Matchup
{
public:
  Matchup(const std::string& team1, const std::string& team2, const std::shared_ptr<SelectionStrategy>& inStrategy)
    : child1(team1), child2(team2), strategy(inStrategy)
  {}

  Matchup(const std::shared_ptr<Matchup>& matchup1,
    const std::shared_ptr<Matchup>& matchup2,
    const std::shared_ptr<SelectionStrategy>& inStrategy)
    : child1(matchup1), child2(matchup2), strategy(inStrategy)
  {}

  std::string getWinner( );

private:
  using child_t = std::variant<std::string, std::shared_ptr<Matchup>>;
  child_t child1{ };
  child_t child2{ };

  std::shared_ptr<SelectionStrategy> strategy{ };
  std::string winner{ };
};

struct Region
{
  static constexpr int ROUND_OF_64_TEAMS = RegionData::N_TEAMS;
  static constexpr int ROUND_OF_64_MATCHUPS = ROUND_OF_64_TEAMS / 2;
  static constexpr int ROUND_OF_32_MATCHUPS = ROUND_OF_64_MATCHUPS / 2;
  static constexpr int SWEET_16_MATCHUPS = ROUND_OF_32_MATCHUPS / 2;

  std::string name{ };
  std::array<std::string, ROUND_OF_64_TEAMS> teams{ };
  std::array<std::shared_ptr<Matchup>, ROUND_OF_64_MATCHUPS> roundOf64{ };
  std::array<std::shared_ptr<Matchup>, ROUND_OF_32_MATCHUPS> roundOf32{ };
  std::array<std::shared_ptr<Matchup>, SWEET_16_MATCHUPS> sweet16{ };
  std::shared_ptr<Matchup> elite8{ };
};

struct Bracket
{
  std::unique_ptr<Region> topLeft{ };
  std::unique_ptr<Region> bottomLeft{ };
  std::unique_ptr<Region> topRight{ };
  std::unique_ptr<Region> bottomRight{ };

  std::shared_ptr<Matchup> leftSemifinal{ };
  std::shared_ptr<Matchup> rightSemifinal{ };
  std::unique_ptr<Matchup> championship{ };
};

Bracket makeBracket(const BracketData& bracketData, const std::shared_ptr<SelectionStrategy>& strategy);

std::ostream& operator<<(std::ostream& out, const Region& region);

std::ostream& operator<<(std::ostream& out, const Bracket& bracket);

}// namespace picker

#endif
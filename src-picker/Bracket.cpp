#include <memory>
// #include <ostream>
#include <string>
#include <variant>

#include "Bracket.hpp"
#include "BracketData.hpp"
#include "SelectionStrategy.hpp"

namespace {
template <class... Ts> struct overloaded : Ts...
{
  using Ts::operator( )...;
};

template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

}// namespace

// NOLINTBEGIN(misc-no-recursion)
std::string picker::Matchup::getWinner( )
{
  if (winner.empty( )) {
    auto visitor = overloaded{ [](const std::string& str) { return str; },
      [](const std::shared_ptr<Matchup>& matchup) { return matchup->getWinner( ); } };
    const auto team1 = std::visit(visitor, child1);
    const auto team2 = std::visit(visitor, child2);
    winner = strategy->selectWinner(team1, team2);
  }
  return winner;
}
// NOLINTEND(misc-no-recursion)

picker::Bracket picker::makeBracket(const BracketData& bracketData, const std::shared_ptr<SelectionStrategy>& strategy)
{
  auto makeRegion = [strategy](std::unique_ptr<Region>& region, const RegionData& regionData) {
    // NOLINTBEGIN
    region = std::make_unique<Region>( );
    region->name = regionData.name;

    region->roundOf64[0] = std::make_shared<Matchup>(regionData.teams[0], regionData.teams[15], strategy);
    region->roundOf64[1] = std::make_shared<Matchup>(regionData.teams[7], regionData.teams[8], strategy);
    region->roundOf64[2] = std::make_shared<Matchup>(regionData.teams[4], regionData.teams[11], strategy);
    region->roundOf64[3] = std::make_shared<Matchup>(regionData.teams[3], regionData.teams[12], strategy);
    region->roundOf64[4] = std::make_shared<Matchup>(regionData.teams[5], regionData.teams[10], strategy);
    region->roundOf64[5] = std::make_shared<Matchup>(regionData.teams[2], regionData.teams[13], strategy);
    region->roundOf64[6] = std::make_shared<Matchup>(regionData.teams[6], regionData.teams[9], strategy);
    region->roundOf64[7] = std::make_shared<Matchup>(regionData.teams[1], regionData.teams[14], strategy);

    region->roundOf32[0] = std::make_shared<Matchup>(region->roundOf64[0], region->roundOf64[1], strategy);
    region->roundOf32[1] = std::make_shared<Matchup>(region->roundOf64[2], region->roundOf64[3], strategy);
    region->roundOf32[2] = std::make_shared<Matchup>(region->roundOf64[4], region->roundOf64[5], strategy);
    region->roundOf32[3] = std::make_shared<Matchup>(region->roundOf64[6], region->roundOf64[7], strategy);

    region->sweet16[0] = std::make_shared<Matchup>(region->roundOf32[0], region->roundOf32[1], strategy);
    region->sweet16[1] = std::make_shared<Matchup>(region->roundOf32[2], region->roundOf32[3], strategy);

    region->elite8 = std::make_shared<Matchup>(region->sweet16[0], region->sweet16[1], strategy);
    // NOLINTEND
  };

  Bracket bracket{ };
  makeRegion(bracket.topLeft, bracketData.topLeft);
  makeRegion(bracket.bottomLeft, bracketData.bottomLeft);
  makeRegion(bracket.topRight, bracketData.topRight);
  makeRegion(bracket.bottomRight, bracketData.bottomRight);
  bracket.leftSemifinal = std::make_shared<Matchup>(bracket.topLeft->elite8, bracket.bottomLeft->elite8, strategy);
  bracket.rightSemifinal = std::make_shared<Matchup>(bracket.topRight->elite8, bracket.bottomRight->elite8, strategy);
  bracket.championship = std::make_unique<Matchup>(bracket.leftSemifinal, bracket.rightSemifinal, strategy);
  return bracket;
}

// std::ostream& picker::operator<<(std::ostream& out, picker::Region& region) {}

/*std::ostream& picker::operator<<(std::ostream& out, picker::Bracket& bracket)
{
  out << bracket.topLeft->name << " Region:\n";
  out << bracket.topLeft << "\n\n";

  out << bracket.bottomLeft << "\n\n";

  out << bracket.topRight << "\n\n";

  out << bracket.bottomRight << "\n\n";*
}*/

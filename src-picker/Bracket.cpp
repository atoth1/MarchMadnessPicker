#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <variant>

#include "fmt/core.h"

#include "Bracket.hpp"
#include "BracketData.hpp"
#include "LogManager.hpp"
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
    // NOLINTBEGIN(*-magic-numbers)
    region = std::make_unique<Region>( );
    region->name = regionData.name;
    region->teams = regionData.teams;
    logDebug(fmt::format("Creating matchups for region: {}", regionData.name));

    logDebug("Creating Round of 64 matchups.");
    region->roundOf64[0] = std::make_shared<Matchup>(regionData.teams[0], regionData.teams[15], strategy);
    region->roundOf64[1] = std::make_shared<Matchup>(regionData.teams[7], regionData.teams[8], strategy);
    region->roundOf64[2] = std::make_shared<Matchup>(regionData.teams[4], regionData.teams[11], strategy);
    region->roundOf64[3] = std::make_shared<Matchup>(regionData.teams[3], regionData.teams[12], strategy);
    region->roundOf64[4] = std::make_shared<Matchup>(regionData.teams[5], regionData.teams[10], strategy);
    region->roundOf64[5] = std::make_shared<Matchup>(regionData.teams[2], regionData.teams[13], strategy);
    region->roundOf64[6] = std::make_shared<Matchup>(regionData.teams[6], regionData.teams[9], strategy);
    region->roundOf64[7] = std::make_shared<Matchup>(regionData.teams[1], regionData.teams[14], strategy);

    logDebug("Creating Round of 32 matchups.");
    region->roundOf32[0] = std::make_shared<Matchup>(region->roundOf64[0], region->roundOf64[1], strategy);
    region->roundOf32[1] = std::make_shared<Matchup>(region->roundOf64[2], region->roundOf64[3], strategy);
    region->roundOf32[2] = std::make_shared<Matchup>(region->roundOf64[4], region->roundOf64[5], strategy);
    region->roundOf32[3] = std::make_shared<Matchup>(region->roundOf64[6], region->roundOf64[7], strategy);

    logDebug("Creating Sweet 16 matchups.");
    region->sweet16[0] = std::make_shared<Matchup>(region->roundOf32[0], region->roundOf32[1], strategy);
    region->sweet16[1] = std::make_shared<Matchup>(region->roundOf32[2], region->roundOf32[3], strategy);

    logDebug("Creating Elite 8 matchup.");
    region->elite8 = std::make_shared<Matchup>(region->sweet16[0], region->sweet16[1], strategy);
    // NOLINTEND(*-magic-numbers)
  };

  Bracket bracket{ };
  makeRegion(bracket.topLeft, bracketData.topLeft);
  makeRegion(bracket.bottomLeft, bracketData.bottomLeft);
  makeRegion(bracket.topRight, bracketData.topRight);
  makeRegion(bracket.bottomRight, bracketData.bottomRight);

  logDebug("Creating Final Four matchups.");
  bracket.leftSemifinal = std::make_shared<Matchup>(bracket.topLeft->elite8, bracket.bottomLeft->elite8, strategy);
  bracket.rightSemifinal = std::make_shared<Matchup>(bracket.topRight->elite8, bracket.bottomRight->elite8, strategy);
  bracket.championship = std::make_unique<Matchup>(bracket.leftSemifinal, bracket.rightSemifinal, strategy);

  logDebug("Filling out bracket.");
  [[maybe_unused]] const auto winner = bracket.championship->getWinner( );

  return bracket;
}

namespace {
constexpr std::string_view pattern{ "{:_^25}\n" };

constexpr std::string_view INDENT{ "                            " };

void writeFinalFour(std::ostream& out, const picker::Bracket& bracket)
{
  out << "Final Four:\n";
  out << fmt::format(pattern, bracket.topLeft->elite8->getWinner( ));
  out << INDENT << fmt::format(pattern, bracket.leftSemifinal->getWinner( ));
  out << fmt::format(pattern, bracket.bottomLeft->elite8->getWinner( ));
  out << INDENT << INDENT << fmt::format(pattern, bracket.championship->getWinner( ));
  out << fmt::format(pattern, bracket.topRight->elite8->getWinner( ));
  out << INDENT << fmt::format(pattern, bracket.rightSemifinal->getWinner( ));
  out << fmt::format(pattern, bracket.bottomRight->elite8->getWinner( ));
}

}// namespace

std::ostream& picker::operator<<(std::ostream& out, const picker::Region& region)
{
  // NOLINTBEGIN(*-magic-numbers)
  out << "Region Name - " << region.name << ":\n";
  out << fmt::format(pattern, region.teams[0]);
  out << INDENT << fmt::format(pattern, region.roundOf64[0]->getWinner( ));
  out << fmt::format(pattern, region.teams[15]);
  out << INDENT << INDENT << fmt::format(pattern, region.roundOf32[0]->getWinner( ));
  out << fmt::format(pattern, region.teams[7]);
  out << INDENT << fmt::format(pattern, region.roundOf64[1]->getWinner( ));
  out << fmt::format(pattern, region.teams[8]);
  out << INDENT << INDENT << INDENT << fmt::format(pattern, region.sweet16[0]->getWinner( ));
  out << fmt::format(pattern, region.teams[4]);
  out << INDENT << fmt::format(pattern, region.roundOf64[2]->getWinner( ));
  out << fmt::format(pattern, region.teams[11]);
  out << INDENT << INDENT << fmt::format(pattern, region.roundOf32[1]->getWinner( ));
  out << fmt::format(pattern, region.teams[3]);
  out << INDENT << fmt::format(pattern, region.roundOf64[3]->getWinner( ));
  out << fmt::format(pattern, region.teams[12]);
  out << INDENT << INDENT << INDENT << INDENT << fmt::format(pattern, region.elite8->getWinner( ));
  out << fmt::format(pattern, region.teams[5]);
  out << INDENT << fmt::format(pattern, region.roundOf64[4]->getWinner( ));
  out << fmt::format(pattern, region.teams[10]);
  out << INDENT << INDENT << fmt::format(pattern, region.roundOf32[2]->getWinner( ));
  out << fmt::format(pattern, region.teams[2]);
  out << INDENT << fmt::format(pattern, region.roundOf64[5]->getWinner( ));
  out << fmt::format(pattern, region.teams[13]);
  out << INDENT << INDENT << INDENT << fmt::format(pattern, region.sweet16[1]->getWinner( ));
  out << fmt::format(pattern, region.teams[6]);
  out << INDENT << fmt::format(pattern, region.roundOf64[6]->getWinner( ));
  out << fmt::format(pattern, region.teams[9]);
  out << INDENT << INDENT << fmt::format(pattern, region.roundOf32[3]->getWinner( ));
  out << fmt::format(pattern, region.teams[1]);
  out << INDENT << fmt::format(pattern, region.roundOf64[7]->getWinner( ));
  out << fmt::format(pattern, region.teams[14]);
  // NOLINTEND(*-magic-numbers)
  return out;
}

std::ostream& picker::operator<<(std::ostream& out, const picker::Bracket& bracket)
{
  out << *bracket.topLeft << '\n';
  out << *bracket.bottomLeft << '\n';
  out << *bracket.topRight << '\n';
  out << *bracket.bottomRight << '\n';
  writeFinalFour(out, bracket);
  return out;
}

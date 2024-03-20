#include <string>

#include "BracketData.hpp"
#include "TestUtils.hpp"

DeterministicStrategy::DeterministicStrategy(const double inVal) : val(inVal) {}

double DeterministicStrategy::getRandom( ) { return val; }

std::string LexicographicCompareStrategy::selectWinner(const std::string& team1, const std::string& team2) const
{
  return team1 < team2 ? team1 : team2;
}

picker::BracketData getTestBracketData( )
{
  return {
    { "Region 1", { "A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1", "I1", "J1", "K1", "L1", "M1", "N1", "O1", "P1" } },
    { "Region 2", { "A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2", "I2", "J2", "K2", "L2", "M2", "N2", "O2", "P2" } },
    { "Region 3", { "A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3", "I3", "J3", "K3", "L3", "M3", "N3", "O3", "P3" } },
    { "Region 4", { "A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4", "I4", "J4", "K4", "L4", "M4", "N4", "O4", "P4" } }
  };
}

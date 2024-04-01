#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

#include "nlohmann/json.hpp"// NOLINT(misc-include-cleaner)

#include "Bracket.hpp"
#include "BracketData.hpp"
#include "OutputStrategy.hpp"
#include "RandomizationStrategy.hpp"
#include "SelectionStrategy.hpp"
#include "TestUtils.hpp"

picker::BracketData getTestBracketData( )
{
  return {
    { "Region 1", { "A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1", "I1", "J1", "K1", "L1", "M1", "N1", "O1", "P1" } },
    { "Region 2", { "A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2", "I2", "J2", "K2", "L2", "M2", "N2", "O2", "P2" } },
    { "Region 3", { "A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3", "I3", "J3", "K3", "L3", "M3", "N3", "O3", "P3" } },
    { "Region 4", { "A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4", "I4", "J4", "K4", "L4", "M4", "N4", "O4", "P4" } }
  };
}

std::string getExpectedOutput( )
{
  return R"(Region Name - Region 1:
___________A1____________
                            ___________A1____________
___________P1____________
                                                        ___________A1____________
___________H1____________
                            ___________H1____________
___________I1____________
                                                                                    ___________A1____________
___________E1____________
                            ___________E1____________
___________L1____________
                                                        ___________D1____________
___________D1____________
                            ___________D1____________
___________M1____________
                                                                                                                ___________A1____________
___________F1____________
                            ___________F1____________
___________K1____________
                                                        ___________C1____________
___________C1____________
                            ___________C1____________
___________N1____________
                                                                                    ___________B1____________
___________G1____________
                            ___________G1____________
___________J1____________
                                                        ___________B1____________
___________B1____________
                            ___________B1____________
___________O1____________

Region Name - Region 2:
___________A2____________
                            ___________A2____________
___________P2____________
                                                        ___________A2____________
___________H2____________
                            ___________H2____________
___________I2____________
                                                                                    ___________A2____________
___________E2____________
                            ___________E2____________
___________L2____________
                                                        ___________D2____________
___________D2____________
                            ___________D2____________
___________M2____________
                                                                                                                ___________A2____________
___________F2____________
                            ___________F2____________
___________K2____________
                                                        ___________C2____________
___________C2____________
                            ___________C2____________
___________N2____________
                                                                                    ___________B2____________
___________G2____________
                            ___________G2____________
___________J2____________
                                                        ___________B2____________
___________B2____________
                            ___________B2____________
___________O2____________

Region Name - Region 3:
___________A3____________
                            ___________A3____________
___________P3____________
                                                        ___________A3____________
___________H3____________
                            ___________H3____________
___________I3____________
                                                                                    ___________A3____________
___________E3____________
                            ___________E3____________
___________L3____________
                                                        ___________D3____________
___________D3____________
                            ___________D3____________
___________M3____________
                                                                                                                ___________A3____________
___________F3____________
                            ___________F3____________
___________K3____________
                                                        ___________C3____________
___________C3____________
                            ___________C3____________
___________N3____________
                                                                                    ___________B3____________
___________G3____________
                            ___________G3____________
___________J3____________
                                                        ___________B3____________
___________B3____________
                            ___________B3____________
___________O3____________

Region Name - Region 4:
___________A4____________
                            ___________A4____________
___________P4____________
                                                        ___________A4____________
___________H4____________
                            ___________H4____________
___________I4____________
                                                                                    ___________A4____________
___________E4____________
                            ___________E4____________
___________L4____________
                                                        ___________D4____________
___________D4____________
                            ___________D4____________
___________M4____________
                                                                                                                ___________A4____________
___________F4____________
                            ___________F4____________
___________K4____________
                                                        ___________C4____________
___________C4____________
                            ___________C4____________
___________N4____________
                                                                                    ___________B4____________
___________G4____________
                            ___________G4____________
___________J4____________
                                                        ___________B4____________
___________B4____________
                            ___________B4____________
___________O4____________

Final Four:
___________A1____________
                            ___________A1____________
___________A2____________
                                                        ___________A1____________
___________A3____________
                            ___________A3____________
___________A4____________
)";
}

StringstreamOutStrategy::StringstreamOutStrategy(std::shared_ptr<std::ostringstream> inOut) : out(std::move(inOut)) {}

void StringstreamOutStrategy::writeOutput(const picker::Bracket& bracket) const { (*out) << bracket; }

StringstreamOutStrategyFactory::StringstreamOutStrategyFactory(std::shared_ptr<std::ostringstream> inOut)
  : out(std::move(inOut))
{}

// NOLINTNEXTLINE(misc-include-cleaner)
std::shared_ptr<picker::OutputStrategy> StringstreamOutStrategyFactory::create(const nlohmann::json& /*params*/) const
{
  return std::make_shared<StringstreamOutStrategy>(out);
}

DeterministicStrategy::DeterministicStrategy(const double inVal) : val(inVal) {}

double DeterministicStrategy::getRandom( ) { return val; }

std::shared_ptr<picker::RandomizationStrategy> DeterministicStrategyFactory::create(
  const nlohmann::json& /*params*/) const// NOLINT(misc-include-cleaner)
{
  constexpr double val = 0.5;
  return std::make_shared<DeterministicStrategy>(val);
}

std::string LexicographicCompareStrategy::selectWinner(const std::string& team1, const std::string& team2) const
{
  return team1 < team2 ? team1 : team2;
}

// NOLINTNEXTLINE(misc-include-cleaner)
std::shared_ptr<picker::SelectionStrategy> LexicographicCompareStrategyFactory::create(const nlohmann::json& /*params*/,
  const RandomizationStrategyPtr& /*randomizationStrategy*/,
  const TeamDataLookupPtr& /*teamDataLookup*/) const
{
  return std::make_shared<LexicographicCompareStrategy>( );
}

void MockLogger::trace(std::string_view /*message*/) { ++countsPtr->trace; }

void MockLogger::debug(std::string_view /*message*/) { ++countsPtr->debug; }

void MockLogger::info(std::string_view /*message*/) { ++countsPtr->info; }

void MockLogger::warning(std::string_view /*message*/) { ++countsPtr->warning; }

void MockLogger::error(std::string_view /*message*/) { ++countsPtr->error; }

void MockLogger::critical(std::string_view /*message*/) { ++countsPtr->critical; }

#ifndef PICKER_PROBLEM_DATA_HPP
#define PICKER_PROBLEM_DATA_HPP

#include <string>
#include <unordered_map>

#include "nlohmann/json.hpp"

#include "BracketData.hpp"
#include "Constants.hpp"
#include "TeamData.hpp"

namespace picker {

struct ProblemData
{
  using TeamDataLookup = std::unordered_map<std::string, TeamData>;

  BracketData bracketData{ };
  TeamDataLookup teamDataLookup{ };

  std::string selectionStrategy{ SPREAD_BASED_STRATEGY_LABEL };
  nlohmann::json selectionStrategyParams{ };

  std::string randomizationStrategy{ MERSENNE_TWISTER_STRATEGY_LABEL };
  nlohmann::json randomizationStrategyParams{ };

  std::string outputStrategy{ STD_OUT_STRATEGY_LABEL };
  nlohmann::json outputStrategyParams{ };

  void validate( ) const;

  bool operator==(const ProblemData&) const noexcept = default;
};

void from_json(const nlohmann::json&, ProblemData&);

}// namespace picker

#endif
#ifndef PICKER_PROBLEM_DATA_HPP
#define PICKER_PROBLEM_DATA_HPP

#include <memory>
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
  std::shared_ptr<TeamDataLookup> teamDataLookup{ };

  std::string selectionStrategy{ SPREAD_BASED_STRATEGY_LABEL };
  nlohmann::json selectionStrategyParams{ };

  std::string randomizationStrategy{ MERSENNE_TWISTER_STRATEGY_LABEL };
  nlohmann::json randomizationStrategyParams{ };

  std::string outputStrategy{ STD_OUT_STRATEGY_LABEL };
  nlohmann::json outputStrategyParams{ };

  void validate( ) const;

  bool operator==(const ProblemData& other) const noexcept;
};

void from_json(const nlohmann::json&, ProblemData&);

}// namespace picker

#endif
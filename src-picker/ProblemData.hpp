#ifndef PICKER_BRACKET_VALIDATOR
#define PICKER_BRACKET_VALIDATOR

#include <optional>
#include <string>
#include <unordered_map>

#include "nlohmann/json_fwd.hpp"

#include "BracketData.hpp"
#include "TeamData.hpp"

namespace picker {

using TeamDataLookup = std::unordered_map<std::string, TeamData>;

struct ProblemData
{
  BracketData bracketData{ };
  TeamDataLookup teamDataLookup{ };

  std::string selectionStrategy{ "spread-based" };
  std::optional<nlohmann::json> selectionStrategyParams{ };

  std::string randomizationStrategy{ "mersenne-twister" };
  std::optional<nlohmann::json> randomizationStrategyParams{ };

  std::string outputStrategy{ "stdout" };
  std::optional<nlohmann::json> outputStrategyParams{ };

  void validate( ) const;

  bool operator==(const ProblemData&) const noexcept = default;
};

void from_json(const nlohmann::json&, ProblemData&);

}// namespace picker

#endif
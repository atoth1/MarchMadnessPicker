#ifndef PICKER_PROBLEM_DATA_HPP
#define PICKER_PROBLEM_DATA_HPP

#include <optional>
#include <string>
#include <unordered_map>

#include "nlohmann/json.hpp"

#include "BracketData.hpp"
#include "RandomizationStrategy_Factory.hpp"
#include "TeamData.hpp"

namespace picker {

struct ProblemData
{
  using TeamDataLookup = std::unordered_map<std::string, TeamData>;

  BracketData bracketData{ };
  TeamDataLookup teamDataLookup{ };

  std::string selectionStrategy{ "spread-based" };
  std::optional<nlohmann::json> selectionStrategyParams{ };

  std::string randomizationStrategy{ RandomizationStrategyFactory::MERSENNE_TWISTER_LABEL };
  std::optional<nlohmann::json> randomizationStrategyParams{ };

  std::string outputStrategy{ "stdout" };
  std::optional<nlohmann::json> outputStrategyParams{ };

  void validate( ) const;

  bool operator==(const ProblemData&) const noexcept = default;
};

void from_json(const nlohmann::json&, ProblemData&);

}// namespace picker

#endif
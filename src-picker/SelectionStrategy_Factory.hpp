#ifndef PICKER_SELECTION_STRATEGY_FACTORY_HPP
#define PICKER_SELECTION_STRATEGY_FACTORY_HPP

#include <memory>
#include <string_view>
#include <unordered_map>

#include "nlohmann/json_fwd.hpp"

#include "ProblemData.hpp"

namespace picker {

template <class Created, class... ArgTypes> class GenericFactory;

class RandomizationStrategy;

class SelectionStrategy;

class SelectionStrategyFactory
{
public:
  using RandomizationStrategyPtr = std::shared_ptr<RandomizationStrategy>;

  using TeamDataLookup = ProblemData::TeamDataLookup;

  using TeamDataLookupPtr = std::shared_ptr<TeamDataLookup>;

  using FactoryType = GenericFactory<SelectionStrategy, RandomizationStrategyPtr, TeamDataLookupPtr>;

  SelectionStrategyFactory( ) = default;

  void setRandomizationStrategy(RandomizationStrategyPtr inRandomizationStrategy);

  void setTeamDataLookup(TeamDataLookupPtr inTeamDataLookup);

  void registerFactory(std::string_view type, std::unique_ptr<FactoryType>&& factory);

  std::shared_ptr<SelectionStrategy> create(std::string_view type, const nlohmann::json& params) const;

private:
  RandomizationStrategyPtr randomizationStrategy{ };

  TeamDataLookupPtr teamDataLookup{ };

  std::unordered_map<std::string_view, std::unique_ptr<FactoryType>> factories{ };
};

}// namespace picker

#endif

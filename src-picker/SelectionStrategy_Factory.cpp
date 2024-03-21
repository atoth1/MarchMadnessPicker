#include <memory>
#include <string_view>
#include <utility>

#include "nlohmann/json.hpp"// NOLINT(misc-include-cleaner)

#include "GenericFactory.hpp"
#include "SelectionStrategy_Factory.hpp"

void picker::SelectionStrategyFactory::setRandomizationStrategy(RandomizationStrategyPtr inRandomizationStrategy)
{
  randomizationStrategy = std::move(inRandomizationStrategy);
}

void picker::SelectionStrategyFactory::setTeamDataLookup(TeamDataLookupPtr inTeamDataLookup)
{
  teamDataLookup = std::move(inTeamDataLookup);
}

void picker::SelectionStrategyFactory::registerFactory(std::string_view type, std::unique_ptr<FactoryType>&& factory)
{
  factories[type] = std::move(factory);
}

std::shared_ptr<picker::SelectionStrategy> picker::SelectionStrategyFactory::create(std::string_view type,
  const nlohmann::json& params) const// NOLINT(misc-include-cleaner)
{
  if (!randomizationStrategy || !teamDataLookup) { return nullptr; }
  if (auto factoryIt = factories.find(type); factoryIt != factories.end( )) {
    return factoryIt->second->create(params, randomizationStrategy, teamDataLookup);
  }
  return nullptr;
}

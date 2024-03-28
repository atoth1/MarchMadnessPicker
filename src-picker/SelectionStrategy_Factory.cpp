#include <memory>
#include <string_view>
#include <utility>

#include "fmt/core.h"
#include "nlohmann/json.hpp"// NOLINT(misc-include-cleaner)

#include "GenericFactory.hpp"
#include "LogManager.hpp"
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
  logDebug(fmt::format("Creating selection strategy {}.", type));
  if (!randomizationStrategy || !teamDataLookup) {
    if (!randomizationStrategy) { logWarning("Randomization strategy is null, returning null."); }
    if (!teamDataLookup) { logWarning("Team data is null, returning null."); }
    return nullptr;
  }
  if (auto factoryIt = factories.find(type); factoryIt != factories.end( )) {
    return factoryIt->second->create(params, randomizationStrategy, teamDataLookup);
  }
  logWarning("Selection strategy is not registered, returning null.");
  return nullptr;
}

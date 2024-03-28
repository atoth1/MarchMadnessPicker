#include <memory>
#include <string_view>
#include <utility>

#include "fmt/core.h"
#include "nlohmann/json.hpp"// NOLINT(misc-include-cleaner)

#include "GenericFactory.hpp"
#include "LogManager.hpp"
#include "RandomizationStrategy_Factory.hpp"

void picker::RandomizationStrategyFactory::registerFactory(std::string_view type,
  std::unique_ptr<FactoryType>&& factory)
{
  factories[type] = std::move(factory);
}

std::shared_ptr<picker::RandomizationStrategy> picker::RandomizationStrategyFactory::create(std::string_view type,
  const nlohmann::json& params) const// NOLINT(misc-include-cleaner)
{
  logDebug(fmt::format("Creating randomization strategy {}.", type));
  if (auto factoryIt = factories.find(type); factoryIt != factories.end( )) {
    return factoryIt->second->create(params);
  }
  logWarning("Randomization strategy is not registered, returning null.");
  return nullptr;
}

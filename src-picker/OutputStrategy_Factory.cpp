#include <memory>
#include <string_view>
#include <utility>

#include "nlohmann/json.hpp"// NOLINT(misc-include-cleaner)

#include "GenericFactory.hpp"
#include "OutputStrategy_Factory.hpp"

void picker::OutputStrategyFactory::registerFactory(std::string_view type,
  std::unique_ptr<GenericFactory<OutputStrategy>>&& factory)
{
  factories[type] = std::move(factory);
}

std::shared_ptr<picker::OutputStrategy> picker::OutputStrategyFactory::create(std::string_view type,
  const nlohmann::json& params) const// NOLINT(misc-include-cleaner)
{
  if (auto factoryIt = factories.find(type); factoryIt != factories.end( )) {
    return factoryIt->second->create(params);
  }
  return nullptr;
}

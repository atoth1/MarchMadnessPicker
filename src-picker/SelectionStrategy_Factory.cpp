#include <memory>
#include <string_view>
#include <utility>

#include "nlohmann/json.hpp"

#include "GenericFactory.hpp"
#include "SelectionStrategy_Factory.hpp"

void picker::SelectionStrategyFactory::registerFactory(std::string_view type,
  std::unique_ptr<GenericFactory<SelectionStrategy>>&& factory)
{
  factories[type] = std::move(factory);
}

std::shared_ptr<picker::SelectionStrategy> picker::SelectionStrategyFactory::create(std::string_view type,
  const nlohmann::json& params) const
{
  if (auto factoryIt = factories.find(type); factoryIt != factories.end( )) {
    return factoryIt->second->create(params);
  }
  return nullptr;
}

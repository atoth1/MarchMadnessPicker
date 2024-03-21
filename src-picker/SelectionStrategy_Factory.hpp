#ifndef PICKER_SELECTION_STRATEGY_FACTORY_HPP
#define PICKER_SELECTION_STRATEGY_FACTORY_HPP

#include <memory>
#include <string_view>
#include <unordered_map>

#include "nlohmann/json_fwd.hpp"

#include "GenericFactory.hpp"

namespace picker {

class SelectionStrategy;

class SelectionStrategyFactory
{
public:
  SelectionStrategyFactory( ) = default;

  void registerFactory(std::string_view type, std::unique_ptr<GenericFactory<SelectionStrategy>>&& factory);

  std::shared_ptr<SelectionStrategy> create(std::string_view type, const nlohmann::json& params) const;

private:
  std::unordered_map<std::string_view, std::unique_ptr<GenericFactory<SelectionStrategy>>> factories{ };
};

}// namespace picker

#endif

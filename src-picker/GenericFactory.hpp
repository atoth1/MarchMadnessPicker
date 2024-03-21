#ifndef PICKER_GENERIC_FACTORY_HPP
#define PICKER_GENERIC_FACTORY_HPP

#include <memory>

#include "nlohmann/json_fwd.hpp"

namespace picker {
template <class Created, class... ArgTypes> class GenericFactory
{
public:
  virtual ~GenericFactory( ) = default;

  GenericFactory(const GenericFactory&) = delete;

  GenericFactory(GenericFactory&&) = delete;

  GenericFactory& operator=(const GenericFactory&) = delete;

  GenericFactory& operator=(GenericFactory&&) = delete;

  virtual std::shared_ptr<Created> create(const nlohmann::json& params, const ArgTypes&... args) const = 0;

protected:
  GenericFactory( ) = default;
};

}// namespace picker

#endif

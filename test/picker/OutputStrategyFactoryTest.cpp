#include <memory>
#include <string_view>

#include "catch2/catch_test_macros.hpp"
#include "nlohmann/json.hpp"

#include "OutputStrategy_Factory.hpp"
#include "OutputStrategy_FileOut.hpp"
#include "OutputStrategy_StdOut.hpp"

TEST_CASE("OutputStrategyFactory - create strategies", "[OutputStrategyFactory]")// NOLINT
{
  picker::OutputStrategyFactory factory{ };
  factory.registerFactory(
    picker::OutputStrategyFactory::FILE_LABEL, std::make_unique<picker::FileOutStrategyFactory>( ));
  factory.registerFactory(
    picker::OutputStrategyFactory::STDOUT_LABEL, std::make_unique<picker::StdOutStrategyFactory>( ));

  // NOLINTBEGIN
  using namespace nlohmann::literals;
  constexpr std::string_view unregisteredFactoryLabel{ "unregistered" };
  const nlohmann::json emptyParams{ };
  const auto fileNameParams = R"({ "file_name": "test-file-name.txt" })"_json;
  CHECK(factory.create(unregisteredFactoryLabel, emptyParams) == nullptr);
  CHECK(std::dynamic_pointer_cast<picker::FileOutStrategy>(
          factory.create(picker::OutputStrategyFactory::FILE_LABEL, emptyParams))
        != nullptr);
  CHECK(std::dynamic_pointer_cast<picker::FileOutStrategy>(
          factory.create(picker::OutputStrategyFactory::FILE_LABEL, fileNameParams))
        != nullptr);
  CHECK(std::dynamic_pointer_cast<picker::StdOutStrategy>(
          factory.create(picker::OutputStrategyFactory::STDOUT_LABEL, emptyParams))
        != nullptr);
  // NOLINTEND
}
#include <memory>
#include <string_view>

#include "catch2/catch_test_macros.hpp"
#include "nlohmann/json.hpp"

#include "Constants.hpp"
#include "OutputStrategy_Factory.hpp"
#include "OutputStrategy_FileOut.hpp"
#include "OutputStrategy_StdOut.hpp"

TEST_CASE("OutputStrategyFactory - create strategies", "[OutputStrategyFactory]")// NOLINT(misc-use-anonymous-namespace)
{
  picker::OutputStrategyFactory factory{ };
  factory.registerFactory(picker::FILE_OUT_STRATEGY_LABEL, std::make_unique<picker::FileOutStrategyFactory>( ));
  factory.registerFactory(picker::STD_OUT_STRATEGY_LABEL, std::make_unique<picker::StdOutStrategyFactory>( ));

  using namespace nlohmann::literals;
  constexpr std::string_view unregisteredFactoryLabel{ "unregistered" };
  const nlohmann::json emptyParams{ };// NOLINT(misc-include-cleaner)
  const auto fileNameParams = R"({ "file_name": "test-file-name.txt" })"_json;
  // NOLINTBEGIN(cppcoreguidelines-avoid-do-while)
  CHECK(factory.create(unregisteredFactoryLabel, emptyParams) == nullptr);
  CHECK(std::dynamic_pointer_cast<picker::FileOutStrategy>(factory.create(picker::FILE_OUT_STRATEGY_LABEL, emptyParams))
        != nullptr);
  CHECK(
    std::dynamic_pointer_cast<picker::FileOutStrategy>(factory.create(picker::FILE_OUT_STRATEGY_LABEL, fileNameParams))
    != nullptr);
  CHECK(std::dynamic_pointer_cast<picker::StdOutStrategy>(factory.create(picker::STD_OUT_STRATEGY_LABEL, emptyParams))
        != nullptr);
  // NOLINTEND(cppcoreguidelines-avoid-do-while)
}

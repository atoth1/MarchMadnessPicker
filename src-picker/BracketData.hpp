#ifndef PICKER_BRACKET_DATA_HPP
#define PICKER_BRACKET_DATA_HPP

#include <array>
#include <string>

#include "nlohmann/json_fwd.hpp"

namespace picker {

struct RegionData
{
  static constexpr int N_TEAMS = 16;
  std::string name{ "Unnamed Region" };
  std::array<std::string, N_TEAMS> teams{ };

  bool operator==(const RegionData&) const noexcept = default;
};

void from_json(const nlohmann::json&, RegionData&);

struct BracketData
{
  RegionData topLeft{ };
  RegionData bottomLeft{ };
  RegionData topRight{ };
  RegionData bottomRight{ };

  bool operator==(const BracketData&) const noexcept = default;
};

void from_json(const nlohmann::json&, BracketData&);

}// namespace picker

#endif

#ifndef PICKER_TEAM_DATA_HPP
#define PICKER_TEAM_DATA_HPP

#include <optional>
#include <string>

#include "nlohmann/json_fwd.hpp"

namespace picker {

struct TeamData
{
  std::string teamName;
  std::optional<int> seed;
  int rank;
  double adjEff;
  double adjOff;
  double adjDef;
  double adjTempo;
  double luck;
  double adjEffSos;
  double adjOffSos;
  double adjDefSos;
  double adjEffSosNc;

  bool operator==(const TeamData&) const noexcept;
};

void from_json(const nlohmann::json&, TeamData&);

}// namespace picker

#endif

#!/usr/bin/env python3

from dataclasses import dataclass

def floatEqual(a: float, b: float) -> bool:
  return abs(a - b) < 1e-9

@dataclass(frozen=True)
class KenpomData:
  team_name: str
  seed: int
  rank: int
  adj_eff: float
  adj_off: float
  adj_def: float
  adj_tempo: float
  luck: float
  adj_eff_sos: float
  adj_off_sos: float
  adj_def_sos: float
  adj_eff_sos_nc: float

  def __eq__(self, other: object) -> bool:
    if (not isinstance(other, KenpomData)):
      return False

    return self.team_name == other.team_name and self.seed == other.seed and self.rank == other.rank and \
      floatEqual(self.adj_eff, other.adj_eff) and floatEqual(self.adj_off, other.adj_off) and \
      floatEqual(self.adj_def, other.adj_def) and floatEqual(self.adj_tempo, other.adj_tempo) and \
      floatEqual(self.luck, other.luck) and floatEqual(self.adj_eff_sos, other.adj_eff_sos) and \
      floatEqual(self.adj_off_sos, other.adj_off_sos) and floatEqual(self.adj_def_sos, other.adj_def_sos) and \
      floatEqual(self.adj_eff_sos_nc, other.adj_eff_sos_nc)


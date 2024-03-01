#!/usr/bin/env python3

from dataclasses import dataclass

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
  
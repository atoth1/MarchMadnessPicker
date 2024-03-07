#!/usr/bin/env python3

import unittest
import json
from json_writer import JsonFileWriter
from kenpom_data import KenpomData

def json_to_kenpom_data(json_dict: dict) -> KenpomData:
  return KenpomData(
    team_name=json_dict["team_name"],
    seed=json_dict["seed"],
    rank=json_dict["rank"],
    adj_eff=json_dict["adj_eff"],
    adj_off=json_dict["adj_off"],
    adj_def=json_dict["adj_def"],
    adj_tempo=json_dict["adj_tempo"],
    luck=json_dict["luck"],
    adj_eff_sos=json_dict["adj_eff_sos"],
    adj_off_sos=json_dict["adj_off_sos"],
    adj_def_sos=json_dict["adj_def_sos"],
    adj_eff_sos_nc=json_dict["adj_eff_sos_nc"]
  )

class TestJsonFileWriter(unittest.TestCase):

  def getTestData(self) -> list[KenpomData]:
    return [KenpomData(
      team_name="Connecticut",
      seed=4,
      rank=1,
      adj_eff=29.86,
      adj_off=120.8,
      adj_def=90.9,
      adj_tempo=66.6,
      luck=-0.056,
      adj_eff_sos=10.39,
      adj_off_sos=109.7,
      adj_def_sos=99.3,
      adj_eff_sos_nc=-1.75
    ), KenpomData(
      team_name="IUPUI",
      seed=None,
      rank=360,
      adj_eff=-22.05,
      adj_off=95.6,
      adj_def=117.7,
      adj_tempo=66.9,
      luck=-0.076,
      adj_eff_sos=-5.79,
      adj_off_sos=102.4,
      adj_def_sos=108.1,
      adj_eff_sos_nc=-7.15
    )]

  def test_writer(self):
    out_file = "test.json"
    writer = JsonFileWriter(out_file, self.getTestData())
    writer.writeOutput()

    with (open(out_file) as json_file):
      data = json.load(json_file, object_hook=json_to_kenpom_data)
      self.assertEqual(sorted(self.getTestData(), key=lambda d: d.team_name), sorted(data, key=lambda d: d.team_name))


if (__name__ == "__main__"):
  unittest.main()
  
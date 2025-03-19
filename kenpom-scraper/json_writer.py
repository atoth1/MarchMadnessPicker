#!/usr/bin/env python3

from abc import ABC, abstractmethod
import json
from kenpom_data import KenpomData


class OutputWriter(ABC):
    @abstractmethod
    def writeOutput(self):
        pass


class JsonFileWriter(OutputWriter):
    def __init__(self, file_name: str, entries: list[KenpomData]):
        super().__init__()
        self._file_name = file_name
        self._entries = entries

    def writeOutput(self):
        with (open(self._file_name, 'w')) as json_file:
            json.dump(self._entries, json_file, indent=2,
                      default=lambda o: o.__dict__)

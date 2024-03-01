#!/usr/bin/env python3

from abc import ABC, abstractmethod
import requests

class HttpException(RuntimeError):
  def __init__(self, message: str):
    super().__init__(message)

class HttpApi(ABC):
  successful_request: int = 200

  @abstractmethod
  def makeRequest(self) -> int:
    pass

  @abstractmethod
  def getText(self) -> str:
    pass

class KenpomHttpApi(HttpApi):
  _base_url: str = "https://kenpom.com/index.php"

  _year_ext: str = "/index.php?y="

  _headers: dict[str, str] = {
    'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.5112.79 Safari/537.36'
  }
  
  def __init__(self, year: int = None) -> None:
    super().__init__()
    self._response = None
    if (year == None):
      self._url = self.__class__._base_url
    else:
      self._url = self.__class__._base_url + self.__class__._year_ext + str(year)

  def makeRequest(self) -> int:
    self._response = requests.get(self._url, headers=self.__class__._headers)
    return self._response.status_code

  def getText(self) -> str:
    if (self._response == None):
      raise HttpException("Request has not yet been made.")
    return self._response.text

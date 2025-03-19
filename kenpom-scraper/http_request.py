#!/usr/bin/env python3

from abc import ABC, abstractmethod
from selenium import webdriver


class HttpException(RuntimeError):
    def __init__(self, message: str):
        super().__init__(message)


class HttpApi(ABC):
    successful_request: int = 200

    failed_request: int = 403

    @abstractmethod
    def makeRequest(self) -> int:
        pass

    @abstractmethod
    def getText(self) -> str:
        pass


class KenpomHttpApi(HttpApi):
    _base_url: str = "https://kenpom.com/index.php"

    _year_ext: str = "?y="

    # _headers: dict[str, str] = {
    #  'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.5112.79 Safari/537.36'
    # }

    def __init__(self, year: int = None) -> None:
        super().__init__()
        self._driver = webdriver.Chrome()
        self._status_code = None
        if (year == None):
            self._url = self.__class__._base_url
        else:
            self._url = self.__class__._base_url + \
                self.__class__._year_ext + str(year)

    def makeRequest(self) -> int:
        self._driver.get(self._url)
        # Can't seem to get a status code from Selenium GET requests, so we'll just assume if the page's source is
        # sufficiently long its fine. As of 3/19/2025 the successful source has length 388,512 and if the response
        # is blocked the response text has length 4534.
        self._status_code = HttpApi.successful_request if len(
            self._driver.page_source) > 10000 else HttpApi.failed_request
        return self._status_code

    def getText(self) -> str:
        if (self._status_code == None):
            raise HttpException("Request has not yet been made.")
        return self._driver.page_source

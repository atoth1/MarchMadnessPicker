#!/usr/bin/env python3

from abc import ABC, abstractmethod
from bs4 import BeautifulSoup
from http_request import HttpApi
from kenpom_data import KenpomData


class HtmlParseException(RuntimeError):
    def __init__(self, message: str):
        super().__init__(message)


class HtmlParser(ABC):
    @abstractmethod
    def getKenpomData(self) -> list[KenpomData]:
        pass


class BeautifulSoupHtmlParser(HtmlParser):
    def __init__(self, httpApi: HttpApi):
        super().__init__()
        self._http_api = httpApi

    def getKenpomData(self) -> list[KenpomData]:
        status = self._http_api.makeRequest()
        if (status != HttpApi.successful_request):
            raise HtmlParseException("Http request failed.")

        data = []
        bs = BeautifulSoup(self._http_api.getText(), "html.parser")
        tables = bs.find_all("tbody")
        for table in tables:
            rows = table.find_all("tr")
            for row in rows:
                cols = row.find_all("td")
                if (len(cols) == 21):
                    # If the team has an NCAA tournament seed, it is appended at the end of the
                    # field representing the team name.
                    if (cols[1].text[-2:].isnumeric()):
                        team_name = cols[1].text[:-3]
                        seed = int(cols[1].text[-2:])
                    elif (cols[1].text[-1:].isnumeric()):
                        team_name = cols[1].text[:-2]
                        seed = int(cols[1].text[-1:])
                    else:
                        team_name = cols[1].text
                        seed = None

                    data.append(KenpomData(
                        team_name=team_name,
                        seed=seed,
                        rank=int(cols[0].text),
                        adj_eff=float(cols[4].text),
                        adj_off=float(cols[5].text),
                        adj_def=float(cols[7].text),
                        adj_tempo=float(cols[9].text),
                        luck=float(cols[11].text),
                        adj_eff_sos=float(cols[13].text),
                        adj_off_sos=float(cols[15].text),
                        adj_def_sos=float(cols[17].text),
                        adj_eff_sos_nc=float(cols[19].text)
                    ))
        return data

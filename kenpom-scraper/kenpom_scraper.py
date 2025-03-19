#!/usr/bin/env python3

from argparse import ArgumentParser
from http_request import KenpomHttpApi
from html_parse import BeautifulSoupHtmlParser
from json_writer import JsonFileWriter


def main():
    parser = ArgumentParser()
    parser.add_argument("-o", "--output_file", type=str, default="kenpom-data.json",
                        help="Path for output JSON file (default kenpom-data.json).")
    parser.add_argument("-y", "--year", type=int,
                        help="Year to fetch data for (most recent is fetched if omitted).")
    args = parser.parse_args()
    JsonFileWriter(args.output_file, BeautifulSoupHtmlParser(
        KenpomHttpApi(args.year)).getKenpomData()).writeOutput()


if (__name__ == "__main__"):
    main()

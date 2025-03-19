#!/usr/bin/env python3

import unittest
from http_request import HttpApi
from http_request import KenpomHttpApi


class TestHttpRequest(unittest.TestCase):

    def test_response(self):
        api = KenpomHttpApi()
        self.assertEqual(api.makeRequest(), HttpApi.successful_request)


if (__name__ == "__main__"):
    unittest.main()

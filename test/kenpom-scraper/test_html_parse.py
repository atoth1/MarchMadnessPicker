#!/usr/bin/env python3

import unittest
from html_parse import BeautifulSoupHtmlParser
from http_request import HttpApi
from kenpom_data import KenpomData


class TestHttpApi(HttpApi):

    def makeRequest(self) -> int:
        return HttpApi.successful_request

    # Reduced page source from 2023 end-of-season
    def getText(self) -> str:
        return """<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<HTML>
<HEAD>
<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1"><script type='text/javascript'>
    $(function() {
        $( 'th' ).tooltip({
            position: {
                my: "center bottom-10",
                at: "center"
            },
            content: function() {
                return $(this).attr('title');
            }
        });
    });
</script>
<style>
    .ui-tooltip {
        background: blue;
        color: white;
        padding: 2px;
        text-align:center;
        line-height: 1.2em;
    }
</style>

<LINK REL=stylesheet TYPE="text/css" HREF="css/rate2.css?1693000918">
<TITLE>2024 Pomeroy College Basketball Ratings</TITLE>

<!-- Google tag (gtag.js) -->
<script async src="https://www.googletagmanager.com/gtag/js?id=G-6DKK0E2CDM"></script>
<script>
  window.dataLayer = window.dataLayer || [];
  function gtag(){dataLayer.push(arguments);}
  gtag('js', new Date());

  gtag('config', 'G-6DKK0E2CDM');
</script>

<!-- try to use css link for google fonts -->
<link rel="stylesheet" type="text/css" href="https://fonts.googleapis.com/css?family=Signika:600,400&text=1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz:%c3%97%C3%A9%c2%b7%C2%A9%20%26%2B%2D%2C%2E%25%27%28%29%2a%7C%95%3F" />

<link rel="Shortcut Icon" type="image/ico" href="assets/favicon.ico?1662440188" />

<LINK REL=stylesheet TYPE='text/css' HREF='css/master2.css?1692999646'>
<style>
    .headline-message {
        background-color: #f5f57b;
        line-height: 1.1em;
        margin: 0 auto 5px auto;
        color: red;
        border: 2px solid red;
        border-radius: 10px;
        max-width: min(90%,550px);
        padding: 2px 0;
    }
</style>

<script src='https://code.jquery.com/jquery-1.11.3.min.js'></script>
<script src='menu.js?1662440188'></script>

</head>

<body>
<div id="wrapper">
<div id="container">

<div id="logged-in">
<div id="login-box">
<span class="mobileHide"><div id="subscribe">
<a href="register-kenpom.php"><img src="assets/subscribe.png" alt="Subscribe!" /></a>
</div>
</span><form id="login" method="POST" action="handlers/login_handler.php">
<input type="email" name="email" placeholder="E-mail"/ required>
<input type="password" name="password" placeholder="Password"/ required>
<input type="submit" name="submit" value="Login!" />
<span class="desktopHide"><br></span><input type="checkbox" name="remember" />Remember me &nbsp;&nbsp;
<a href="forgotpassword.php">Forgot password?</a>
<span class="desktopHide"><a href="register-kenpom.php"><b> | SUBSCRIBE!</b></a></span>
</form>
</div>
    <!-- new navigation bar -->
    <div id="logo-header">
        <div id="tagline-container">
            <div class="icon"><a href="https://doubletakeout.com"><img src="https://kenpom.com/assets/dt_logo.svg" width="30"></a></div>
            <div id="tagline"><h3>ADVANCED ANALYSIS OF COLLEGE BASKETBALL</h3></div>
            <div class="icon">
                <a href="https://kenpom.substack.com"><img src="https://kenpom.com/assets/substack.svg" height="16"></a>
                <a href="https://dunksandthrees.com"><img src="https://kenpom.com/assets/dunksandthrees.svg" height="16"></a>
            </div>
        </div>
        <hr><hr>
    </div> <!-- end logo-header div -->

    <div id="nav2">
                <h1 class="logo"><a href="/"><img src="assets/kenpom_new.png" /></a></h1>
        <nav>
            <a class="burger-nav"><span class="burger-span">&#8801;</span></a>
            <ul id="main-menu">
                <li id="stats-menu" class="stats"><a href="#">Stats</a>
                    <ul>
                        <li><a href="summary.php">Efficiency</a></li>
                        <li><a href="stats.php">Four Factors</a></li>
                        <li><a href="playerstats.php">Player Stats</a></li>
                        <li><a href="pointdist.php">Point Distribution</a></li>
                        <li><a href="height.php">Height/Experience</a></li>
                        <li><a href="teamstats.php">Misc. Team Stats</a></li>
                    </ul>
                </li>
                <li class="fanmatch"><a href="fanmatch.php" title="FanMatch">FanMatch</a></li>
                <li class="universe"><a href="universe.php" title="D-I Universe">D-I Universe</a></li>
                <li id="misc-menu" class="misc"><a href="#">Miscellany</a>
                    <ul>
                        <li><a href="blog">Blog</a></li>
                        <li><a href="game_attrs.php">Game Rankings</a></li>
                        <li><a href="trends.php">D-I Stats Trends</a></li>
                        <li><a href="officials.php">Ref Ratings</a></li>
                        <li><a href="hca.php">Home Court Ratings</a></li>
                        <li><a href="arenas.php">Arena Capacity</a></li>
                        <!-- <li><a href="blog/the-h-u-m-a-n-poll/">H.U.M.A.N. Poll</a></li> -->
                    </ul>
                </li>
                <li class="search">
                    <form action="team.php">
                        <input id="teams" name="team" placeholder="Search teams"/>
                    </form>
                    <form action="history.php">
                        <input id="coaches" name="c" placeholder="Search coaches"/>
                    </form>
                </li>
                <li class="contact"><a href="contact.php" title="Contact">Contact</a></li>
            </ul>
        </nav>
    </div>
    <hr>
    <hr>
</div>

<!-- The content header -->
<div id="content-header">
<h2>2024 Pomeroy <span class="mobileHide">College Basketball </span>Ratings</h2><span class="rank"><a href="blog/ratings-methodology-update">help</a><div id="years-wrapper"><div id="years-container"><a href="/index.php?y=2002">02</a>&sdot;<a href="/index.php?y=2003">03</a>&sdot;<a href="/index.php?y=2004">04</a>&sdot;<a href="/index.php?y=2005">05</a>&sdot;<a href="/index.php?y=2006">06</a>&sdot;<a href="/index.php?y=2007">07</a>&sdot;<a href="/index.php?y=2008">08</a>&sdot;<a href="/index.php?y=2009">09</a>&sdot;<a href="/index.php?y=2010">10</a>&sdot;<a href="/index.php?y=2011">11</a>&sdot;<a href="/index.php?y=2012">12</a>&sdot;<a href="/index.php?y=2013">13</a>&sdot;<a href="/index.php?y=2014">14</a>&sdot;<a href="/index.php?y=2015">15</a>&sdot;<a href="/index.php?y=2016">16</a>&sdot;<a href="/index.php?y=2017">17</a>&sdot;<a href="/index.php?y=2018">18</a>&sdot;<a href="/index.php?y=2019">19</a>&sdot;<a href="/index.php?y=2020">20</a>&sdot;<a href="/index.php?y=2021">21</a>&sdot;<a href="/index.php?y=2022">22</a>&sdot;<a href="/index.php?y=2023">23</a>&sdot;24</div><div id="scrollLeft" class="scrollFadeLeft"></div><div id="scrollRight"></div></div><b><span class="update">Data through games of <a href="fanmatch.php?d=2024-03-06">Wednesday, March 6</a>
<span class='mobileHide'> (5718 games)
</span></span></b></div> <!-- end content-header div -->
<div id="data-area">
<div id='table-wrapper'><table id='ratings-table'>
<thead><tr class="thead1"><th class="hard_left"></th><th class="next_left"></th><th colspan="3"></th><th class='divide' colspan='4'></th><th class='divide' colspan='2'></th><th class='divide' colspan='2'></th><th colspan='6'  class='divide'>Strength of Schedule</th>
<th colspan='2' class='divide'>NCSOS</th></tr>
<tr class='thead2'><th class='hard_left'><a href='/index.php'>Rk</a></th>
<th class="next_left" style="text-align:left"><a href="/index.php?s=TeamName">Team</a></th>
<th class='conf'>Conf</th>
<th class='wl'><a href="/index.php?s=Wins">W</a>-<a href="/index.php?s=Losses">L</a></th>
<th title="Adjusted efficiency margin" id='position1' class='column-sort'><a href="/index.php">AdjEM</a></th>
<th colspan=2 title="Adjusted offensive efficiency: points scored per 100 possessions (adjusted for opponent)" id="position1" class='divide'><a href="/index.php?s=RankAdjOE">AdjO</a></th>
<th colspan=2 title="Adjusted defensive efficiency: points allowed per 100 possessions (adjusted for opponent)" id="position1"><a href="/index.php?s=RankAdjDE">AdjD</a></th>
<th colspan=2 title="Adjusted tempo: possessions per 40 minutes (adjusted for opponent)" id="position1" class='divide'><a href="/index.php?s=RankAdjTempo">AdjT</a></th>
<th colspan=2 title="Luck rating" id="position1" class='divide'><a href="/index.php?s=RankLuck">Luck</a></th>
<th colspan=2 title="Strength of schedule rating" id="position1" class='divide'><a href="/index.php?s=RankSOS">AdjEM</a></th>
<th colspan=2 title="Average AdjOE of opposing offenses" id="position1"><a href="/index.php?s=RankSOSO">OppO</a></th>
<th colspan=2 title="Average AdjDE of opposing defenses" id="position1"><a href="/index.php?s=RankSOSD">OppD</a></th>
<th colspan=2 title="Non-conference strength of schedule rating" id="position1" class='divide'><a href="/index.php?s=RankNCSOS">AdjEM</a></th>
</tr></thead>
<tbody>
<tr>
<td class="hard_left">1</td><td class="next_left"><a href="team.php?team=Connecticut&y=2023">Connecticut</a> <span class="seed">4</span></td><td class='conf'><a href="conf.php?c=BE&y=2023">BE</a></td><td class="wl">31-8</td><td>+29.86</td><td class="td-left divide">120.8</td><td class="td-right"><span class="seed">3</span></td><td class="td-left">90.9</td><td class="td-right"><span class="seed">7</span></td><td class="td-left divide">66.6</td><td class="td-right"><span class="seed">204</span></td><td class="td-left divide">-.056</td><td class="td-right"><span class="seed">304</span></td><td class="td-left divide">+10.39</td><td class="td-right"><span class="seed">17</span></td><td class="td-left">109.7</td><td class="td-right"><span class="seed">29</span></td><td class="td-left">99.3</td><td class="td-right"><span class="seed">14</span></td><td class="td-left divide">-1.75</td><td class="td-right"><span class="seed">208</span></td></tr>
<tr>
<td class="hard_left">360</td><td class="next_left"><a href="team.php?team=IUPUI&y=2023">IUPUI</a></td><td class='conf'><a href="conf.php?c=Horz&y=2023">Horz</a></td><td class="wl">5-27</td><td>-22.05</td><td class="td-left divide">95.6</td><td class="td-right"><span class="seed">334</span></td><td class="td-left">117.7</td><td class="td-right"><span class="seed">360</span></td><td class="td-left divide">66.9</td><td class="td-right"><span class="seed">185</span></td><td class="td-left divide">-.076</td><td class="td-right"><span class="seed">331</span></td><td class="td-left divide">-5.79</td><td class="td-right"><span class="seed">306</span></td><td class="td-left">102.4</td><td class="td-right"><span class="seed">281</span></td><td class="td-left">108.1</td><td class="td-right"><span class="seed">312</span></td><td class="td-left divide">-7.15</td><td class="td-right"><span class="seed">333</span></td></tr>
</tbody>
</table>
</div>
</div> <!-- end data-area div -->
</div>
<div id="team-footer">
&copy; 1999-2024 The Forecast Factory LLC. All rights reserved.
<!--<span class="desktopHide"><br/></span>--><span class="mobileHide">| <a href="terms.php">Terms of Use</a> | <a href="privacy.php">Privacy Policy</a>
	| Stats provided by <a href="https://stats.com">STATS Perform</a><br /></span>
</div></div>
<!-- end wrapper div -->

</body>

<link rel="stylesheet" href="https://code.jquery.com/ui/1.11.0/themes/smoothness/jquery-ui.min.css">
<script type="text/javascript" src="https://code.jquery.com/ui/1.11.0/jquery-ui.min.js"></script>
<script type='text/javascript' src='coach_box.js?1702667430'></script>
</html>"""

    def getExpectedData(self) -> list[KenpomData]:
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


class TestHtmlParse(unittest.TestCase):

    def test_parse(self):
        api = TestHttpApi()
        parser = BeautifulSoupHtmlParser(api)
        self.assertEqual(parser.getKenpomData(), api.getExpectedData())


if (__name__ == "__main__"):
    unittest.main()

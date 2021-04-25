<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

class Vars
{
    static function init_url(string $url)
    {
        Vars::$url_main = $url;
        Vars::$url_events = Vars::$url_main . "/events/";
        Vars::$url_matches = Vars::$url_main . "/matches/";
        Vars::$url_maps = Vars::$url_main . "/stats/matches/mapstatsid/";
        Vars::$url_teams = Vars::$url_main . "/team/";
        Vars::$url_lineup = Vars::$url_main . "/stats/lineup";
        Vars::$url_players = Vars::$url_main . "/stats/players/";
        Vars::$url_news = Vars::$url_main . "/news/";
    }
    
    static public $url_main;
    static public $url_events;
    static public $url_matches;
    static public $url_maps;
    static public $url_teams;
    static public $url_lineup;
    static public $url_players;
    static public $url_news;
}
<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of Map
 *
 * @author Демьян
 */

function Map_From_Database(int $id)
{
    $map = new Map();
    $map->fromDatabase($id);
    return $map;
}

function Map_From_Html(string $link)
{
    $map = new Map();
    $map->fromHtml($link);
    return $map;
}


class LineupInfo
{
    static function fromArray(array $array)
    {
        $info = new LineupInfo();
        $info->lineup = $array['lineup'];
        $info->rounds = $array['rounds'];
        $info->stats = $array['stats'];
        return $info;
    }
    
    function findPlayer(int $id)
    {
        foreach($this->lineup->players as $player)
            if($player->id == $id)
                return $player;
        return false;
    }
    
    public $lineup;
    public $rounds = array();
    public $stats = array();
}


class Map {
    
    function __construct() {
        $this->info = array(
            1 => new LineupInfo(),
            2 => new LineupInfo()
        );
        $this->tops = array();
    }
            
    function fromDatabase(int $id)
    {
        $result = Service::$database->query("SELECT * FROM Maps WHERE id = $id ;");
        $data = $result->fetchAll()[0];
        if(!empty($data))
        {
            $this->id = $data['id'];
            $this->match_id = $data['match_id'];
            $this->event_id = $data['event_id'];
            $this->timepoint = Timepoint::fromString($data['timepoint']);
            $this->location = $data['location'];
            
            comment("Найдены данные о карте (id = $this->id):", true);
            for($i = 1; $i < 3; $i++)
            {
                comment("Найдены данные о команде $i:", true);
                console_indent(2);
                $this->info[$i]->lineup = Lineup_From_Database($data["lineup$i" . "_id"]);
                $this->info[$i]->rounds = explode(" ", $data["rounds$i"]);
                $this->info[$i]->stats = MapStat::findByPlayersAndMap(
                        $this->info[$i]->lineup->players_id(), 
                        $this->id);
                console_indent(-2);
            }
            $this->tops = MapTop::findByMap($this->id);
        }
    }
    
    function fromHtml(string $link)
    {
        $this->checkLink($link);
        comment("Загружаю данные о карте с $link ", true);
        $html = NetworkManager::loadPage($link);
        $page = phpQuery::newDocument($html);
        
        $tp_text = $page->find("div.match-info-box span[data-time-format=yyyy-MM-dd HH:mm]")->text();
        $this->timepoint = Timepoint::fromFormat($tp_text);
        
        $this->location = $this->findLocation($page->find("div.match-info-box")->text());
        
        $frg_lineups = $page->find("table.stats-table");
        $index = 1;
        
        $query = "div[class=col top-players] div[class=most-x-box standard-box]";
        $frg_tops = $page->find($query);
        $this->tops = array();
        comment("Загружаю достижения игроков: ", true);
        console_indent(2);
        foreach($frg_tops as $frg_top_)
        {
            $frg_top = pq($frg_top_);
            $this->tops[] = MapTop_From_Html($frg_top, $this->id);
        }
        console_indent(-2);
        
        foreach($frg_lineups as $frg_lineup_)
        {
            $frg_lineup = pq($frg_lineup_);
            $team_name = $frg_lineup->find("th[class=st-teamname text-ellipsis]")->text();
            $frg_stats = $frg_lineup->find("tbody tr");
            $stats = array();
            $players = array();
            comment("Загружаю статистику игроков команды $team_name: ", true);
            console_indent(2);
            foreach ($frg_stats as $frg_stat_)
            {
                $frg_stat = pq($frg_stat_);
                
                $player_link = $frg_stat->find("td.st-player a")->attr("href");
                $player_id = explode("/", $player_link)[3];
                $player = Player::getPlayer($player_id);
                $players[] = $player;
                $stats[] = MapStat_From_Html($frg_stat, $this->id, $player_id);
            }
            console_indent(-2);
            
            $frg_rounds = $page->find("div.round-history-team-row:has(img[title=$team_name]) "
                    . "img.round-history-outcome");
            $rounds = array();
            foreach ($frg_rounds as $frg_round_)
            {
                $frg_round = pq($frg_round_);
                $type = $frg_round->attr('src');
                switch ($type)
                {
                case "//static.hltv.org/images/scoreboard/ct_win.svg": 
                    $rounds[] = Map::CT_WIN;
                    break;
                case "//static.hltv.org/images/scoreboard/bomb_defused.svg": 
                    $rounds[] = Map::BOMB_DEFUSED;
                    break;
                case "//static.hltv.org/images/scoreboard/stopwatch.svg": 
                    $rounds[] = Map::TIMEOUT;
                    break;
                case "//static.hltv.org/images/scoreboard/t_win.svg": 
                    $rounds[] = Map::T_WIN;
                    break;
                case "//static.hltv.org/images/scoreboard/bomb_exploded.svg": 
                    $rounds[] = Map::BOMB_EXPLODED;
                    break;
                case "//static.hltv.org/images/scoreboard/emptyHistory.svg": 
                    $rounds[] = Map::LOST;
                    break;
                }
            }
            
            $this->info[$index]->lineup = Lineup_From_Data($players, $team_name);
            $this->info[$index]->rounds = $rounds;
            $this->info[$index]->stats = $stats;
            $index++;
        }
        $this->save();
    }
    
    function checkUpdates()
    {
        $this->fromHtml($this->link());
    }
    
    function link()
    {
        return Vars::$url_main . "/stats/matches/mapstatsid/$this->id/match";
    }
    
    function output()
    {
        comment("Данные карты "
                . $this->info[1]->lineup->team_name 
                . " vs " . $this->info[2]->lineup->team_name . ":", true);
        comment("id: $this->id");
        comment("id матча: $this->match_id");
        comment("id события: $this->event_id");
        comment("Локация: $this->location");
        comment("Время начала: " . $this->timepoint->toFormat());
        comment("История раундов 1 состава: " . implode("-", $this->info[1]->rounds));
        comment("История раундов 2 состава: " . implode("-", $this->info[2]->rounds));
        comment("Ссылка: " . $this->link());
        
        console_indent(2);
        comment("Достижения игроков:", true);
        foreach($this->tops as $top)
            $top->output($this->findPlayer($top->player_id)->nick);
        
        $this->info[1]->lineup->output();
        foreach ($this->info[1]->stats as $stat)
            $stat->output($this->info[1]->findPlayer($stat->player_id)->name);
        $this->info[2]->lineup->output();
        foreach ($this->info[2]->stats as $stat)
            $stat->output($this->info[2]->findPlayer($stat->player_id)->name);
        console_indent(-2);
    }
    
    function save()
    {
        if(!$this->exist($this->id))
            $this->insert();
    }
    
    function insert()
    {
        $query = "INSERT INTO "
                . "Maps (id, match_id, event_id, timepoint, location, "
                . "lineup1_id, lineup2_id, rounds1, rounds2) "
                . "VALUES ($this->id, $this->match_id, $this->event_id, "
                . "'" . $this->timepoint->toString() . "', '$this->location', "
                . $this->info[1]->lineup->id . ", " . $this->info[2]->lineup->id . ", "
                . "'" . implode(" ", $this->info[1]->rounds) . "', "
                . "'" . implode(" ", $this->info[2]->rounds) . "');";
        Service::databaseExecute($query);
        comment("Сохраняю информацию о карте");
    }
    
    function delete()
    {
        $query = "DELETE FROM Maps WHERE id = $this->id";
        Service::databaseExecute($query);
        comment("Удаляю информацию о карте");
    }
    
    static function exist(int $id)
    {
        $result = Service::$database->query("SELECT id FROM Maps WHERE id = $id");
        if(empty($result->fetchAll()))
            return false;
        else
            return true;
    }
    
    private function checkLink(&$link)
    {
        $array = explode("/", $link);
        if(count($array) == 8 and $array[3] == "stats" 
                and $array[4] == "matches" and $array[5] == "mapstatsid")
        {
            $this->id = $array[6];
        }
    }
    
    private function findPlayer(int $id)
    {
        foreach ($this->info[1]->lineup->players as $player)
            if($player->id == $id)
                return $player;
        foreach ($this->info[2]->lineup->players as $player)
            if($player->id == $id)
                return $player;
        return false;
    }
    
    private function findLocation(string $str)
    {
        if(strpos($str, "Dust2") != false)
            return "Dust2";
        if(strpos($str, "Nuke") != false)
            return "Nuke";
        if(strpos($str, "Cobblestone") != false)
            return "Cobblestone";
        if(strpos($str, "Tuscan") != false)
            return "Tuscan";
        if(strpos($str, "Cache") != false)
            return "Cache";
        if(strpos($str, "Mirage") != false)
            return "Mirage";
        if(strpos($str, "Train") != false)
            return "Train";
        if(strpos($str, "Overpass") != false)
            return "Overpass";
        if(strpos($str, "Vertigo") != false)
            return "Vertigo";
        if(strpos($str, "Season") != false)
            return "Season";
        if(strpos($str, "Inferno") != false)
            return "Inferno";
        return "Unknown";
    }
    
    
    const CT_WIN = 1;
    const BOMB_DEFUSED = 2;
    const TIMEOUT = 3;
    const T_WIN = 4;
    const BOMB_EXPLODED = 5;
    const LOST = 6;
    
    public $id;
    public $match_id = -1;
    public $event_id = -1;
    public $timepoint;
    public $location;
    public $info;
    public $tops;
}

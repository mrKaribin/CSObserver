<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of Event
 *
 * @author Демьян
 */

function Event_From_Database(int $id)
{
    $event = new Event();
    $event->fromDatabase($id);
    return $event;
}

function Event_From_Html(string $link)
{
    $event = new Event();
    $event->fromHtml($link);
    return $event;
}


class Event {
    
    function fromDatabase(int $id)
    {
        $query = "SELECT * FROM Events WHERE id = $id ;";
        $result = Service::databaseRequest($query);
        $data = $result->fetchAll()[0];
        if(!empty($data))
        {
            $this->id = $id;
            $this->name = $data['name'];
            comment("Найдены данные о событии '$this->name'", true, 2);
            $this->date_begin = $data['date_begin'];
            $this->date_end = $data['date_end'];
            $this->prize = $data['prize'];
            $this->location = $data['location'];
            $this->updated = Timepoint::fromString($data['updated']);
            console_indent(-2);
        }
        else return false;
    }
    
    function fromHtml(string $link)
    {
        $this->id = explode("/", $link)[4];
        
        if(Event::actual($this->id))
        {
            $this->fromDatabase($this->id);
            return;
        }
        
        comment("Загружаю данные о событии с '$link'", true);
        $html = NetworkManager::loadPage($link);
        $page = phpQuery::newDocument($html);
        
        $this->name = $page->find("div.eventname")->text();
        
        $this->prize = $page->find("td[class=prizepool text-ellipsis]")->text();
        
        $this->location = $page->find("td[class=location gtSmartphone-only] "
                . "span.text-ellipsis")->text();
        
        $date = $page->find("td.eventdate")->text();
        $this->decodeDate($date);
        
        $this->lineups = array();
        $frg_teams = $page->find("div[class=teams-attending grid] "
                . "div[class=standard-box team-box]");
        foreach ($frg_teams as $frg_team_)
        {
            $frg_team = pq($frg_team_);
            
            comment("Загружаю данные о команде", true, 2);
            $team_link = Vars::$url_main . $frg_team->find("div.team-name a")->attr("href");
            $team = Team_From_Html($team_link);
            console_indent(-2);
            
            comment("Загружаю данные о составе", true, 2);
            $players = array();
            $frg_players = $frg_team->find("div[class=flag-align player] a");
            foreach ($frg_players as $frg_player)
                $players[] = Player_From_Html(Vars::$url_main . pq($frg_player)->attr('href'));
            $this->lineups[] = Lineup_From_Data($players, $team->name);
            console_indent(-2);
        }
        
        $this->achievements = array();
        $frg_achievements = $page->find("div[class=standard-box placements-holder] "
                . "div.placement");
        comment("Загружаю данные о достижениях", true, 2);
        foreach ($frg_achievements as $frg_achieve_)
        {
            $frg_achieve = pq($frg_achieve_);
            $team_name = $frg_achieve->find("div.team a")->text();
            $lineup = $this->findLineup($team_name, Event::BY_TEAM_NAME);
            $position = $frg_achieve->find("div:eq(1)")->text();
            $prize = $frg_achieve->find("div.prizeMoney")->text();
            $this->achievements[] = Achievement_From_Data($this, $lineup, $position, $prize);
        }
        console_indent(-2);
        
        
        $this->save();
    }
    
    function lineups()
    {
        if($this->lineups == null)
        {
            $result = Service::databaseRequest("SELECT teams FROM Events WHERE id = $this->id ;");
            $this->dataToTeams($result->fetchAll()[0]['teams']);
        }
        return $this->lineups;
    }
    
    function achievements()
    {
        if($this->achievements == null)
            $this->achievements = Achievement::find($this->id, Achievement::BY_EVENT);
        return $this->achievements;
    }
    
    function link()
    {
        return Vars::$url_events . "$this->id/event";
    }
    
    function findLineup($key, int $type = Event::BY_ID)
    {
        switch($type)
        {
            case Event::BY_ID:
                foreach ($this->lineups() as $lineup)
                    if($lineup->id == $key)
                        return $lineup;
                break;
            case Event::BY_TEAM_NAME:
                foreach ($this->lineups() as $lineup)
                    if($lineup->team_name == $key)
                        return $lineup;
                break;
        }
        return false;
    }
    
    function output()
    {
        $link = $this->link();
        comment("Данные события '$this->name':", true);
        comment("id: " . $this->id);
        comment("Название: " . $this->name);
        comment("Призовой фонд: " . $this->prize);
        comment("Локация: " . $this->location);
        comment("Сслыка: $link");
        
        comment("Команды-участники:", false, 2);
        foreach ($this->lineups() as $lineup)
        {
            comment("$lineup->team_name:", true);
            foreach ($lineup->players as $player)
                comment("$player->nick");
        }
        console_indent(-2);
        
        comment("Достижения:", true, 2);
        foreach ($this->achievements() as $achieve)
            comment("$achieve->position: " 
                    . $this->findLineup($achieve->lineup_id)->team_name
                    . " - $achieve->prize");
        console_indent(-2);
    }
    
    function save()
    {
        if(Event::exist($this->id))
            $this->update();
        else
            $this->insert();
    }
    
    function insert()
    {
        $query = "INSERT INTO "
                . "Events (id, name, date_begin, date_end, prize, location, teams, updated) "
                . "VALUES ($this->id, '$this->name', "
                . "'" . $this->date_begin . "', "
                . "'" . $this->date_end . "', "
                . "'$this->prize', '$this->location', "
                . "'" . $this->teamsToData() . "', "
                . "'" . Timepoint::current()->toString() . "' );";
        Service::databaseExecute($query);
        comment("Сохраняю информацию события $this->name");
    }
    
    function update()
    {
        $query = "UPDATE Events SET "
                . "name = '$this->name', "
                . "date_begin = '" . $this->date_begin . "', "
                . "date_end = '" . $this->date_end . "', "
                . "prize = '$this->prize', "
                . "location = '$this->location', "
                . "teams = '" . $this->teamsToData() . "', "
                . "updated = '" . Timepoint::current()->toString() . "' "
                . "WHERE id = $this->id ;";
        Service::databaseExecute($query);
        comment("Обновляю информацию события $this->name");
    }
    
    private function decodeDate(string $date)
    {
        comment("event data: $date");
        $array = explode("-", $date);
        $this->date_begin = $array[0];
        $this->date_end = $array[1];
        if(empty($this->date_begin))
            $this->date_begin = "empty";
        if(empty($this->date_end))
            $this->date_end  = "empty";
    }
    
    private function teamsToData()
    {
        foreach ($this->lineups as $team)
            $result .= $team->id . " ";
        return trim($result);
    }
    
    private function dataToTeams(string $data)
    {
        $this->lineups = array();
        $data = trim($data);
        $teams_id = explode(" ", $data);
        foreach ($teams_id as $team_id)
            $this->lineups[] = Lineup_From_Database($team_id);
    }
    
    static function exist(int $id)
    {
        $result = Service::$database->query("SELECT id FROM Events WHERE id = $id");
        if(empty($result->fetchAll()))
            return false;
        else
            return true;
    }
    
    static function actual(int $id)
    {
        if(!Event::exist($id))
            return false;
        $result = Service::$database->query("SELECT updated FROM Events WHERE id = $id");
        $timepoint = Timepoint::fromString($result->fetchAll()[0]['updated']);
        if(Timepoint::current()->toSeconds() - $timepoint->toSeconds() < Event::$actualityPeriod)
            return true;
        else 
            return false;
    }
    
    static function getLink(int $id)
    {
        return Vars::$url_events . "$id/event";
    }
    
    
    const BY_ID = 1;
    const BY_TEAM_NAME = 2;
    const BY_PLAYER = 3;
    
    static public $actualityPeriod = 3600;
    
    public $id;
    public $name;
    public $date_begin;
    public $date_end;
    public $prize;
    public $location;
    public $updated;
    
    private $achievements = null;
    private $lineups = null;
    private $teams = null;
}

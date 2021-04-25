<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of Team
 *
 * @author Демьян
 */


function Team_From_Database(string $name)
{
    $result = new Team();
    $result->fromDatabase($id);
    return $result;
}

function Team_From_Html(string $link)
{
    $result = new Team();
    $result->fromHtml($link);
    return $result;
}

class Team {
    
    function fromDatabase($key, int $type = Team::INIT_BY_NAME)
    {
        switch($type)
        {
            case Team::INIT_BY_ID:
                $query = "SELECT * FROM Teams WHERE id = $key";
                break;
            case Team::INIT_BY_NAME:
                $query = "SELECT * FROM Teams WHERE name = '$key'";
                break;
        }
        $result = Service::databaseRequest($query);
        $data = $result->fetchAll()[0];
        if(!empty($data))
        {
            $this->name = $data['name'];
            comment("Найдены данные о команде $this->name", true, 2);
            $this->id = $data['id'];
            $this->region = $data['region'];
            $this->ranking = $data['ranking'];
            $this->lineup_id = Lineup_From_Database($data['lineup_id']);
            $this->dataToNews($data['news']);
            $this->updated = Timepoint::fromString($data['updated']);
            console_indent(-2);
        }
    }
    
    function fromHtml($link)
    {
        $this->id = explode("/", $link)[4];
        
        if(Team::actual($this->id))
        {
            $this->fromDatabase($this->id, Team::INIT_BY_ID);
            return;
        }
        
        comment('Загружаю данные о команде с "' . $link . '"', true);
        $html = NetworkManager::loadPage($link);
        $page = phpQuery::newDocument($html);
        
        $frg_header = $page->find('.profile-team-info');
        if(!isNull($frg_header, "fragment_header"))
        {
            $this->name = $frg_header->find('h1')->text();
            $this->region = $frg_header->find('img')->attr("title");
        }
        
        $this->ranking = $page->find(".profile-team-stat a[href=/ranking/teams]")->text();
        $this->ranking = preg_replace('/[^0-9]/', '', $this->ranking);
        
        $players = array();
        $frg_lineup = $page->find("div[class=bodyshot-team g-grid] a.col-custom");
        comment("Загружаю данные о текущем составе:", true, 2);
        foreach($frg_lineup as $player)
        {
            $link = Vars::$url_main . pq($player)->attr('href');
            $players[] = Player_From_Html($link);
        }
        console_indent(-2);
        $this->lineup = Lineup_From_Data($players, $this->name);
        
        $frg_news = $page->find("div#newsBox a.subTab-newsArticle");
        $this->news = array();
        comment("Загружаю новости:", true, 2);
        foreach ($frg_news as $frg_new)
        {
            $news = News_From_Html(Vars::$url_main . pq($frg_new)->attr('href'));
            $this->news[] = $news;
            if(Timepoint::current()->toSeconds() - $news->timepoint->toSeconds() > News::$actualityPeriod)
                break;
        }
        console_indent(-2);
        
        $this->save();
    }
    
    function link()
    {
        return Vars::$url_main . "/team/$this->id/$this->name";
    }
    
    function lineups()
    {
        
    }
    
    function events()
    {
        
    }
    
    function achievements()
    {
       
    }
    
    function output()
    {
        $link = $this->link();
        comment("Данные команды $this->name:", true);
        comment("id: " . $this->id);
        comment("Название: " . $this->name);
        comment("Регион: " . $this->region);
        comment("Рейтинг: " . $this->ranking);
        comment("Сслыка: $link");
        $this->lineup->output();
    }
    
    function save()
    {
        $this->checkData();
        if(Team::exist($this->id))
            $this->update();
        else
            $this->insert();
    }
    
    function insert()
    {
        $query = "INSERT INTO "
                . "Teams (id, name, region, ranking, lineup_id, news, updated) "
                . "VALUES ($this->id, '$this->name', "
                . "'$this->region', $this->ranking, "
                . $this->lineup->id . ", '" . $this->newsToData() . "', "
                . "'" . Timepoint::current()->toString() . "' );";
        Service::databaseExecute($query);
        comment("Сохраняю информацию команды $this->name");
    }
    
    function update()
    {
        $query = "UPDATE Teams SET "
                . "name = '$this->name', "
                . "region = '$this->region', "
                . "ranking = $this->ranking, "
                . "lineup_id = " . $this->lineup->id . ", "
                . "updated = '" . Timepoint::current()->toString() . "' "
                . "WHERE id = $this->id ;";
        Service::databaseExecute($query);
        comment("Обновляю информацию команды $this->name");
    }
    
    private function checkData()
    {
        checkAndReplace($this->name, "", "empty");
        checkAndReplace($this->region, "", "empty");
        checkAndReplace($this->ranking, "", 0);
        checkAndReplace($this->news, "", " ");
    }
    
    private function newsToData()
    {
        foreach($this->news as $new)
            $result .= $new->id . " ";
        return $result;
    }
    
    private function dataToNews(string $data)
    {
        $this->news = array();
        $data = trim($data);
        $news_id = explode(" ", $data);
        foreach ($news_id as $new_id)
            $this->news[] = News_From_Database($new_id);
    }
    
    static function exist(int $id)
    {
        $result = Service::databaseRequest("SELECT * FROM Teams WHERE id = $id");
        if(empty($result->fetchAll()))
            return false;
        else
            return true;
    }
    
    static function actual(int $id)
    {
        if(!Team::exist($id))
            return false;
        $result = Service::databaseRequest("SELECT updated FROM Teams WHERE id = $id");
        $timepoint = Timepoint::fromString($result->fetchAll()[0]['updated']);
        if(Timepoint::current()->toSeconds() - $timepoint->toSeconds() < Event::$actualityPeriod)
            return true;
        else 
            return false;
    }

    
    const INIT_BY_ID = 1;
    const INIT_BY_NAME = 2;
    
    static public $actualityPeriod = 3600;
    
    public $id;
    public $name;
    public $region;
    public $ranking;
    public $lineup;
    public $news;
    public $updated;
}

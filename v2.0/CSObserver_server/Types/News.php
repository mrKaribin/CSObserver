<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of News
 *
 * @author Демьян
 */

function News_From_Database(int $id)
{
    $news = new News();
    $news->fromDatabase($id);
    return $news;
}

function News_From_Html(string $link)
{
    $news = new News();
    $news->fromHtml($link);
    return $news;
}


class News {
    
    function fromDatabase(int $id)
    {
        $result = Service::$database->query("SELECT * FROM News WHERE id = $id");
        $data = $result->fetchAll()[0];
        if(!empty($data))
        {
            $this->id = $id;
            $this->header = $data['header'];
            $this->timepoint = Timepoint::fromString($data['timepoint']);
            comment("Найдена новость '$this->header'", true);
            return true;
        }
        else return false;
    }
    
    function fromHtml(string $link)
    {
        $this->id = explode("/", $link)[4];
        
        if(News::exist($this->id))
        {
            $this->fromDatabase($this->id);
            return;
        }
        
        comment('Загружаю новость с "' . $link . '"', true);
        $html = NetworkManager::loadPage($link);
        $page = phpQuery::newDocument($html);
        
        $this->header = str_replace("'", " ", $page->find("h1.headline")->text());
        
        $str_timepoint = $page->find("div.date")->text();
        $array = explode(" - ", $str_timepoint);
        $arr_date = explode("/", $array[0]);
        $arr_time = explode(":", $array[1]);
        $this->timepoint = new Timepoint(
                $arr_date[2], $arr_date[1], $arr_date[0],
                $arr_time[0], $arr_time[0]);
        
        $this->save();
    }
    
    function link()
    {
        return Vars::$url_news . "$this->id/page";
    }
    
    function save()
    {
        if(!News::exist($this->id))
            $this->insert();
    }
    
    function insert()
    {
        $query = "INSERT INTO "
                . "News (id, header, timepoint) "
                . "VALUES ($this->id, '$this->header', "
                . "'" . $this->timepoint->toString() . "' );";
        Service::databaseExecute($query);
        comment("Сохраняю новость $this->header");
    }
    
    static function exist(int $id)
    {
        $result = Service::$database->query("SELECT * FROM News WHERE id = $id");
        if(empty($result->fetchAll()))
            return false;
        else
            return true;
    }
    
    
    static public $actualityPeriod = 7776000;
    
    public $id;
    public $timepoint;
    public $header;
}

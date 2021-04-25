<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of Player
 *
 * @author Демьян
 */

function Player_From_Database(int $id)
{
    $player = new Player();
    $player->fromDatabase($id);
    return $player;
}

function Player_From_Html(string $link)
{
    $player = new Player();
    $player->fromHtml($link);
    return $player;
}


class Player {
    
    function fromDatabase(int $id)
    {
        $result = Service::databaseRequest("SELECT * FROM Players WHERE id = $id");
        $data = $result->fetchAll()[0];
        if(!empty($data))
        {
            $this->id = $data['id'];
            $this->nick = $data['nickname'];        
            comment("Найдены данные об игроке $this->nick", true);
            $this->name = $data['name'];
            $this->nationality = $data['nationality'];
            $this->age = $data['age'];
        }
    }
    
    function fromHtml(string $link)
    {
        $this->checkLink($link);
        if(Player::actual($this->id))
        {
            $this->fromDatabase($this->id);
            return;
        }
        comment("Загружаю данные об игроке с '$link'", true);
        $html = NetworkManager::loadPage($link);
        $page = phpQuery::newDocument($html);
        
        $frg_header = $page->find("div.summaryShortInfo");
        $this->nick = $frg_header->find("h1[class=summaryNickname text-ellipsis]")->text();
        
        $frg_info = $frg_header->find("div.summaryInfoContainer");
        $this->name = $frg_info->find("div[class=summaryRealname text-ellipsis] div")->text();
        $this->nationality = $frg_info->find("div[class=summaryRealname text-ellipsis] img")->attr("title");
        $this->age = explode(" ", $frg_info->find("div.summaryPlayerAge")->text())[0];
        
        $this->rating_hltv = $page->find("div[class=summaryStatBreakdownRow] "
                . "div:has(div.summaryStatBreakdownSubHeader:contains('Rating')) "
                . "div.summaryStatBreakdownDataValue")->text();

        $this->save();
    }
    
    function link()
    {
        return Vars::$url_main . "/stats/players/$this->id/$this->nick";
    }
    
    function output()
    {
        comment("Данные игрока $this->nick:", true);
        comment("id: $this->id");
        comment("Ник: $this->nick");
        comment("Имя: $this->name");
        comment("Национальность: $this->nationality");
        comment("Возраст: $this->age");
        comment("Рейтинг hltv: $this->rating_hltv");
        comment("Ссылка: " . $this->link());
    }
    
    function save()
    {
        $this->checkData();
        if($this->exist($this->id))
            $this->update();
        else
            $this->insert();
    }
    
    function insert()
    {
        $query = "INSERT INTO "
                . "Players (id, nickname, name, nationality, age, rating_hltv, updated) "
                . "VALUES ($this->id, '$this->nick', '$this->name', "
                . "'$this->nationality', $this->age, $this->rating_hltv, '"
                . Timepoint::current()->toString() . "');";
        Service::databaseExecute($query);
        comment("Сохраняю информацию игрока $this->nick");
    }
    
    function update()
    {
        $query = "UPDATE Players SET "
                . "nickname = '$this->nick', "
                . "name = '$this->name', "
                . "nationality = '$this->nationality', "
                . "age = $this->age, "
                . "rating_hltv = $this->rating_hltv, "
                . "updated = '" . Timepoint::current()->toString() . "' "
                . "WHERE id = $this->id ;";
        Service::databaseExecute($query);
        comment("Обновляю информацию игрока $this->nick");
    }
    
    function delete()
    {
        $query = "DELETE FROM Players WHERE id = $this->id";
        Service::databaseExecute($query);
        comment("Удаляю информацию игрока $this->nick");
    }
    
    private function checkData()
    {
        checkAndReplace($this->nick, "", "empty");
        checkAndReplace($this->name, "", "empty");
        checkAndReplace($this->nationality, "", "empty");
        checkAndReplace($this->age, "", 0);
        checkAndReplace($this->rating_hltv, "", 0);
    }
    
    private function checkLink(&$link)
    {
        $array = explode("/", $link);
        if(count($array) == 6 and $array[3] == "player")
        {
            $this->id = $array[4];
            $link = Vars::$url_main . "/stats/players/$array[4]/$array[5]";
        }
        if(count($array) == 7 and $array[3] == "stats" and $array[4] == "players")
        {
            $this->id = $array[5];
        }
    }
    
    static function getPlayer(int $id)
    {
        if(!Player::exist($id) or !Player::actual($id))
            return Player_From_Html(Player::getLink($id));
        else
            return Player_From_Database($id);
    }
    
    static function exist(int $id)
    {
        $result = Service::databaseRequest("SELECT id FROM Players WHERE id = $id");
        if(empty($result->fetchAll()))
            return false;
        else
            return true;
    }
    
    static function actual(int $id)
    {
        if(!Player::exist($id))
            return false;
        $result = Service::databaseRequest("SELECT updated FROM Players WHERE id = $id");
        $timepoint = Timepoint::fromString($result->fetchAll()[0]['updated']);
        if(Timepoint::current()->toSeconds() - $timepoint->toSeconds() < Player::$actualityPeriod)
            return true;
        else 
            return false;
    }
    
    static function getLink(int $id)
    {
        return Vars::$url_main . "/stats/players/$id/player";
    }
    
    static public $actualityPeriod = 3600;

    public $id;
    public $nick;
    public $name;
    public $nationality;
    public $age;
    public $rating_hltv;
    
}

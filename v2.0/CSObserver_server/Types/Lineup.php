<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of Lineup
 *
 * @author Демьян
 */

function Lineup_From_Database(int $id)
{
    $lineup = new Lineup();
    $lineup->fromDatabase($id);
    return $lineup;
}

function Lineup_From_Data(array $players, string $team_name)
{
    $lineup = new Lineup();
    $lineup->fromData($players, $team_name);
    return $lineup;
}


class Lineup {
    
    function fromDatabase(int $id)
    {
        $result = Service::$database->query("SELECT * FROM Lineups WHERE id = $id");
        $data = $result->fetchAll()[0];
        if(!empty($data))
        {
            $this->id = $id;
            comment("Найден состав команды $team_name", true, 2);
            $this->team_name = $data['team_name'];
            $str_players = $data['players'];
            $this->string_to_players($str_players);
            console_indent(-2);
            return true;
        }
        else return false;
    }
        
    function fromData(array $players, string $team_name)
    {
        if($players != NULL && $team_name != NULL)
        {
            comment("Формирую состав команды $team_name", true);
            $this->team_name = $team_name;
            $this->players = $players;
            $this->save();
        }
    }
    
    function players_id()
    {
        $result = array();
        foreach ($this->players as $player)
            $result[] = $player->id;
        return $result;
    }
    
    function save()
    {
        $players = $this->players_to_string();
        $query = "SELECT * FROM Lineups "
                . "WHERE players = '$players' "
                . "AND team_name = '$this->team_name' ;";
        $result = Service::databaseRequest($query);
        $data = $result->fetchAll();
        if(empty($data))
        {
            $this->insert();
        }
        else
        {
            $this->id = $data[0]['id'];
            $this->update();
        }
    }
    
    function insert()
    {
        $players = $this->players_to_string();
        $query = "INSERT INTO "
                . "Lineups (team_name, players) "
                . "VALUES ('$this->team_name', '$players');";
        Service::databaseExecute($query);
        
        $query = "SELECT id FROM Lineups WHERE rowid=last_insert_rowid();";
        $array = Service::databaseRequest($query)->fetchAll();
        $this->id = $array[0]['id'];
        comment("Сохраняю информацию состава");
    }
    
    function update()
    {
        $players = $this->players_to_string();
        $query = "UPDATE Lineups SET "
                . "team_name = '$this->team_name', "
                . "players = '$players' "
                . "WHERE id = $this->id ;";
        Service::databaseExecute($query);
        comment("Обновляю информацию состава");
    }
    
    function output()
    {
        comment("Данные о составе $this->team_name:", true);
        comment("id: $this->id");
        $players = "";
        foreach($this->players as $player)
            $players .= "<$player->nick> ";
        comment("Список игроков: $players");
    }
    
    private function players_to_string()
    {
        $players_id = array();
        foreach($this->players as $player)
            $players_id[] = $player->id;
        asort($players_id);
        $result = implode("|", $players_id);
        return $result;
    }
    
    private function string_to_players(string $str)
    {
        $players_id = explode("|", $str);
        $this->players = array();
        foreach($players_id as $player_id)
            $this->players[] = Player_From_Database($player_id);
    }
    
    public $id;
    public $team_name;
    public $players;
}

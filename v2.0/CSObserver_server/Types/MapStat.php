<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of MapStat
 *
 * @author Демьян
 */

function MapStat_From_Database($key, int $type = MapStat::INIT_ID)
{
    $stat = new MapStat();
    $stat->fromDatabase($key, $type);
    return $stat;
}

function MapStat_From_Html(phpQueryObject $fragment, int $map_id, int $player_id)
{
    $stat = new MapStat();
    $stat->fromHtml($fragment, $map_id, $player_id);
    return $stat;
}


class MapStat {
    
    function fromDatabase($key, int $type = MapStat::INIT_ID)
    {
        switch ($type)
        {
            case MapStat::INIT_ID:
                $query = "SELECT * FROM MapStats WHERE id = $key";
                break;
            case MapStat::INIT_MAP_PLAYER:
                $query = "SELECT * FROM MapStats WHERE map_id = " . $key['map_id'] 
                    . " AND player_id = " . $key['player_id'] . " ;";
                break;
            default:
                comment("Не удалось загрузить ");
        }
        $data = Service::databaseRequest($query)->fetchAll()[0];
        $this->id = $data['id'];
        $this->map_id = $data['map_id'];
        $this->player_id = $data['player_id'];
        $this->kills = $data['kills'];
        $this->headshots = $data['headshots'];
        $this->deaths = $data['deaths'];
        $this->assists = $data['assists'];
        $this->damagePR = $data['adr'];
        $this->rating_hltv = $data['rating_hltv'];
        comment("Найдена статистика игрока (id = $this->player_id) на карте (id = $this->map_id)");
    }
    
    function fromHtml(phpQueryObject $fragment, int $map_id, int $player_id)
    {
        comment("Загружаю статистику игрока (id = $player_id) на карте (id = $map_id)");
        $this->player_id = $player_id;
        $this->map_id = $map_id;
        $this->kills = explode(" ", $fragment->find("td.st-kills")->text())[0];
        $this->headshots = str_replace(array('(', ')'), '', $fragment->find("td.st-kills span")->text());
        $this->deaths = $fragment->find("td.st-deaths")->text();
        $this->assists = explode(" ", $fragment->find("td.st-assists")->text())[0];
        $this->damagePR = $fragment->find("td.st-adr")->text();
        $this->rating_hltv = $fragment->find("td.st-rating")->text();
        $this->save();
    }
    
    function output(string $player_name = "empty")
    {
        if($player_name == "empty")
            $player_name = $this->player_id;
        comment("$player_name :: (K)$this->kills - (D)$this->deaths - (A)$this->assists "
                . ":: (Headshots)$this->headshots - (ADR)$this->damagePR - (Rating)$this->rating_hltv");
    }
    
    function save()
    {
        if(MapStat::exist(array('map_id' => $this->map_id, 'player_id' => $this->player_id), MapStat::INIT_MAP_PLAYER) === false)
            $this->insert();
    }
    
    function insert()
    {
        $query = "INSERT INTO "
                . "MapStats (map_id, player_id, kills, headshots, deaths, assists, adr, rating_hltv) "
                . "VALUES ($this->map_id, $this->player_id, "
                . "$this->kills, $this->headshots, $this->deaths, "
                . "$this->assists, $this->damagePR, $this->rating_hltv );";
        Service::databaseExecute($query);
        
        $query = "SELECT id FROM MapStats WHERE rowid=last_insert_rowid();";
        $array = Service::databaseRequest($query)->fetchAll();
        $this->id = $array[0]['id'];
        comment("Сохраняю информацию игрока (id = $this->player_id) на карте (id = $this->map_id)");
    }
    
    function delete()
    {
        $query = "DELETE FROM MapStats WHERE id = $this->id";
        Service::databaseExecute($query);
        comment("Удаляю статистику игрока (id = $this->player_id) на карте (id = $this->map_id)");
    }
    
    static function findByMap(int $map_id)
    {
        $query = "SELECT id FROM MapStats WHERE map_id = $map_id";
        $ids = Service::databaseRequest($query)->fetchAll();
        $array = array();
        comment("Поиск статистики игроков на карте (id = $map_id):");
        console_indent(2);
        foreach($ids as $id)
            $array[] = MapStat_From_Database($id);
        console_indent(-2);
        return $array;
    }
    
    static function findByPlayer(int $player_id)
    {
        $query = "SELECT id FROM MapStats WHERE player_id = $player_id";
        $ids = Service::databaseRequest($query)->fetchAll();
        $array = array();
        comment("Поиск статистики игрока по id: $player_id");
        console_indent(2);
        foreach($ids as $id)
            $array[] = MapStat_From_Database($id);
        console_indent(-2);
        return $array;
    }
    
    static function findByPlayersAndMap(array $players_id, int $map_id)
    {
        $where = " WHERE (";
        foreach ($players_id as $player_id)
            $where .= " player_id = $player_id OR";
        $where = substr($where, 0, strlen($where) - 3);
        $where .= " ) AND map_id = $map_id";
        $query = "SELECT id FROM MapStats" . $where . " ;";
        $arr_ids = Service::databaseRequest($query)->fetchAll();
        $array = array();
        comment("Поиск статистики по нескольким игрокам:", true);
        console_indent(2);
        foreach($arr_ids as $id)
            $array[] = MapStat_From_Database($id['id']);
        console_indent(-2);
        return $array;
    }
    
    static function exist($key, int $type = MapStat::INIT_ID)
    {
        $query = "";
        switch ($type)
        {
            case MapStat::INIT_ID:
                $query = "SELECT id FROM MapStats WHERE id = $key ;";
                break;
            case MapStat::INIT_MAP_PLAYER:
                $query = "SELECT id FROM MapStats WHERE map_id = " . $key['map_id'] 
                    . " AND player_id = " . $key['player_id'] . " ;";
                break;
        }
        $result = Service::$database->query($query);
        if(empty($result->fetchAll()))
            return false;
        else
            return true;
    }

    
    const INIT_ID = 1;
    const INIT_MAP_PLAYER = 2;

    public $id;
    public $map_id;
    public $player_id;
    public $kills;
    public $headshots;
    public $deaths;
    public $assists;
    public $damagePR;
    public $rating_hltv;
}

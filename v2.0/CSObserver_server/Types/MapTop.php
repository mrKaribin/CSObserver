<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of MapTop
 *
 * @author Демьян
 */

function MapTop_From_Database($key, int $type = MapTop::INIT_ID)
{
    $top = new MapTop();
    $top->fromDatabase($key, $type);
    return $top;
}

function MapTop_From_Html(phpQueryObject $fragment, int $map_id)
{
    $top = new MapTop();
    $top->fromHtml($fragment, $map_id);
    return $top;
}


class MapTop {
    
    function fromDatabase($key, int $type = MapTop::INIT_ID)
    {
        switch ($type)
        {
            case MapTop::INIT_ID:
                $query = "SELECT * FROM MapTops WHERE id = $key";
                break;
            case MapTop::INIT_MAP_PLAYER:
                $query = "SELECT * FROM MapTops WHERE map_id = " . $key['map_id'] 
                    . " AND player_id = " . $key['player_id'] 
                    . " AND type = '" . $key['type'] . "' ;";
                break;
        }
        $data = Service::databaseRequest($query)->fetchAll()[0];
        $this->id = $data['id'];
        $this->map_id = $data['map_id'];
        $this->player_id = $data['player_id'];
        $this->type = $data['type'];
        $this->value = $data['value'];
        comment("Найдено достижение игрока (id = $this->player_id) на карте (id = $this->map_id)");
    }
    
    function fromHtml(phpQueryObject $fragment, int $map_id)
    {
        $this->map_id = $map_id;
        $this->player_id = explode("/", $fragment->find("div.name a")->attr("href"))[3];
        $this->type = $fragment->find("div.name span.most-x-title")->text();
        $this->value = $fragment->find("span.valueName")->text();
        comment("Загружаю достижение игрока (id = $this->player_id) на карте (id = $map_id)");
        $this->save();
    }
    
    function output(string $player_name = "empty")
    {
        if($player_name == "empty")
            $player_name = $this->player_id;
        comment("$player_name :: $this->type - $this->value");
    }
    
    function save()
    {
        if(!MapTop::exist(array(
                    'map_id' => $this->map_id,
                    'player_id' => $this->player_id,
                    'type' => $this->type), 
                MapTop::INIT_MAP_PLAYER))
            $this->insert();
    }
    
    function insert()
    {
        $query = "INSERT INTO "
                . "MapTops (map_id, player_id, type, value) "
                . "VALUES ($this->map_id, $this->player_id, "
                . "'$this->type', $this->value );";
        Service::databaseExecute($query);
        
        $query = "SELECT id FROM MapTops WHERE rowid=last_insert_rowid();";
        $array = Service::databaseRequest($query)->fetchAll();
        $this->id = $array[0]['id'];
        comment("Сохраняю достижение игрока (id = $this->player_id) на карте (id = $this->map_id)");
    }
    
    static function findByMap(int $map_id)
    {
        $query = "SELECT id FROM MapTops WHERE map_id = $map_id";
        $ids = Service::databaseRequest($query)->fetchAll();
        $array = array();
        comment("Поиск достижений игроков на карте (id = $map_id):", true);
        console_indent(2);
        foreach($ids as $id)
            $array[] = MapTop_From_Database($id['id']);
        console_indent(-2);
        return $array;
    }
    
    static function exist($key, int $type = MapTop::INIT_ID)
    {
        switch ($type)
        {
            case MapTop::INIT_ID:
                $query = "SELECT id FROM MapTops WHERE id = $key";
                break;
            case MapTop::INIT_MAP_PLAYER:
                $query = "SELECT id FROM MapTops WHERE map_id = " . $key['map_id'] 
                    . " AND player_id = " . $key['player_id'] 
                    . " AND type = '" . $key['type'] . "' ;";
                break;
        }
        $result = Service::databaseRequest($query)->fetchAll();
        if(empty($result))
            return false;
        else 
            return true;
    }

    
    const INIT_ID = 1;
    const INIT_MAP_PLAYER = 2;
    
    public $id;
    public $map_id;
    public $player_id;
    public $type;
    public $value;
}

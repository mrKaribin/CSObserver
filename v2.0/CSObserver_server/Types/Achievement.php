<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of Achievement
 *
 * @author Демьян
 */

function Achievement_From_Database(int $id1, int $id2 = -1)
{
    $achievement = new Achievement();
    $achievement->fromDatabase($id1, $id2);
    return $achievement;
}

function Achievement_From_Data(Event $event, Lineup $lineup, string $position, string $prize)
{
    $achievement = new Achievement();
    $achievement->fromData($event, $lineup, $position, $prize);
    return $achievement;
}


class Achievement {
    
    function fromDatabase(int $id1, int $id2 = -1)
    {
        if($id2 == -1)
            $query = "SELECT * FROM Achievements WHERE id = $id1";
        else
            $query = "SELECT * FROM Achievements WHERE event_id = $id1" 
                    . " AND lineup_id = $id2 ;";
        $data = Service::databaseRequest($query)->fetchAll()[0];
        
        $this->id = $data['id'];
        $this->event_id = $data['event_id'];
        $this->lineup_id = $data['lineup_id'];
        $this->position = $data['position'];
        $this->prize = $data['prize'];
        comment("Найдено достижение состава (id = $this->lineup_id) в событии (id = $this->event_id)", true);
    }
    
    function fromData(Event $event, Lineup $lineup, string $position, string $prize)
    {
        if(Achievement::exist($event->id, $lineup->id))
        {
            $this->fromDatabase($event->id, $lineup->id);
            return;
        }
        
        $this->event_id = $event->id;
        $this->lineup_id = $lineup->id;
        $this->position = $position;
        $this->prize = trim($prize);
        if(empty($this->prize))
            $this->prize = "$0";
        comment("Загружаю достижение состава (id = $this->lineup_id) в событии (id = $this->event_id)", true);
        
        $this->save();
    }
    
    function save()
    {
        if(!Achievement::exist($this->event_id, $this->lineup_id))
            $this->insert();
    }
    
    function insert()
    {
        $query = "INSERT INTO "
                . "Achievements (event_id, lineup_id, position, prize) "
                . "VALUES ($this->event_id, $this->lineup_id, "
                . "'$this->position', '$this->prize' );";
        Service::databaseExecute($query);
        
        $query = "SELECT id FROM Achievements WHERE rowid=last_insert_rowid();";
        $array = Service::databaseRequest($query)->fetchAll();
        $this->id = $array[0]['id'];
        comment("Сохраняю достижение состава (id = $this->lineup_id) в событии (id = $this->event_id)");
    }
    
    static function exist(int $event_id, int $lineup_id)
    {
        $query = "SELECT id FROM Achievements WHERE event_id = $event_id"
                . " AND lineup_id = $lineup_id ;";
        $result = Service::$database->query($query);
        if(empty($result->fetchAll()))
            return false;
        else
            return true;
    }
    
    static function find($key, int $type)
    {
        switch($type)
        {
            case Achievement::BY_ID:
                $query = "SELECT id FROM Achievements WHERE id = $key ;";
                break;
            case Achievement::BY_EVENT:
                $query = "SELECT id FROM Achievements WHERE event_id = $key ;";
                break;
            case Achievement::BY_LINEUP:
                $query = "SELECT id FROM Achievements WHERE lineup_id = $key ;";
                break;
        }
        $result = array();
        $datas = Service::databaseRequest($query)->fetchAll();
        foreach ($datas as $data)
            $result[] = Achievement_From_Database($data['id']);
        return $result;
    }
    
    
    const BY_ID = 1;
    const BY_EVENT = 2;
    const BY_LINEUP = 3;
    const BY_EVENTandLINEUP = 4;
    
    public $id;
    public $event_id;
    public $lineup_id;
    public $position;
    public $prize;
}

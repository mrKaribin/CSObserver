<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of Match
 *
 * @author Демьян
 */

class MatchTeamData extends Team
{
    public $score;
}


class Match {

    function fromLive() 
    {
        
    }

    function fromUpcoming(DOMDocument $element) 
    {
        
    }


    public $id;
    public $team1;
    public $team2;
    public $event;
    public $timepoint;
    public $type;
    public $stage;
    public $draft;
    public $status;
}

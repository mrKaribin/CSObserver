<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of Synchronizer
 *
 * @author Демьян
 */

class Synchronizer {
    
    private $page;
    
    function __construct()
    {
        
    }
    
    function reloadMatches()
    {
        $this->page = file_get_html(Vars::$url_main . "/matches");
        $element = $this->page->find('.upcomingMatchesContainer', 0);
        
        $array = $element->find('.upcomingMatch removeBackground oddRowBgColor');
        foreach ($array as $element)
        {
            $match = new Match();
            $match->fromUpcoming($element);
        }
    }
};

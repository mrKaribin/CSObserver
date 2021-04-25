<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of Tester
 *
 * @author Демьян
 */

require_once 'Types/Team.php';

class Tester {
    
    static function testAll()
    {
        Tester::news_test_full();
        sleep(1);
        
        Tester::player_test_full();
        sleep(1);
        
        Tester::team_test_full();
        sleep(1);
        
        Tester::event_test_full();
        sleep(1);
        
        Tester::map_test_full();
        sleep(1);
        
    }
    
    static function news_test_full()
    {
        $className = "News";
        comment("Тестирую класс '$className'", true);
        console_indent(2);
        $news = News_From_Html(Vars::$url_news . "30587/news");
        $news->output();
        console_indent(-2);
        comment("Теcтирование завершено", true);
    }
    
    static function player_test_full()
    {
        $className = "Player";
        comment("Тестирую класс '$className'", true);
        console_indent(2);
        $player = Player_From_Html(Vars::$url_players . "15639/dezon");
        $player->output();
        console_indent(-2);
        comment("Теcтирование завершено", true);
    }
    
    static function team_test_full()
    {
        $className = "Team";
        comment("Тестирую класс '$className'", true);
        console_indent(2);
        $team = Team_From_Html(Vars::$url_teams . "4674/ldlc");
        $team->output(); 
        console_indent(-2);
        comment("Теcтирование завершено", true);
    }
    
    static function event_test_full()
    {
        $className = "Event";
        comment("Тестирую класс '$className'", true);
        console_indent(2);
        $event = Event_From_Html(Vars::$url_events . "5586/event");
        $event->output(); 
        console_indent(-2);
        comment("Теcтирование завершено", true);
    }
    
    static function map_test_full()
    {
        $className = "Map";
        comment("Тестирую класс '$className'", true);
        console_indent(2);
        
        $map = Map_From_Html(Vars::$url_maps . "106378/match");
        $map->output(); 
        
        comment("Загрузка класса '$className' из БД:", true);
        $map = Map_From_Database($map->id);
        $map->output();
        
        console_indent(-2);
        comment("Теcтирование завершено", true);
    }
    
}

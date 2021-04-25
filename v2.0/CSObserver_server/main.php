<?php
/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

require_once 'phpQuery/phpQuery.php';
require_once 'NetworkManager.php';
require_once 'Tester.php';

require_once 'Service/Vars.php';
require_once 'Service/Service.php';
require_once 'Service/Timepoint.php';

require_once 'Types/News.php';
require_once 'Types/Player.php';
require_once 'Types/Lineup.php';
require_once 'Types/Achievement.php';
require_once 'Types/Event.php';
require_once 'Types/Team.php';
require_once 'Types/Map.php';
require_once 'Types/MapStat.php';
require_once 'Types/MapTop.php';


Vars::init_url("https://www.hltv.org");
Service::$database = new PDO('sqlite:database.db');
Service::checkDatabase();

comment("Ожидание команды:", true);
while(($line = trim(fgets(STDIN))) != "exit")
{
    if($line == "")
        continue;
    
    $words = explode(" ", $line);
    
    switch ($words[0])
    {
        case "testing":
            switch($words[1])
            {
                case "all":
                    Tester::testAll();
                    break;
                case "players":
                    Tester::player_test_full();
                    break;
                case "teams":
                    Tester::team_test_full();
                    break;
                case "events":
                    Tester::event_test_full();
                    break;
                case "maps":
                    Tester::map_test_full();
                    break;
                default:
                    comment("Не указан объект тестирования!");
                    break;
            }
            $line = trim(fgets(STDIN));
            break;
        default:
            comment("Команда не распознана");
            $line = trim(fgets(STDIN));
            break;
    }
    //system("CLS");
    comment("Ожидание команды:", true);
}

//Tester::player_test_full();
//Tester::team_test_full();
//Tester::map_test_full();
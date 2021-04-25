<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of NetworkManager
 *
 * @author Демьян
 */

class NetworkManager {
    
    const queryDelay = 1;
    
    static function loadPage(string $link)
    {
        static $lastQuery_time = 0;
        while(true)
        {
            $currTime = microtime(true);
            $interval = $currTime - $lastQuery_time;
            if($lastQuery_time == 0 ||
                $interval >= NetworkManager::queryDelay)
            {
                $ch = curl_init();
                curl_setopt_array($ch, array(
                    CURLOPT_URL => $link,
                    CURLOPT_HEADER => 0,
                    CURLOPT_RETURNTRANSFER => 1,
                    CURLOPT_SSL_VERIFYHOST => FALSE,
                    CURLOPT_SSL_VERIFYPEER => FALSE
                ));
                $html = curl_exec($ch);
                curl_close($ch);
                $lastQuery_time = microtime(true);
                comment("Загружена страница: '$link'");
                return $html;
            }
            else
            {
                $interval = number_format($interval, 2) - 0.01;
                comment("Ожидание. Интервал между запросами: $interval");
                usleep ((NetworkManager::queryDelay - $interval) * 1000000);
            }
        }
    }
    
}

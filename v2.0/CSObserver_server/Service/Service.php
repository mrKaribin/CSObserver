<?php

    
class Service
{   
    public static $console_prefix = "";
    public static $debug = true;
    public static $checkout = true;
    public static $checkout_sql = false;
    public static $database;
    
    static function checkDatabase()
    {
        $result = Service::$database->query("SELECT name FROM sqlite_master WHERE type='table' ORDER BY name");
        $tables = $result->fetchAll();
        if($tables != NULL)
        {
            if(debug || Service::$checkout)
            {
                if(empty($tables))
                    comment("В базе данных нет таблиц!", true);
            }
            if(!in_array("Events", $tables))
            {
                //Service::
            }
            if(!in_array("Matches", $tables))
            {
                //Service::
            }
            if(!in_array("Maps", $tables))
            {
                //Service::
            }
            if(!in_array("Teams", $tables))
            {
                //Service::
            }
            if(!in_array("Lineups", $tables))
            {
                //Service::
            }
            if(!in_array("Players", $tables))
            {
                //Service::
            }
        }
    }
    
    static function databaseRequest($query)
    {
        $result = Service::$database->query($query);
        if($result === false)
        {
            alarm("Не удалось выполнить команду '$query'\n"
                    . "Ошибка: " . Service::$database->errorInfo());
            return false;
        }
        else
        {
            if(Service::$checkout_sql)
                comment("DATABASE REQUEST: " . $query, true);
            return $result;
        }
    }
    
    static function databaseExecute($query)
    {
        if(Service::$database->exec($query) === false)
            alarm("Не удалось выполнить команду '$query'\n"
                    . "Ошибка: " . Service::$database->errorInfo());
        else
        {
            if(Service::$checkout_sql)
                comment("DATABASE REQUEST: " . $query);
        }
    }
    
}
    

function isNull($object, string $name = "object")
{
    if($object == NULL)
    {
        echo $name . " is NULL.\n";
        return true;
    }
    else 
    {
        return false;
    }
}

function checkAndReplace(&$object, $find, $new)
{
    if($object == $find)
        $object = $new;
}

function console_indent(int $size)
{
    $old_size = strlen(Service::$console_prefix);
    $new_size = $old_size + $size;
    Service::$console_prefix = "";
    for($i = 0; $i < $new_size; $i++){
        Service::$console_prefix .= " ";
    }
}

function comment(string $text, bool $newline = false, int $indent = 0)
{
    if(Service::$debug || Service::$checkout)
    {
        if($newline)
            echo "\n";
        echo Service::$console_prefix . $text . "\n";
    }
    if($indent != 0)
        console_indent($indent);
}

function alarm(string $text)
{
    echo "\n!!! " . $text . "\n";
}


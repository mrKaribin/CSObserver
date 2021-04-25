<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of Timepoint
 *
 * @author Демьян
 */


class Time
{
    function copy(Time $time)
    {
        $this->hours = $time->hours;
        $this->minutes = $time->minutes;
        $this->seconds = $time->seconds;
    }
    
    function setTime(int $hours, int $minutes = 0, int $seconds = 0)
    {
        $this->hours = $hours;
        $this->minutes = $minutes;
        $this->seconds = $seconds;
    }
    
    static function fromString(string $str)
    {
        $time = new Time();
        $array = explode(":", $str);
        $time->setTime($array[0], $array[1], $array[2]);
        return $time;
    }
    
    function toString()
    {
        return $result = implode(":", array(
            $this->hours,
            $this->minutes,
            $this->seconds
        ));
    }
    
    static function fromFormat(string $str)
    {
        $time = new Time();
        $array = explode(":", $str);
        $time->setTime($array[0], $array[1]);
        return $time;
    }
    
    function toFormat()
    {
        return "$this->hours:$this->minutes:$this->seconds";
    }
    
    function toSecs()
    {
        $result = $this->seconds;
        $result += $this->minutes * 60;
        $result += $this->hours * 3600;
        return $result;
    }
    
    static function current()
    {
        $time = new Time();
        $time->hours = date("H");
        $time->minutes = date("i");
        $time->seconds = date("s");
        return $time;
    }
    
    
    public $seconds = 0;
    public $minutes = 0;
    public $hours = 0;
}


class Timepoint extends Time
{
    function __construct(int $years = 0, int $months = 0, int $days = 0, int $hours = 0, int $minutes = 0, int $seconds = 0) 
    {
        $this->set($years, $months, $days, $hours, $minutes, $seconds);
    }
            
    function setDate(int $years, int $months = 0, int $days = 0)
    {
        $this->year = $years;
        $this->month = $months;
        $this->day = $days;
    }
    
    function set(int $years, int $months = 0, int $days = 0, int $hours = 0, int $minutes = 0, int $seconds = 0)
    {
        $this->setTime($hours, $minutes, $seconds);
        $this->setDate($years, $months, $days);
    }
    
    static function fromString(string $str)
    {
        $timepoint = new Timepoint();
        $array = explode("|", $str);
        $timepoint->copy(Time::fromString($array[1]));
        $array = explode(".", $array[0]);
        $timepoint->setDate($array[0], $array[1], $array[2]);
        return $timepoint;
    }
    
    function dataToString()
    {
        return $result = implode(".", array(
            $this->year,
            $this->month,
            $this->day
        ));
    }
    
    function toString() 
    {
        return $this->dataToString() . "|" . parent::toString();
    }
    
    static function fromFormat(string $str)
    {
        $timepoint = new Timepoint();
        $array = explode(" ", $str);
        $timepoint->copy(Time::fromFormat($array[1]));
        $array = explode("-", $array[0]);
        $timepoint->setDate($array[0], $array[1], $array[2]);
        return $timepoint;
    }
    
    function toFormat()
    {
        return parent::toFormat() . " $this->day.$this->month.$this->year";
    }
    
    function toSeconds() 
    {
        $result = parent::toSecs();
        $result += $this->day * 86400;
        for($i = 1; $i < $this->month; $i++)
            $result += cal_days_in_month(CAL_GREGORIAN, $i, $this->year) * 86400;
        $result += ($this->year - 1) * 86400 * 365;
        return $result;
    }
    
    static function current() 
    {
        $timepoint = new Timepoint();
        $timepoint->copy(Time::current());
        $timepoint->day = date("j");
        $timepoint->month = date("n");
        $timepoint->year = date("Y");
        return $timepoint;
    }
    
    
    public $day = 0;
    public $month = 0;
    public $year = 0;
}

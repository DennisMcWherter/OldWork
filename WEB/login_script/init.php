<?php
/**
 * Simple _SECURE_ login by Dennis McWherter
 *
 * This is a free script. Under no circumstances does anyone have permission
 * to sell this script!
 *
 * Nothing needs to be touched in this file. For everything to work, however,
 * this must be the first file included!
 *
 */
session_start();

// Now logout if idle for 5 minutes :) (300 seconds)
if(isset($_SESSION['username'])){
  if(time() > $_SESSION['time']+300){
    session_destroy();
    exit;
   }
  $_SESSION['time'] = time(); // Passed the test, renew session time...
}

define("SCRIPT",true); // Define for script..

// Any other definitions below...

?>
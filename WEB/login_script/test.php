<?php
/**
 * Simple _SECURE_ login by Dennis McWherter
 *
 * This is a free script. Under no circumstances does anyone have permission
 * to sell this script!
 *
 * Test script :D
 *
 */
include_once("init.php");

if(!isset($_SESSION['username'])){
  print "You're not logged in... <a href=\"index.php\">index</a>";
  exit;
}

print "Your username is still ".$_SESSION['username']." - success! :)<br /><br />
<a href=\"index.php\">home</a>";

?>
<?php
/**
 * Salt Encryption Tutorial by Dennis McWherter
 *
 * (C) 2009 Dennis McWherter. All Rights Reserved.
 *
 * This is where all of our functions are. Yes a lot of these
 * Some of this stuff is extra nonsense, but makes life a lot
 * more difficult for hackers.
 *
 */
require_once("config.php");
require_once("functions.php");

$login = new Login;

if(!isset($_GET['page'])){
  $_GET['page'] = "index";
}

switch($_GET['page']){
  default:
    if(!$_SESSION['username']){
      print "<form name=\"login\" method=\"post\" action=\"?page=login\">
	<p>User: <input type=\"text\" name=\"user\" /></p>
	<p>Pass: <input type=\"password\" name=\"pass\" /></p>
	<p><input type=\"submit\" value=\"login\" /></p>
	<p><a href=\"?page=register\">Register</a></p></form>";
      exit;
    } else {
      print "Hello ".$_SESSION['username'].",<br /><br />Welcome to a random test site!
	<br /><br />Your password is safe here ;)<br /><br /><a href=\"?page=logout\">logout</a>";
      exit;
    }
  break;
  case 'register':
    if(!isset($_POST['user']) OR !isset($_POST['pass'])){
      print "<p>All fields are required! <i>(If they are not filled out, you will be
	returned to this page!)</i></p><br /><br />
	<form name=\"reg\" method=\"post\" action=\"?page=register\">
	<p>User: <input type=\text\" name=\"user\" /></p>
	<p>Pass: <input type=\"password\" name=\"pass\" /></p>
	<p><input type=\"submit\" value=\"register\" /></p>
	</form>";
      exit;
    } else {
      if(!$login->register($_POST['user'],$_POST['pass'])){
        print "Login failed: Username already in use!";
        exit;
      } else {
        print "Login successful! You can now <a href=\"?page=index\">login</a>!";
        exit;
      }
    }
  break;
  case 'login':
    if(!isset($_POST['user']) OR !isset($_POST['pass'])){
      $_GET['page'] = "index";
    } else {
      $login->login($_POST['user'],$_POST['pass']);
    }
  break;
  case 'logout':
    if(!isset($_SESSION['username'])){
      print "User is not logged in!";
    } else {
      if(session_destroy()){
        print "User logged out successfully!";
      } else {
        print "User could not be logged out!";
      }
    }
  break;
}

?>
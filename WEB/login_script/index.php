<?php
/**
 * Simple _SECURE_ login by Dennis McWherter
 *
 * This is a free script. Under no circumstances does anyone have permission
 * to sell this script!
 *
 */
include_once("init.php"); // This will take care of starting our sessions and all prelim stuff
include_once("functions.php"); // All our functions will just sit in here!

// Define our function class
$login = new Login_Base;

// Well if the user isn't logged in then tell them to do so!
if(!isset($_SESSION['username']) && $_GET['page'] != "register" && !isset($_POST['form'])){
  print "<form name=\"login\" method=\"post\" action=\"?page=login\">
	<p>Username: <input type=\"text\" name=\"user\" /></p>
	<p>Password: <input type=\"password\" name=\"pass\" /></p>
	<p><input type=\"submit\" value=\"login\" /></p>
	<input type=\"hidden\" name=\"form\" value=\"true\" />
	</form>
	<p><a href=\"?page=register\">Register Now!</a></p>";
  exit;
}

// Default everything out :)
if(!isset($_GET['page'])){
  $_GET['page'] = "index";
}

switch(strtolower($_GET['page'])){
  default:
    print "<p>The login has been successful!<br /><br />
    Your username is: ".$_SESSION['username']."<br /><br />
    Please proceed with the following:<br />
    <a href=\"test.php\">Test page 2</a> (Separate page to show that it carries)<br />
    <a href=\"?page=logout\">Logout</a></p>";
  break;
  case 'logout':
    if(session_destroy()){
      print "Successfully logged out!";
      exit;
    } else {
      print "There was an error logging out!";
      exit;
    }
  break;
  case 'register':
    if($_GET['act'] != "go"){
      print "<form name=\"register\" method=\"post\" action=\"?page=register&act=go\">
	     <p>Username: <input type=\"text\" name=\"user\" /></p>
	     <p>Password: <input type=\"password\" name=\"pass\" /></p>
	     <p><input type=\"submit\" value=\"Register\" /></p>
	     </form>";
    } else {
      if($login->register($_POST['user'],$_POST['pass'])){
	print "Registration successful! You can now login!";
      } else {
	print "Registration failed!";
      }
    }
  break;
  case 'login':
    if($login->login($_POST['user'],$_POST['pass'])){
      print "Login successful! Please go back <a href=\"?page=index\">home</a>";
      exit;
    } else {
      print "Login failed!";
      exit;
    }
  break;
}
mysql_close();
?>
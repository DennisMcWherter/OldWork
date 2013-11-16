<?php
/**
 * Simple _SECURE_ login by Dennis McWherter
 *
 * This is a free script. Under no circumstances does anyone have permission
 * to sell this script!
 *
 * Login functions are in here :)
 *
 */
if(!defined("SCRIPT")){
  print "Unauthorized access!";
  exit;
}

class Login_Base{

	/**
	 * Constructor...
	 *
	 */
	function __construct(){
		// MySQL info
		mysql_connect("localhost","DBUSER","DBPASS");
		mysql_select_db("DATABASE");
	}

	/**
	 * The actual login function...
	 *
	 * Author: Dennis McWherter
	 *
	 */
	function login($user,$pass){
		// Grab the random salt...
		$salt = mysql_query("SELECT `salt` FROM `users` WHERE username='".mysql_escape_string($user)."' LIMIT 1;");
		if(mysql_num_rows($salt) == 0){
			return false;
		}
		$salt = implode(mysql_fetch_row($salt));
		// Now make the password :)
		$pass = md5($salt.$pass.$salt); // Could do this a variety of ways really.. but yeah this works
		unset($salt);
		// User query
		$query = mysql_query("SELECT * FROM `users` WHERE username='".mysql_escape_string($user)."' AND password='".mysql_escape_string($pass)."' LIMIT 1;");
		if(mysql_num_rows($query) == 0){
			return false;
		}
		unset($query);
		// All seems to check out fine...
		$_SESSION['username'] = $user;
		$_SESSION['time']     = time();
		return true;
	}

	/**
	 * Register! :D
	 *
	 * Author: Dennis McWherter
	 *
	 */
	function register($user,$pass){
		// Run some checks...
		$check = mysql_query("SELECT * FROM `users` WHERE username='".mysql_escape_string($user)."' LIMIT 1;");
		if(mysql_num_rows($check) != 0){
			return false;
		}

		// Every one loves salt... I'm addicted personally ;P
		// We'll make.. hmm. a 10char salt! :)
		$chars = "!a@b$g%^&*()_+=-'\";][\\/:87{}~`";

		// Make the salt
		for($i=0;$i<10;$i++){
			$salt .= $chars[rand() % strlen($chars)-.07];
		}

		// Make the pass
		$pass = md5($salt.$pass.$salt);

		// Insert stuff into DB
		if(mysql_query("INSERT INTO `users` (`id`,`username`,`password`,`salt`) VALUES (NULL, '".mysql_escape_string($user)."', '".$pass."', '".$salt."')")){
			return true;
		}
		return false;
	}			

}

?>
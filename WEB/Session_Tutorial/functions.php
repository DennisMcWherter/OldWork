<?php
/**
 * Simple Sessions Tutorial by RageD
 *
 * (C) RageD 2009. All Rights Reserved.
 *
 *
 * All of our simple functions will be held here! :D
 * All the login/logout will be carried out. Perhaps later
 * I'll add on with a MySQL version so you can checkAuth();
 * against a db, etc!
 *
 */

class Session
{
  /**
   * Login
   *
   * Starting right on it :) No need for a __construct();
   * or other variables to be defined because this isn't a
   * large project carrying from multiple files, functions,
   * classes, etc.! :)
   *
   */
  function login($user,$pass)
  {
    // Here we will completely carryout the login function
    // according to data inserted. Since we aren't logged
    // into a DB this is going to be static and only allow
    // as many as you define.
    if($user == "Test" AND $pass="w00t" OR $user == "User2" AND $pass == "pass2")
    {
      $_SESSION['username'] = $user; // Sets the session data username = to $user
      print "Login Successful! Go back <a href=\"?page\">home</a>"; // Prints msg
    } else {
      print "Invalid login credentials!"; // Prints msg
      return false;
    }
    return true;
  }

  /**
   * Logout
   *
   */
  function logout()
  {
    // Unbelievably simple but... Yep, that's it! ;)
    session_destroy(); // Destroys session
    print "Logout Successful!"; // Prints message
    return true;
  }

  /**
   * CheckAuth
   *
   * Again, no DB so no checking for permissions
   * only for session data really :)
   *
   */
  function checkAuth()
  {
    if(!$_SESSION['username'])
    {
      print "You must be logged in!";
      return false;
    }
    return true;
  }
}
?>
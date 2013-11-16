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
// Script security :)
if(!defined("IS_SCRIPT")){
  print "Unauthorized access";
  exit;
}

class Login
{

  /**
   * Constructor :D
   *
   */
  function __construct(){
    mysql_connect(DBHOST,DBUSER,DBPASS);
    mysql_select_db(DATABASE);
  }

  /**
   * Register function :D
   *
   */
  function register($user,$pass){
    // Simple checks.. umm. Yeah let's make sure user doesn't exist XD
    $check = mysql_query("SELECT * FROM users WHERE user='".mysql_escape_string($user)."'");
    if(mysql_num_rows($check) != 0){
      return false;
    }

    // Let's begin with making our first and second salt character set
      // This is our first set of possible salt characters. Shuffle so always different all aspects
    $set1 = str_shuffle("!@#$%^&*()_+=-';:,<.>126AaBbJjKkLlSdDsQwWeErqRtTyY");
      // Second set. Same thing, different characters though :D
    $set2 = str_shuffle("1234567890`~ZxzxCcVvBb?[]{}pP");

    // Now the loops to actually make the salt characters
    // We'll be using the rand(); function give us random chars from the shuffled sets
    // The for loops are fairly simple.
    // Salt1 = 12 char
    // Salt2 = 10 char
    for($i=0;$i<12;$i++){
      $salt1 .= $set1[rand() % strlen($set1)-.04];
    }

    for($i=0;$i<10;$i++){
      $salt2 .= $set2[rand() % strlen($set2)-.07];
    }

    // Now let's generate a pattern. We'll have only about 4 combinations.
    // For time sake we'll only do a few simple ones.
    $part[1] = "{salt1}";
    $part[2] = "{salt2}";
    $part[3] = "{pass}";
    $psort   = array_rand($part,3);
    $pattern = $part[$psort[0]].".".$part[$psort[1]].".".$part[$psort[2]];

    // Now for pass
    $grep = array("/{salt1}/","/{salt2}/","/{pass}/"); // Identify pattern
    $repl = array($salt1,$salt2,$pass); // Make pattern real

    // Now replace the pattern with actual values XD
    $sendpass = preg_replace($grep,$repl,$pattern);

    // Send all to DB
    $query = "INSERT INTO users (`id`,`user`,`password`,`salt1`,`salt2`,`pattern`) VALUES 
	(NULL, '".mysql_escape_string($user)."',
	'".md5($sendpass)."', '".mysql_escape_string($salt1)."',
	'".mysql_escape_string($salt2)."', '".mysql_escape_string($pattern)."')";
    if(!mysql_query($query)){
      print "DB Connection failed: ".mysql_error();
      return false;
    }
    return true;
  }

  /**
   * Login Function
   *
   */
  function login($user,$pass){
    // Grab info by username since usernames are unique anyway...
    $query = "SELECT * FROM users WHERE user='".mysql_escape_string($user)."' LIMIT 1;";
    if(!mysql_query($query)){
      print "DB Connection Failed: ".mysql_error();
      return false;
    }
    $info  = mysql_fetch_assoc(mysql_query($query));
    
    // Use the grep and replace arrays again to replace information from pattern!
    $grep = array("/{salt1}/","/{salt2}/","/{pass}/"); // Identify pattern
    $repl = array($info['salt1'],$info['salt2'],$pass); // Make pattern real
    $pwd  = preg_replace($grep,$repl,$info['pattern']); // Generate password how it should be.

    // Now let's make sure the user is properly identifying!
    if(md5($pwd) != $info['password']){
      print "Incorrect password!";
      unset($info);
      return false;
    }

    // All checks out... Let's create session data and give a success msg.. We're just about done
    // anyway ;)
    $_SESSION['username'] = $user;
    print "You've logged in successfully! Please return <a href=\"?page=index\">home</a>";

    // Delete all info in the $info var
    unset($info);
    return true;
  }
}
?>
<?php
/**
 * Simple Sessions Tutorial by RageD
 *
 * (C) RageD 2009. All Rights Reserved.
 *
 * Main index script! :)
 *
 */
// Needs to be included first remember:
require_once("init.php");

// Include functions!
require_once("functions.php");

$session = new Session; // Declare our session and how we're going to call ptrs
$page = $_GET['page']; // Declare this to input multiple pages in this doc :)
switch($page)
{
  default:
    if(!$_SESSION['username'])
    { // Basically meaning if user is not logged in!
?>
<html>
<head>
<title>Login Page</title>
</head>
<body>
<form name="login" method="post" action="?page=login">
<p>User: <input type="text" name="user" /></p>
<p>Pass: <input type="password" name="pass" /></p>
<p><input type="submit" value="Login" /> <input type="reset" value="Reset" /></p>
</form>
</body>
</html>
<?php
    } else {
?>
<html>
<head>
<title>Home (User: <?php echo($_SESSION['username']); ?> Logged in!)</title>
</head>
<body>
<h2>Options:</h2>
<p><a href="test.php">Test to see if session works on multiple pages</a></p>
<p><a href="?page=logout">Logout</a></p>
</body>
</html>
<?php
    }
  break;
  case 'login':
    $session->login($_POST['user'],$_POST['pass']);
  break;
  case 'logout':
    $session->logout();
  break;
}
?>
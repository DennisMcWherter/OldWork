<?php
/**
 * Simple Sessions Tutorial by RageD
 *
 * (C) RageD 2009. All Rights Reserved.
 *
 *
 * Just a simple test document to prove that
 * the sessions will work across the entire 
 * website as long as "init.php" is loaded
 * first thing!
 *
 */
require_once("init.php");
$page = $_GET['page'];
if(!$_SESSION['username'])
{
?>
<html>
<head>
<title>No user logged in</title>
</head>
<body>
<p>Since no user is logged in, this page is useless :)<br /><br />
Please go back <a href="index.php">here</a> and login with the following credentials
to successfully login and use this page.</p>
<p></p>
<p>User 1<br />
User: Test<br />
Pass: w00t<br /><br />
User 2<br />
User: User2<br />
Pass: Pass2</p>
</body>
</html>
<?php
} else {
?>
<html>
<head>
<title>User: <?php echo($_SESSION['username']); ?> - Logged In!</title>
</head>
<body>
<p>See, it works properly! :) You're logged in with the username <?php echo($_SESSION['username']); ?>. 
Nothing special here but this message. You can go back home <a href="index.php">here</a>. I guess I can
throw a little server grabbing in here too.</p>
<p>Since we don't have a database nothing will be logged and therefore making it pointless to add
how many logins the account has had.</p>
<p>So... I guess I can show you your IP address! :)<br /></p>
<p>Your IP Address: <?php echo($_SERVER['REMOTE_ADDR']); ?><br /><br />Enjoy,<br />RageD</p>
</body>
</html>
<?php
}
?>
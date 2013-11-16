<?php
session_start();
// Plugins
$res = mysql_query("select * from plugins where enabled='True'");
while($row = mysql_fetch_array($res)){
	include_once("includes/plugins/uploads/".$row['name']."/".$row['main']);
}
// Free results
unset($res);
if ($option -> is_installed() != true) {
	header("Location: install/install.php");
}

if (isset($_SESSION['logged_in'])) {
	if ($_SESSION['admin'] == 1) {
		$smarty->assign('login', $option -> get_option_value("admin_logged_in"));
	} else {
		$smarty->assign('login', $option -> get_option_value("logged_in"));
	}
} else {
	$smarty->assign('login', $option -> get_option_value("login_box"));
}

if (isset($_GET['notice'])) {
	$error = $_GET['notice'];
	$display = "<div class='error-sbox'>"
					. "<h1>Notice!</h1>"
					. "<p>$error</p>"
				. "</div>";
	$smarty->assign('notice', $display);
}

$smarty -> assign('site_url', $option -> get_option_value('site_url'));
$smarty -> assign('site_description', $option -> get_option_value('description'));
$smarty -> assign('site_keywords', $option -> get_option_value('keywords'));
$smarty -> caching = false;
$template = $option -> get_option_value("active_template");

$option -> add_hit();

$ip = $_SERVER['REMOTE_ADDR'];

$sql = "select * from banned where value = '$ip'";
$result = mysql_query($sql);
$r = mysql_num_rows($result);
if ($r > 0) {
	die("You've been banned.");
}
?>
<?php
/**
 * Pagination Script by Dennis M.
 * (C) 2009 Dennis M. All Rights Reserved.
 *
 * Primary purpose of this script is to teach
 * people the art and concept of pagination
 * and how to effectively create/use it.
 * Please give credit to Dennis M. if you
 * take anything directly from this script.
 *
 */

// Connect to DB
mysql_connect("localhost","USER","PASS");
mysql_select_db("USER_DATABASE");

// Define results per page
$perPage = 1;

// Define page number in URL
$num = $_GET['no'];

// Define link starting point.
$linkno = 1;

// If no number given, default it.
if(!isset($num) OR !is_numeric($num)){
    $num = 1;
}

// Multiply to see where we're at to show results :)
$currentLimit = $perPage*($num-1);

// Get how many pages we'll have total (for links)
$numPages = mysql_num_rows(mysql_query("SELECT * FROM pagination"))/$perPage;

$query = mysql_query("SELECT * FROM pagination ORDER BY id ASC LIMIT ".mysql_escape_string($currentLimit).",".mysql_escape_string($perPage).";");

// Fetch all the info
while($row = mysql_fetch_array($query)){
    $title = stripslashes($row['name']);
    $article = stripslashes($row['content']);
?>
<html>
<head>
<title>Pagination Test</title>
</head>
<body>
<h1><?php echo($title); ?></h1><br />
<p><?php echo($article); ?></p><br /><hr>
<?php
}
print "<p align=\"right\">";
if($perPage <= 2){
    while($links < round($numPages)){
?>
<a href="?no=<?php echo($linkno); ?>"><?php echo($linkno); ?></a>
<?php
        $links++;
        $linkno++;
    }
} else {
    while($links <= round($numPages)){
?>
<a href="?no=<?php echo($linkno); ?>"><?php echo($linkno); ?></a>
<?php
        $links++;
        $linkno++;
    }
}
?></p>
</body>
</html>

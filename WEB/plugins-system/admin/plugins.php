<?PHP
	include('header.php');
	$admtitle = 'Plugins';
	$admactive = 'plugins';
if($_GET['upload'] == "true"){
  if($_FILES != NULL){
    $zip = new ZipArchive;
    if(!@$zip->open($_FILES['plugin']['tmp_name'])){
      $nofile = "<font color=\"red\">No file selected!</font>";
    } else {
      // check name
      $name = mysql_query("SELECT * FROM plugins WHERE name='".str_replace('.zip','',$_FILES['plugin']['name'])."'");
      if(mysql_num_rows($name) != 0){
	$msg = "<font color=\"red\">Plugin already uploaded with that name!</font>";
      } else {
	$zip->extractTO('../includes/plugins/uploads/'.str_replace('.zip','',$_FILES['plugin']['name']));
	$zip->close();
	@$desc = file_get_contents('../includes/plugins/uploads/'.str_replace('.zip','',$_FILES['plugin']['name']).'/description.txt');
	if(!mysql_query("INSERT INTO plugins SET name='".str_replace('.zip','',$_FILES['plugin']['name'])."',
	  description='".mysql_escape_string($desc)."', main='".str_replace('.zip','',$_FILES['plugin']['name']).".php', enabled='True'")){
	  $msg = "<font color=\"red\">MySQL Error: ".mysql_error()."</font>";
        }
      }
    }
  }
  // Free
  unset($zip);
  unset($name);
  unset($desc);
}

if($_GET['delete']){
  $res  = mysql_query("SELECT * FROM plugins WHERE id='".$_GET['delete']."'");
  $row = mysql_fetch_array($res);
  if(!mysql_query("DELETE FROM plugins WHERE id='".$_GET['delete']."'")){
	$msg = "<font color=\"red\">Failed to delete plugin!</font>";
  } else {
	$msg = "<font color=\"green\">Plugin deleted successfully!</font>";
  }
  @$open = opendir('../includes/plugins/uploads/'.$row['name']);
  if($open){
    while($dir = readdir($open)){
      if($dir != '.' OR $dir != '..'){
        @unlink('../includes/plugins/uploads/'.$row['name'].'/'.$dir);
      }
    }
    closedir($open);
    @rmdir('../includes/plugins/uploads/'.$row['name']);
  }
}

if($_GET['enable']){
  if(!mysql_query("UPDATE plugins SET enabled='True' WHERE id='".$_GET['enable']."'")){
	$msg = "<font color=\"red\">Failed to enable plugin!</font>";
  } else {
	$msg = "<font color=\"green\">Plugin successfully enabled!</font>";
  }
}
if($_GET['disable']){
  if(!mysql_query("UPDATE plugins SET enabled='False' WHERE id='".$_GET['disable']."'")){
	$msg = "<font color=\"red\">Failed to disable plugin!</font>";
  } else {
	$msg = "<font color=\"green\">Plugin successfully disabled!</font>";
  }
}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html lang="EN" dir="ltr" xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta http-equiv="content-type" content="text/xml; charset=utf-8" />
		<title>Useful.WS Admin | <?PHP echo $admtitle; ?></title>
		<link rel="stylesheet" type="text/css" href="admin.css" />
		<script type="text/javascript" src="../scripts/jquery.js"></script>
	</head>
	<body>
		<div id="page-container">
			<div id="branding">
				<h1>Useful.WS <span>| web administration module</span></h1>
			</div>
			
			<?php include('page-nav.php'); ?>


		<div id="page-content" class="clearfix">
			<h1>Plugins</h1>
			<h2>General Area <span>(site stats and common activities)</span></h2>


			
			<div class="inner-box clearfix">
				<div id="dashboard-menu">
					<span>Plugins:</span>
					<ul><li style="color:#FFFFFF"> To use the plugin system please upload a plugin and then activate/deactiviate it from the menu
					below. You can activate/deactivate a mod at any time.</li>
					</ul>
				</div>
				<?php print $msg; ?>
				<div class='stats-wrapper'>
					<div class="stats-box">
						<p><strong>Current Plugins</strong></p>
					<?php
					$i=0;
					$res = mysql_query("select * from plugins");
					while($row = mysql_fetch_array($res)){
					if($i&1){ ?>
					<p> <?php } else { ?>
					<p class="dashboard-menu">
					<?php }
					print "<strong>Name:</strong> ".$row['name']."<br />
					<strong>Description:</strong> <em>".$row['description']."</em><br />";
					if($row['enabled'] != 'True'){
						print "<a href=\"?enable=".$row['id']."\">Enable</a>";
					} else {
						print "<a href=\"?disable=".$row['id']."\">Disable</a>";
					} ?>
					<a href="?delete=<?php echo($row['id']); ?>">Delete</a>
					</p>
					<?php $i++; } ?>
					</div>

					<div class="stats-box news">
					<p><strong>Upload a Plugin</strong></p>
					<form name="upload" action="?upload=true" method="post" enctype="multipart/form-data">
					<p><em>Mod Archive File: (.zip archive)</em> <input type="file" name="plugin" /><br />(<em>To include description add description.txt to archive</em>)</p>
					<p align="center"><input type="submit" value="Upload" />
					<?php
					if(isset($nofile)){
						print "<br />\n".$nofile;
						unset($nofile);
					}
					?>
					</p>
					</form>
					</div>
				</div>
			</div>
			
			

<?PHP
	include('footer.php');
?>

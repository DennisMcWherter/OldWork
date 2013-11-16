<div id="sidebar">
	
	{$notice}
	
	<div class="sbox">
		{$login}
	</div>
	
	<div class="sbox">
		<h1>Search</h1>
		<span class="se">The useful directory</span>
		<form method="post" action="search.php">
			<input type="text" name="search" />
			<input value="Go" class="submit" type="submit" /> 
		</form>
	</div>

	{php}
	// Plugins - Redundant, but need for side bar.
	$res = mysql_query("select * from plugins where enabled='True'");
	while($row = mysql_fetch_array($res)){
		if(preg_match('/\$sidebar_module/',file_get_contents("includes/plugins/uploads/".$row['name']."/".$row['main']))){
			include("includes/plugins/uploads/".$row['name']."/".$row['main']);
		}
	}
	// Free results
	unset($res);
	if(is_array($sidebar_module)){
		foreach($sidebar_module as $mod){
			if($mod['type'] == "page" && !isset($dpage)){
				print "<div class=\"sbox\">\n<h1>Plugins</h1>\n";
				$dpage = 1;
			}
		}
		foreach($sidebar_module as $mod){
			if(strtolower($mod['enabled']) == "true" && $mod['type'] == "page"){
				print "<a href=\"?page={$mod['link']}\">{$mod['title']}</a><br />\n";
			}
		}
		print "</div>";
		foreach($sidebar_module as $mod){
			if(strtolower($mod['enabled']) == "true" && $mod['type'] == "module"){
				$_GET['page'] = $mod['link'];
				print "<div class=\"sbox\"><h1>{$mod['title']}</h1>\n";
				include('includes/plugins/uploads/'.$mod['link'].'/'.$mod['link'].'.php');
				print "\n
				</div>";
			}
		}
	
	}
	{/php}

	<div class="sbox">
		<h1>Main Categories</h1>
		<span class="se">Of useful websites</span>
		<ul>
			{$categories}
		</ul>
	</div>
	
	{$subcategories}
	
</div>
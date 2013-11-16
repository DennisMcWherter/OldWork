<div id="page-navigation" class="clearfix">
				<ul>
					<?php
						$pages = array(
									array(
										"../index.php",
										"View Site"
									),
									array(
										"index.php",
										"Dashboard"
									),
									array(
										"sites.php",
										"Sites"
									),
									array(
										"pages.php",
										"Pages"
									),
									array(
										"categories.php",
										"Categories"
									),
									array(
										"settings.php",
										"Settings"
									),
									array(
										"plugins.php",
										"Plugins"
									),
									array(
										"templates.php",
										"Templates"
									),
									array(
										"users.php",
										"Users"
									),
									array(
										"logout.php",
										"Logout"
									)
								);
						$list = "";		
						
						$this_file = $_SERVER["SCRIPT_NAME"];
					    $parts = Explode('/', $this_file);
					    $this_file = $parts[count($parts) - 1];
						
						for ($i=0;$i<9;$i++) {
							if ($_SESSION['admin'] == 0 && $i >= 1 && $i <= 6) {
								$i = 7;
							}
							if ($pages[$i][0] == $this_file) {
								$list .= "<li class='current'><a href='" . $pages[$i][0] . "'>" . $pages[$i][1] . "</a></li>\n";
							} else {
								$list .= "<li><a href='" . $pages[$i][0] . "'>" . $pages[$i][1] . "</a></li>\n";
							}
						}
						echo $list;
					?>
				</ul>		
			</div>
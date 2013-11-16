CREATE TABLE `plugins` (
  `id` bigint(10) NOT NULL auto_increment,
  `name` varchar(255) NOT NULL,
  `description` text NOT NULL,
  `main` varchar(255) NOT NULL,
  `enabled` enum('True','False') NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=15 ;

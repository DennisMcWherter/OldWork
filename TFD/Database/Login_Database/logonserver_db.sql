-- TFD Logon Server Database
-- 
-- First example

-- --------------------------------------------------------
-- 
-- Table structure for table `tfd_login`
-- 

DROP TABLE IF EXISTS `tfd_login`;
CREATE TABLE `tfd_login` (
  `id` bigint(10) NOT NULL auto_increment,
  `user` varchar(16) NOT NULL,
  `pass` varchar(32) NOT NULL,
  `email` varchar(32) NOT NULL,
  `status` enum('active','pending','suspended','banned') NOT NULL default 'active',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1;


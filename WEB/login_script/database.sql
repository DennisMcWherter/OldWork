CREATE TABLE `users` (
`id` BIGINT( 10 ) NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`username` VARCHAR( 32 ) NOT NULL ,
`password` VARCHAR( 32 ) NOT NULL ,
`salt` VARCHAR( 10 ) NOT NULL
) ENGINE = MYISAM ;
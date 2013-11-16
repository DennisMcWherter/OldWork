/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`login_server` /*!40100 DEFAULT CHARACTER SET ucs2 */;

USE `login_server`;

/*Table structure for table `account server table` */

DROP TABLE IF EXISTS `account server table`;

CREATE TABLE `account server table` (
  `Account Server ID` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'ID of the account server',
  `Server Address` varchar(65) NOT NULL COMMENT 'Ip address of the account server',
  `Server Port` smallint(5) unsigned NOT NULL COMMENT 'Port address of the account server',
  PRIMARY KEY (`Account Server ID`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=ucs2;

/*Data for the table `account server table` */

LOCK TABLES `account server table` WRITE;

insert  into `account server table`(`Account Server ID`,`Server Address`,`Server Port`) values (1,'127.0.0.1',40000);

UNLOCK TABLES;

/*Table structure for table `game server table` */

DROP TABLE IF EXISTS `game server table`;

CREATE TABLE `game server table` (
  `Server Game ID` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'ID of the game server',
  `Server Game Name` varchar(32) NOT NULL COMMENT 'Name of the game server',
  `Server Address` varchar(65) NOT NULL COMMENT 'Public address of the server',
  `Server Local Address` varchar(65) NOT NULL COMMENT 'Local address of the server, used for lan communication',
  `Server Port` smallint(5) unsigned NOT NULL COMMENT 'Public port of the server',
  `Server Login Port` smallint(5) unsigned NOT NULL COMMENT 'Local port of the server',
  `Server Nationality` smallint(5) unsigned NOT NULL COMMENT 'Nationality of the server',
  PRIMARY KEY (`Server Game ID`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=ucs2;

/*Data for the table `game server table` */

LOCK TABLES `game server table` WRITE;

insert  into `game server table`(`Server Game ID`,`Server Game Name`,`Server Address`,`Server Local Address`,`Server Port`,`Server Login Port`,`Server Nationality`) values (1,'Test Server','127.0.0.1','127.0.0.1',40001,40002,1);

UNLOCK TABLES;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

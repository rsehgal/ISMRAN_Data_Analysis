-- MySQL dump 10.13  Distrib 5.7.36, for Linux (x86_64)
--
-- Host: localhost    Database: ismran_db
-- ------------------------------------------------------
-- Server version	5.7.36-0ubuntu0.18.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `ismran_data_files`
--

DROP TABLE IF EXISTS `ismran_data_files`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ismran_data_files` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `daqFileName` varchar(500) DEFAULT NULL,
  `creationDate` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `hashCode` varchar(200) DEFAULT NULL,
  `ambarFileName` varchar(500) DEFAULT NULL,
  `copyDate` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `hashCheck` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ismran_data_files`
--

LOCK TABLES `ismran_data_files` WRITE;
/*!40000 ALTER TABLE `ismran_data_files` DISABLE KEYS */;
/*!40000 ALTER TABLE `ismran_data_files` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ismran_files`
--

DROP TABLE IF EXISTS `ismran_files`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ismran_files` (
  `filePath` varchar(500) DEFAULT '',
  `fileName` varchar(500) DEFAULT '',
  `currenFile` tinyint(1) DEFAULT '0',
  `hashCode` varchar(500) DEFAULT '',
  `copied` tinyint(1) DEFAULT '0',
  `integrityCheck` tinyint(1) DEFAULT '0',
  `remoteFilePath` varchar(500) DEFAULT ''
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ismran_files`
--

LOCK TABLES `ismran_files` WRITE;
/*!40000 ALTER TABLE `ismran_files` DISABLE KEYS */;
INSERT INTO `ismran_files` VALUES ('/home/rsehgal/ISMRAN_dqm/sourceDir','test1.txt',0,'a7bbc7af4a9245a1a796778067cd9d995c278293462e0c8a1e1946179d2e1fd0',1,1,'/home/rsehgal/ISMRAN_dqm/targetDir'),('/home/rsehgal/ISMRAN_dqm/sourceDir','test2.txt',0,'f360f60a15362c7bb4da9f36e52a417dca420c3ced8e90f17301f03c29d48489',1,1,'/home/rsehgal/ISMRAN_dqm/targetDir');
/*!40000 ALTER TABLE `ismran_files` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-11-05 23:58:45

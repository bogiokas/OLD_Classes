-- MySQL dump 10.16  Distrib 10.1.33-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: wien_trains
-- ------------------------------------------------------
-- Server version	10.1.33-MariaDB

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
-- Table structure for table `routes`
--

DROP TABLE IF EXISTS `routes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `routes` (
  `route_id` tinyint(3) unsigned NOT NULL,
  `route_name` char(2) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`route_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `routes`
--

LOCK TABLES `routes` WRITE;
/*!40000 ALTER TABLE `routes` DISABLE KEYS */;
INSERT INTO `routes` VALUES (1,'U1'),(2,'U2'),(3,'U3'),(4,'U4'),(6,'U6');
/*!40000 ALTER TABLE `routes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stop_times`
--

DROP TABLE IF EXISTS `stop_times`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stop_times` (
  `trip_id` tinyint(3) unsigned NOT NULL,
  `stop_sequence` tinyint(3) unsigned NOT NULL,
  `stop_id` char(2) COLLATE utf8mb4_unicode_ci NOT NULL,
  `minutes` tinyint(4) NOT NULL,
  `event_id` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`event_id`)
) ENGINE=InnoDB AUTO_INCREMENT=64 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stop_times`
--

LOCK TABLES `stop_times` WRITE;
/*!40000 ALTER TABLE `stop_times` DISABLE KEYS */;
INSERT INTO `stop_times` VALUES (10,0,'LO',2,1),(10,1,'KP',16,2),(10,2,'SZ',18,3),(10,3,'SP',19,4),(10,4,'PR',21,5),(10,5,'LU',36,6),(11,0,'LU',0,7),(11,1,'PR',15,8),(11,2,'SP',17,9),(11,3,'SZ',18,10),(11,4,'KP',20,11),(11,5,'LO',33,12),(20,0,'EE',3,13),(20,1,'PR',22,14),(20,2,'SR',25,15),(20,3,'VT',30,16),(20,4,'KP',33,17),(21,0,'KP',1,18),(21,1,'VT',4,19),(21,2,'SR',9,20),(21,3,'PR',12,21),(21,4,'EE',31,22),(30,0,'OK',1,23),(30,1,'WS',8,24),(30,2,'VT',12,25),(30,3,'SZ',15,26),(30,4,'LA',17,27),(30,5,'SA',27,28),(31,0,'SA',1,29),(31,1,'LA',11,30),(31,2,'SZ',13,31),(31,3,'VT',16,32),(31,4,'WS',20,33),(31,5,'OK',27,34),(40,0,'HF',1,35),(40,1,'LE',11,36),(40,2,'KP',18,37),(40,3,'LA',21,38),(40,4,'SP',23,39),(40,5,'SR',24,40),(40,6,'AU',28,41),(40,7,'HS',30,42),(41,0,'HS',2,43),(41,1,'AU',4,44),(41,2,'SR',7,45),(41,3,'SP',8,46),(41,4,'LA',10,47),(41,5,'KP',13,48),(41,6,'LE',20,49),(41,7,'HF',30,50),(60,0,'HT',3,51),(60,1,'LE',15,52),(60,2,'WS',18,53),(60,3,'AU',29,54),(60,4,'FL',36,55),(61,0,'FL',0,56),(61,1,'AU',7,57),(61,2,'WS',19,58),(61,3,'LE',22,59),(61,4,'HT',34,60);
/*!40000 ALTER TABLE `stop_times` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stops`
--

DROP TABLE IF EXISTS `stops`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stops` (
  `stop_id` char(2) COLLATE utf8mb4_unicode_ci NOT NULL,
  `stop_name` varchar(15) COLLATE utf8mb4_unicode_ci NOT NULL,
  `transfer_min` tinyint(4) NOT NULL,
  PRIMARY KEY (`stop_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stops`
--

LOCK TABLES `stops` WRITE;
/*!40000 ALTER TABLE `stops` DISABLE KEYS */;
INSERT INTO `stops` VALUES ('AU','Spittelau',2),('EE','Seestadt',0),('FL','Floridsdorf',0),('HF','Hütteldorf',0),('HS','Heiligenstadt',0),('HT','Siebenhirten',0),('KP','Karlsplatz',3),('LA','Landstraße',2),('LE','Längenfeldgasse',2),('LO','Oberlaa',0),('LU','Leopoldau',0),('OK','Ottakring',0),('PR','Praterstern',2),('SA','Simmering',0),('SP','Schwedenplatz',2),('SR','Schottenring',3),('SZ','Stephansplatz',3),('VT','Volkstheater',2),('WS','Westbahnhof',2);
/*!40000 ALTER TABLE `stops` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trips`
--

DROP TABLE IF EXISTS `trips`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trips` (
  `trip_id` tinyint(3) unsigned NOT NULL,
  `route_id` tinyint(3) unsigned NOT NULL,
  PRIMARY KEY (`trip_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trips`
--

LOCK TABLES `trips` WRITE;
/*!40000 ALTER TABLE `trips` DISABLE KEYS */;
INSERT INTO `trips` VALUES (10,1),(11,1),(20,2),(21,2),(30,3),(31,3),(40,4),(41,4),(60,6),(61,6);
/*!40000 ALTER TABLE `trips` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-06-13  3:35:41

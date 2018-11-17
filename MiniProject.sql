-- MySQL dump 10.13  Distrib 5.7.17, for Linux (x86_64)
--
-- Host: localhost    Database: SUPERMARKET1
-- ------------------------------------------------------
-- Server version	5.7.17-0ubuntu0.16.04.2

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
-- Table structure for table `billing`
--

DROP TABLE IF EXISTS `billing`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `billing` (
  `date_time_purchase` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `memid` int(11) DEFAULT NULL,
  `totamt` float DEFAULT NULL,
  `givamt` float DEFAULT NULL,
  `balance` float DEFAULT NULL,
  `cardno` int(20) DEFAULT NULL,
  PRIMARY KEY (`date_time_purchase`),
  KEY `memid` (`memid`),
  CONSTRAINT `billing_ibfk_1` FOREIGN KEY (`memid`) REFERENCES `member` (`memid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `billing`
--

LOCK TABLES `billing` WRITE;
/*!40000 ALTER TABLE `billing` DISABLE KEYS */;
INSERT INTO `billing` VALUES ('2017-04-25 10:11:52',702,100,0,0,9993),('2017-04-25 10:25:21',702,1050,5000,3950,NULL),('2017-04-25 11:53:32',702,1.5,0,-1.5,NULL);
/*!40000 ALTER TABLE `billing` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `category`
--

DROP TABLE IF EXISTS `category`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `category` (
  `catid` int(11) NOT NULL,
  `cname` varchar(30) DEFAULT NULL,
  `secid` int(11) DEFAULT NULL,
  PRIMARY KEY (`catid`),
  KEY `secid` (`secid`),
  CONSTRAINT `category_ibfk_1` FOREIGN KEY (`secid`) REFERENCES `section` (`secid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `category`
--

LOCK TABLES `category` WRITE;
/*!40000 ALTER TABLE `category` DISABLE KEYS */;
INSERT INTO `category` VALUES (200100,'FruitsNVegetables',200),(200101,'MeatNSeafood',200),(200102,'Bakery',200),(200103,'DairyPdts',200),(201104,'Babycare',201),(201105,'cosmetics',201),(201106,'FashionAccessories',201),(202107,'KitchenApp',202),(202108,'Electricals',202),(202109,'CleaningAcc',202),(203110,'FirstAidPro',203),(204111,'SchoolSupply',204),(204112,'OfficeSupply',204);
/*!40000 ALTER TABLE `category` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `emp_pass`
--

DROP TABLE IF EXISTS `emp_pass`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `emp_pass` (
  `empid` int(11) NOT NULL,
  `password` varchar(30) NOT NULL,
  PRIMARY KEY (`empid`),
  CONSTRAINT `fkey` FOREIGN KEY (`empid`) REFERENCES `employee` (`empid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `emp_pass`
--

LOCK TABLES `emp_pass` WRITE;
/*!40000 ALTER TABLE `emp_pass` DISABLE KEYS */;
INSERT INTO `emp_pass` VALUES (500,'500'),(501,'501'),(502,'502'),(503,'503'),(504,'504'),(505,'505'),(506,'506'),(509,'hi'),(600,'600'),(601,'601'),(602,'602'),(603,'603'),(604,'604');
/*!40000 ALTER TABLE `emp_pass` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `empleave`
--

DROP TABLE IF EXISTS `empleave`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `empleave` (
  `leave_date` date DEFAULT NULL,
  `empid` int(11) NOT NULL,
  KEY `empid` (`empid`),
  CONSTRAINT `empleave_ibfk_1` FOREIGN KEY (`empid`) REFERENCES `employee` (`empid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `empleave`
--

LOCK TABLES `empleave` WRITE;
/*!40000 ALTER TABLE `empleave` DISABLE KEYS */;
INSERT INTO `empleave` VALUES ('2017-04-27',500),('2018-05-05',501),('2018-05-05',500),('2019-05-05',500),('2020-05-05',500),('2020-06-06',500);
/*!40000 ALTER TABLE `empleave` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `employee`
--

DROP TABLE IF EXISTS `employee`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `employee` (
  `empid` int(11) NOT NULL,
  `name` varchar(30) DEFAULT NULL,
  `secid` int(11) DEFAULT NULL,
  `phno` int(11) DEFAULT NULL,
  `dob` date DEFAULT NULL,
  `gender` char(1) DEFAULT NULL,
  `addr` varchar(30) DEFAULT NULL,
  `salary` int(11) DEFAULT NULL,
  `joindate` date DEFAULT NULL,
  PRIMARY KEY (`empid`),
  KEY `secid` (`secid`),
  CONSTRAINT `employee_ibfk_1` FOREIGN KEY (`secid`) REFERENCES `section` (`secid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `employee`
--

LOCK TABLES `employee` WRITE;
/*!40000 ALTER TABLE `employee` DISABLE KEYS */;
INSERT INTO `employee` VALUES (500,'kailash',201,901132414,'1977-10-13','M','13-23/D/B,chennai',31000,'2013-11-30'),(501,'kasi',202,901132499,'1912-10-13','M','13-23-13/D/B,chennai',10000,'2015-01-31'),(502,'neeli',203,901132491,'1912-10-20','F','01-12-13/D/B,chennai',10020,'2012-04-12'),(503,'samwright',200,38434,'1912-10-20','M','01-12-13/AB,chennai',12000,'2013-04-13'),(504,'bhargavi',204,901132491,'1912-10-20','F','01-211-13/B,chennai',12343,'2009-04-15'),(505,'bhargav',202,901132491,'1912-10-20','M','01-211-13/B,chennai',10943,'2010-04-30'),(506,'dikshita',203,901132492,'1912-10-21','F','01-212-13/B,chennai',12943,'2010-04-28'),(507,'joe',200,88766,'2017-04-04','M','krjn',98545,'2017-04-04'),(509,'jay',200,3094,'2017-04-04','M','hwbf',4000,'2017-04-04'),(600,'rajagopal',200,999999999,'1965-12-12','M','11-120/A,chennai',25000,'2014-12-12'),(601,'ramarao',201,901132442,'1965-12-12','M','11-120/A,chennai',25000,'2014-12-12'),(602,'ramarao',202,901132432,'1944-12-13','M','12-343/A,chennai',25400,'2015-02-04'),(603,'sailaja',203,901132431,'1988-12-13','F','12-343/B,chennai',34220,'2016-12-04'),(604,'radhika',204,901132434,'1977-12-13','F','12-2333/B,chennai',35000,'2013-12-23');
/*!40000 ALTER TABLE `employee` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `empshift`
--

DROP TABLE IF EXISTS `empshift`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `empshift` (
  `empid` int(11) NOT NULL,
  `secid` int(11) DEFAULT NULL,
  `shift` int(11) DEFAULT NULL,
  `day` varchar(30) DEFAULT NULL,
  KEY `empid` (`empid`),
  CONSTRAINT `empshift_ibfk_1` FOREIGN KEY (`empid`) REFERENCES `employee` (`empid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `empshift`
--

LOCK TABLES `empshift` WRITE;
/*!40000 ALTER TABLE `empshift` DISABLE KEYS */;
INSERT INTO `empshift` VALUES (507,200,1,'Monday'),(507,200,2,'Monday'),(507,200,1,'Tuesday'),(503,200,2,'Tuesday'),(503,200,1,'Wednesday'),(507,200,2,'Wednesday'),(507,200,2,'Thursday'),(503,200,1,'Friday'),(503,200,1,'Thursday'),(507,200,2,'Friday'),(500,201,1,'Monday');
/*!40000 ALTER TABLE `empshift` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `item`
--

DROP TABLE IF EXISTS `item`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `item` (
  `itemid` int(11) NOT NULL,
  `iname` varchar(15) DEFAULT NULL,
  `catid` int(11) DEFAULT NULL,
  `cost` float DEFAULT NULL,
  `stock` int(11) DEFAULT NULL,
  `supid` int(11) DEFAULT NULL,
  `expdate` date DEFAULT NULL,
  PRIMARY KEY (`itemid`),
  KEY `supid` (`supid`),
  KEY `catid` (`catid`),
  CONSTRAINT `item_ibfk_1` FOREIGN KEY (`supid`) REFERENCES `supplier` (`supid`),
  CONSTRAINT `item_ibfk_2` FOREIGN KEY (`catid`) REFERENCES `category` (`catid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `item`
--

LOCK TABLES `item` WRITE;
/*!40000 ALTER TABLE `item` DISABLE KEYS */;
INSERT INTO `item` VALUES (300,'Onions',200100,19.5,190,400,'2017-05-05'),(301,'Tomatoes',200100,15,0,400,'2017-05-01'),(302,'Apples',200100,50.25,86,400,'2017-05-04'),(303,'Corn',200100,10,0,400,'2017-05-01'),(304,'fish',200101,250,11,401,'2017-04-27'),(305,'Cakes',200102,45.75,0,402,'2017-04-25'),(306,'Milk',200103,20,0,403,'2017-04-25'),(307,'Babysoap',201104,40,48,404,'2018-10-27'),(308,'MakeupKit',201105,100,48,405,'2018-10-27'),(309,'Slippers',201106,101.5,0,406,'2018-10-27'),(310,'spoon',202107,10,25,407,NULL),(311,'PencilCell',202108,10,25,408,NULL),(312,'Lizol',202109,50.87,25,409,'2018-10-27'),(313,'Bandaid',203110,15.34,50,410,'2020-09-12'),(314,'SchoolBag',204111,400,50,411,NULL),(315,'LaptopBag',204112,1000,50,412,NULL);
/*!40000 ALTER TABLE `item` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `member`
--

DROP TABLE IF EXISTS `member`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `member` (
  `memid` int(11) NOT NULL,
  `mname` varchar(30) DEFAULT NULL,
  `phno` int(11) DEFAULT NULL,
  `gender` char(1) DEFAULT NULL,
  `dob` date DEFAULT NULL,
  `addr` varchar(30) DEFAULT NULL,
  `points` int(11) DEFAULT NULL,
  PRIMARY KEY (`memid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `member`
--

LOCK TABLES `member` WRITE;
/*!40000 ALTER TABLE `member` DISABLE KEYS */;
INSERT INTO `member` VALUES (700,'Chand',966896855,'M','1998-08-18','12,GandhiSt,Chennai',12),(701,'Raju',966456855,'M','1978-05-18','14,NehruSt,Chennai',18),(702,'Sita',966498855,'F','2017-04-04','18,NehruSt,Chennai',62),(703,'Rama',966498855,'F','2017-04-04','21,BalajiSt,Chennai',10),(704,'John',966498834,'M','1999-11-28','11/13,Rajanagar,Chennai',15),(705,'Srinivas',966491734,'M','1999-11-09','19,Rajanagar,Chennai',9),(706,'Bindu',966498855,'F','2017-04-04','29,BalajiSt,Chennai',10),(707,'Sarika',966498977,'M','1990-12-09','26,BalajiSt,Chennai',10),(708,'Byju',966498734,'M','1999-11-09','14,Rajanagar,Chennai',9),(709,'Heera',966498764,'F','1996-12-09','24,Rajanagar,Chennai',9),(710,'Santhosh',966458764,'M','1998-07-09','25,Rajanagar,Chennai',20),(711,'Rupali',966498999,'F','1998-09-23','28,NehruSt,Chennai',19),(712,'joe',42,'M','2017-04-04','fgdg',0),(713,'joe',324,'M','2017-03-04','dfgd',0);
/*!40000 ALTER TABLE `member` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `purchase`
--

DROP TABLE IF EXISTS `purchase`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `purchase` (
  `date_time_purchase` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `itemid` int(11) NOT NULL,
  `quantity` int(11) DEFAULT NULL,
  `memid` int(11) DEFAULT NULL,
  `cost` float DEFAULT NULL,
  PRIMARY KEY (`date_time_purchase`,`itemid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `purchase`
--

LOCK TABLES `purchase` WRITE;
/*!40000 ALTER TABLE `purchase` DISABLE KEYS */;
INSERT INTO `purchase` VALUES ('2017-04-25 08:30:32',309,1,702,101.5),('2017-04-25 09:32:04',301,0,702,0),('2017-04-25 09:32:04',302,2,702,100.5),('2017-04-25 10:11:52',306,5,702,100),('2017-04-25 10:25:21',301,0,702,0),('2017-04-25 10:25:21',303,0,702,0),('2017-04-25 10:25:21',304,5,702,1250),('2017-04-25 11:52:20',308,1,702,100),('2017-04-25 11:52:20',309,13,702,1319.5),('2017-04-25 11:53:32',308,1,702,100),('2017-04-25 11:53:32',309,1,702,101.5);
/*!40000 ALTER TABLE `purchase` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `section`
--

DROP TABLE IF EXISTS `section`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `section` (
  `secid` int(11) NOT NULL,
  `mgrid` int(11) DEFAULT NULL,
  PRIMARY KEY (`secid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `section`
--

LOCK TABLES `section` WRITE;
/*!40000 ALTER TABLE `section` DISABLE KEYS */;
INSERT INTO `section` VALUES (200,600),(201,601),(202,602),(203,603),(204,604);
/*!40000 ALTER TABLE `section` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `supplier`
--

DROP TABLE IF EXISTS `supplier`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `supplier` (
  `supid` int(11) NOT NULL,
  `sname` varchar(30) DEFAULT NULL,
  `locn` varchar(30) DEFAULT NULL,
  `phno` int(11) DEFAULT NULL,
  PRIMARY KEY (`supid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `supplier`
--

LOCK TABLES `supplier` WRITE;
/*!40000 ALTER TABLE `supplier` DISABLE KEYS */;
INSERT INTO `supplier` VALUES (400,'Bharat','Adyar,chennai',956473829),(401,'Swami','Dombivli,Mumbai',956477976),(402,'Harish','GandhiNagar,Gujarat',956475785),(403,'Balaji','Kelambakkam,chennai',956475785),(404,'Bala','Nungambakkam,chennai',956475785),(405,'priyanka','Guindy,chennai',999547578),(406,'priya','porur,chennai',987547578),(407,'devika','LBNagar,Hyderabad',987547867),(408,'devi','Hitechcity,Hyderabad',987547656),(409,'suresh','SagarRd,Hyderabad',987547855),(410,'Keerthi','SagarRd,Hyderabad',987596855),(411,'sekar','Guindy,chennai',987896855),(412,'BipinChand','Adyar,chennai',966896855);
/*!40000 ALTER TABLE `supplier` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-04-27 15:11:16

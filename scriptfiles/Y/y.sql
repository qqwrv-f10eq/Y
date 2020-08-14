-- phpMyAdmin SQL Dump
-- version 4.9.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Aug 14, 2020 at 01:58 PM
-- Server version: 10.4.11-MariaDB
-- PHP Version: 7.2.26

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `y-rp`
--

-- --------------------------------------------------------

--
-- Table structure for table `accounts`
--

DROP TABLE IF EXISTS `accounts`;
CREATE TABLE `accounts` (
  `id` bigint(20) UNSIGNED NOT NULL,
  `name` varchar(32) NOT NULL,
  `password` varchar(61) NOT NULL,
  `email` varchar(32) NOT NULL,
  `created_at` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=tis620;

--
-- Dumping data for table `accounts`
--

INSERT INTO `accounts` (`id`, `name`, `password`, `email`, `created_at`) VALUES
(4, 'John_Connor', '$2y$12$FNi3Lq.lXo7G0ixc8p7Ssew3kNP6DUAtQj/cXalhgoo.CE9w3qLoC', '', '2020-08-12 01:18:49'),
(5, 'Sarah_Candy', '$2y$12$FNi3Lq.lXo7G0ixc8p7Ssew3kNP6DUAtQj/cXalhgoo.CE9w3qLoC', '', '2020-08-12 01:18:49');

-- --------------------------------------------------------

--
-- Table structure for table `characters`
--

DROP TABLE IF EXISTS `characters`;
CREATE TABLE `characters` (
  `id` bigint(20) UNSIGNED NOT NULL,
  `name` varchar(25) NOT NULL,
  `secret_key` varchar(61) NOT NULL,
  `account_id` bigint(20) UNSIGNED NOT NULL,
  `active` tinyint(1) NOT NULL,
  `ip` varchar(18) NOT NULL,
  `created_at` datetime NOT NULL DEFAULT current_timestamp(),
  `logged_at` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=tis620;

--
-- Dumping data for table `characters`
--

INSERT INTO `characters` (`id`, `name`, `secret_key`, `account_id`, `active`, `ip`, `created_at`, `logged_at`) VALUES
(5, 'John_Connor', '$2y$12$6wnxft5A0ki3x.sGg10pvesewpTNt3mVE5SG/WU0yI63oIlcbdUX2', 4, 1, '127.0.0.1', '2020-08-12 01:18:55', '2020-08-14'),
(6, 'Sarah_Candy', '$2y$12$6wnxft5A0ki3x.sGg10pvesewpTNt3mVE5SG/WU0yI63oIlcbdUX2', 5, 1, '192.168.1.5', '2020-08-12 01:18:55', '2020-08-14');

-- --------------------------------------------------------

--
-- Table structure for table `character_statuses`
--

DROP TABLE IF EXISTS `character_statuses`;
CREATE TABLE `character_statuses` (
  `id` bigint(20) UNSIGNED NOT NULL,
  `character_id` bigint(20) UNSIGNED NOT NULL DEFAULT 0,
  `developer` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `admin` tinyint(1) UNSIGNED NOT NULL DEFAULT 0,
  `cash` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `bank` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `vip` tinyint(3) UNSIGNED NOT NULL DEFAULT 0,
  `vip_exp` date NOT NULL,
  `level` smallint(5) UNSIGNED NOT NULL,
  `skin` smallint(5) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=tis620;

--
-- Dumping data for table `character_statuses`
--

INSERT INTO `character_statuses` (`id`, `character_id`, `developer`, `admin`, `cash`, `bank`, `vip`, `vip_exp`, `level`, `skin`) VALUES
(2, 5, 1, 5, 0, 0, 0, '0000-00-00', 0, 72),
(3, 6, 1, 5, 0, 0, 0, '0000-00-00', 0, 1);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `accounts`
--
ALTER TABLE `accounts`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `characters`
--
ALTER TABLE `characters`
  ADD PRIMARY KEY (`id`),
  ADD KEY `account_id` (`account_id`);

--
-- Indexes for table `character_statuses`
--
ALTER TABLE `character_statuses`
  ADD PRIMARY KEY (`id`),
  ADD KEY `character_id` (`character_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `accounts`
--
ALTER TABLE `accounts`
  MODIFY `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- AUTO_INCREMENT for table `characters`
--
ALTER TABLE `characters`
  MODIFY `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT for table `character_statuses`
--
ALTER TABLE `character_statuses`
  MODIFY `id` bigint(20) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `characters`
--
ALTER TABLE `characters`
  ADD CONSTRAINT `account_id` FOREIGN KEY (`account_id`) REFERENCES `accounts` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `character_statuses`
--
ALTER TABLE `character_statuses`
  ADD CONSTRAINT `character_id` FOREIGN KEY (`character_id`) REFERENCES `characters` (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

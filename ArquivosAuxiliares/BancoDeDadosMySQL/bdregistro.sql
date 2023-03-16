-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Mar 16, 2023 at 02:01 PM
-- Server version: 10.4.27-MariaDB
-- PHP Version: 8.2.0

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `bdregistro`
--

-- --------------------------------------------------------

--
-- Table structure for table `tbdados`
--

CREATE TABLE `tbdados` (
  `id` int(11) NOT NULL,
  `Esp32` varchar(50) NOT NULL,
  `data_hora` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `tbdados`
--

INSERT INTO `tbdados` (`id`, `Esp32`, `data_hora`) VALUES
(1, 'CAIU', '2023-02-23 00:34:33'),
(3, 'urgente', '2023-02-23 00:35:02'),
(4, 'CAIU', '2023-02-23 00:34:33'),
(5, 'CAIU', '2023-02-23 00:34:33'),
(6, 'urgente', '2023-02-23 00:35:02'),
(7, 'CAIU', '2023-02-23 00:34:33'),
(8, 'CAIU', '2023-02-23 00:34:33'),
(9, 'urgente', '2023-02-23 00:35:02'),
(10, 'CAIU', '2023-02-23 00:34:33'),
(11, 'urgente', '2023-02-23 00:35:02'),
(12, 'CAIU', '2023-02-23 00:34:33'),
(13, 'CAIU', '2023-02-23 00:34:33'),
(14, 'urgente', '2023-02-23 00:35:02'),
(15, 'CAIU', '2023-02-23 00:34:33'),
(16, 'CAIU', '2023-02-23 00:34:33'),
(17, 'urgente', '2023-02-23 00:35:02'),
(18, 'CAIU', '2023-02-23 00:34:33'),
(19, 'CAIU', '2023-02-23 00:34:33'),
(20, 'urgente', '2023-02-23 00:35:02'),
(21, 'CAIU', '2023-02-23 00:34:33'),
(22, 'urgente', '2023-02-23 00:35:02'),
(23, 'CAIU', '2023-02-23 00:34:33'),
(24, 'CAIU', '2023-02-23 00:34:33'),
(25, 'urgente', '2023-02-23 00:35:02'),
(26, 'CAIU', '2023-02-23 00:34:33'),
(27, 'CAIU', '2023-02-23 00:34:33'),
(28, 'urgente', '2023-02-23 00:35:02'),
(29, 'CAIU', '2023-02-23 00:34:33'),
(30, 'CAIU', '2023-02-23 00:34:33'),
(31, 'urgente', '2023-02-23 00:35:02'),
(32, 'CAIU', '2023-02-23 00:34:33'),
(33, 'urgente', '2023-02-23 00:35:02'),
(34, 'CAIU', '2023-02-23 00:34:33'),
(35, 'CAIU', '2023-02-23 00:34:33'),
(36, 'urgente', '2023-02-23 00:35:02'),
(37, 'CAIU', '2023-02-23 00:34:33'),
(38, 'CAIU', '2023-02-23 00:34:33'),
(39, 'urgente', '2023-02-23 00:35:02'),
(40, 'CAIU', '2023-02-23 00:34:33'),
(41, 'CAIU', '2023-02-23 00:34:33'),
(42, 'urgente', '2023-02-23 00:35:02'),
(43, 'CAIU', '2023-02-23 00:34:33'),
(44, 'urgente', '2023-02-23 00:35:02'),
(45, 'CAIU', '2023-02-23 00:34:33');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `tbdados`
--
ALTER TABLE `tbdados`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `tbdados`
--
ALTER TABLE `tbdados`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=46;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

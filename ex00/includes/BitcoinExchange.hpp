/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:20:41 by lorey             #+#    #+#             */
/*   Updated: 2025/06/25 22:58:31 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>

class BitcoinExchange {
public:
	BitcoinExchange();
	// BitcoinExchange(BitcoinExchange &&) = default;
	// BitcoinExchange(const BitcoinExchange &) = default;
	// BitcoinExchange &operator=(BitcoinExchange &&) = default;
	// BitcoinExchange &operator=(const BitcoinExchange &) = default;
	~BitcoinExchange();
	void writeCSV();
	void parseCSV();
	void doTheCompare(std::string dateStr, double value); 

private:
	std::map<std::string, double> _priceMap;
};


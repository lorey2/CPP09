/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:24:56 by lorey             #+#    #+#             */
/*   Updated: 2025/06/25 23:14:36 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */



#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::~BitcoinExchange() {
}

void BitcoinExchange::writeCSV() {
	for (std::map<std::string, double>::const_iterator it = _priceMap.begin(); it != _priceMap.end(); ++it) {
		std::cout << it->first << " : " << it->second << std::endl;
	}
}

void BitcoinExchange::parseCSV() {
    std::string oneLine;
    std::ifstream Database("data.csv");
    std::size_t pos;

    if (!Database.is_open()) {
        std::cerr << "Error: cannot open file" << std::endl;
        return;
    }
    std::getline(Database, oneLine);
    while (std::getline(Database, oneLine)) {
        pos = oneLine.find(',');
        if (pos == std::string::npos) {
            std::cerr << "Error: bad input => " << oneLine << std::endl;
            continue;
        }
        std::string dateStr = oneLine.substr(0, pos);
        std::string valueStr = oneLine.substr(pos + 1);
        double value = strtod(valueStr.c_str(), NULL);

        if (value < 0) {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000000.0) {
             std::cerr << "Error: too large a number." << std::endl;
             continue;
        }
        if (dateStr.size() != 10 || dateStr[4] != '-' || dateStr[7] != '-') {
            std::cerr << "Error: bad date format => " << dateStr << std::endl;
            continue;
        }
        double year = strtod(dateStr.substr(0, 4).c_str(), NULL);
        double month = strtod(dateStr.substr(5, 2).c_str(), NULL);
        double day = strtod(dateStr.substr(8, 2).c_str(), NULL);
        if (year < 2009 || year > 2025 || month < 1 || month > 12 || day < 1 || day > 31) {
            std::cerr << "Error: invalid date components => " << dateStr << std::endl;
            continue;
        }
        this->_priceMap[dateStr] = value;
    }
	Database.close();
}

void BitcoinExchange::doTheCompare(std::string dateStr, double value) {
	// upper_bound() finds the first element with a date *strictly greater* than dateStr.
	std::map<std::string, double>::iterator it = this->_priceMap.upper_bound(dateStr);
	// We need the date on or *before* the input date, so we move the iterator back one position.
	--it;
	double btcPrice = it->second;
	double totalValue = value * btcPrice;
	// Print the result with proper formatting for two decimal places.
	std::cout	<< dateStr << " => " << value << " = "
				<< std::fixed << std::setprecision(2) << totalValue
				<< std::endl;
}

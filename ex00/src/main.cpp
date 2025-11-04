/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:05:26 by lorey             #+#    #+#             */
/*   Updated: 2025/06/25 22:58:48 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int parseInput(std::ifstream &File, BitcoinExchange &btc) {
    std::string oneLine;
    std::size_t pos;

    std::getline(File, oneLine);
	if (oneLine != "date | value") {
		std::cerr << "Error: first line of input file not correct (data | value)" << std::endl;
		return (1);
	}
    while (std::getline(File, oneLine)) {
        pos = oneLine.find('|');
        if (pos != 11) {
            std::cerr << "Error: bad input ex: (2011-01-03 | 3) =>" << oneLine << std::endl;
            continue;
        }
        std::string dateStr = oneLine.substr(0, pos - 1);
        std::string valueStr = oneLine.substr(pos + 2);
        double value = strtod(valueStr.c_str(), NULL);

        if (value < 0) {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000.0) {
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
        if (year < 2009 || (year == 2009 && month == 1 && day == 1)  || year > 2025 || month < 1 || month > 12 || day < 1 || day > 31) {
            std::cerr << "Error: invalid date components => " << dateStr << std::endl;
            continue;
        }
		btc.doTheCompare(dateStr, value);
    }
	return (0);
}

int main(int argc, char **argv){
	std::map<std::string, double> input;
	if (argc != 2) {
		std::cout << "You must have a file and only a file as argument (./btc file.txt)" << std::endl;
		return (1);
	}
	
    std::ifstream File(argv[1]);
    if (!File.is_open()) {
        std::cerr << "Error: cannot open file" << std::endl;
        return (1);
    }
	
	BitcoinExchange bit;
	bit.parseCSV();
//	bit.writeCSV();
	if (parseInput(File, bit)) {
		return (1);
	}
}

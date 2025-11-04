/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <loic.rey.vs@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:05:26 by lorey             #+#    #+#             */
/*   Updated: 2025/06/27 22:17:04 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RPN.hpp"
int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "only one arg must be provided: \"8 9 * 9 - 9 - 9 - 9 - 4 - 1 +\"" << std::endl;
	}
	RPN salutATousCestFanta = RPN();

	std::cout << salutATousCestFanta.calcul(argv[1]) << std::endl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 02:56:46 by lorey             #+#    #+#             */
/*   Updated: 2025/06/27 22:23:07 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <cstdlib>

bool RPN::isOperator(char a) {
	return(a == '-' || a == '+' || a == '*' || a == '/');
}

double RPN::calcul(const std::string& expr) {
	size_t i = -1;
	double num1;
	double num2;
	double result;

	while (++i < expr.size()) {
		while (std::isspace(expr[i])) {
			i++;
		}
		if (expr[i] >= '0' && expr[i] <= '9') {
			this->_stack.push(expr[i] - '0');
		} else if(isOperator(expr[i])) {
			if (this->_stack.size() < 2) {
				std::cerr << "Error: Too less element in the stack to perform an operation" << std::endl;
				exit(1);
			} else {
				num2 = this->_stack.top();
				this->_stack.pop();
				num1 = this->_stack.top();
				this->_stack.pop();
				switch (expr[i]) {
					case '+':
						result = num1 + num2;
						break;
					case '-':
						result = num1 - num2;
						break;
					case '*':
						result = num1 * num2;
						break;
					case '/':
						result = num1 / num2;
						break;
				}
				this->_stack.push(result);
			}
		} else {
			std::cerr << "Error: Unauthortized character" << expr[i] << std::endl;
			exit(1);
		}
	}
	if (this->_stack.size() != 1) {
		std::cerr << "Error: There is more than one element is the stack after performing the operations" << std::endl;
		exit(1);
	}
	return (this->_stack.top());
}

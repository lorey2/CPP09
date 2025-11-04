/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 02:56:48 by lorey             #+#    #+#             */
/*   Updated: 2025/06/27 22:19:42 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <stack>
#include <string>
class RPN {
	private:
		std::stack<double> _stack;
	public:
		RPN(){};
		~RPN(){};
		RPN(const RPN& rpn){this->_stack = rpn._stack;};
		RPN& operator=(const RPN& rpn){this->_stack = rpn._stack; return *this;};
		double calcul(const std::string& expr);
		bool isOperator(char a);
};

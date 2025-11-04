/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:13:08 by lorey             #+#    #+#             */
/*   Updated: 2025/07/07 20:45:28 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <deque>
#include <vector>
class PmergeMe {
public:
	PmergeMe(int argc, char** argv);
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();
	void run();
private:
	PmergeMe();
	std::vector<int> _vec;
	std::deque<int> _deq;
	int _argc;
	char **_argv;
	void parseInput();
	template <typename Container>
	void fordJohnsonSort(Container &container);
	std::vector<int> generateJacobsthalNumbers(int limit);
	template <typename Container, typename T>
	typename Container::iterator binarySearch(Container& container, T value, typename Container::iterator end);
	void executeSort();
};

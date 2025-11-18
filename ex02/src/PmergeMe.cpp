/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:22:39 by lorey             #+#    #+#             */
/*   Updated: 2025/11/18 18:31:42 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>

PmergeMe::PmergeMe() : _argc(0), _argv(NULL) {}

PmergeMe::PmergeMe(int argc, char** argv) : _argc(argc), _argv(argv) {
	parseInput();
}

PmergeMe::PmergeMe(const PmergeMe& other) {
	*this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		this->_vec = other._vec;
		this->_deq = other._deq;
		this->_argc = other._argc;
		this->_argv = other._argv;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

//this is the only public function; the following ones are private

void PmergeMe::run() {
	executeSort();
}

//so private functions next


//this function is here to fill the deque and the vector
void PmergeMe::parseInput() {
	if (this->_argc < 2) {
		throw std::runtime_error("Error: one or zero arg provided. Program is irrelevant :)");
	}
	for (int i = 1; i < this->_argc; ++i) {
		std::stringstream ss(this->_argv[i]);
		int num;
		char remaining;
		if (!(ss >> num) || (ss >> remaining)) {
			throw std::runtime_error("Error: Input must be a sequence of integers");
		}
		this->_vec.push_back(num);
		this->_deq.push_back(num);
	}
}

//that is just some magic suit of numbers that are efficient
//understand that implies too much math
//I dont have time have fun if you want :)
//(create the suit is easy. Understand why it exist and why it is soo efficient is not in my mind)
std::vector<int> PmergeMe::generateJacobsthalNumbers(int limit) {
	std::vector<int> jacobsthal;
	if (limit <= 0) {
		return jacobsthal;
	}
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	int i = 2;
	while (true) {
		int next_jacobsthal = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];
		if (next_jacobsthal > limit) {
			break;
		}
		jacobsthal.push_back(next_jacobsthal);
		i++;
	}
	return jacobsthal;
}

//lower_bound
//used to find the index in which we insert
//envoie un itérateur pointant sur le premier élément qui est supérieur ou égal (>=) à la valeur que vous recherchez.
template <typename Container, typename T>
typename Container::iterator PmergeMe::binarySearch(Container& container, T value, typename Container::iterator end) {
	return std::lower_bound(container.begin(), end, value);
}

template <typename Container>
void PmergeMe::fordJohnsonSort(Container &container) {
	// base case for the recursion: a container with 0 or 1 element is already sorted.
	if (container.size() < 2) {
		return;
	}

	//in our case that is int but we can easily modify this to double later if we want
	typedef typename Container::value_type ValueType;
	//just a typedef for the line after
	typedef std::pair<ValueType, ValueType> Pair;

	//organize elements in group of two
	std::vector<Pair> pairs;
	//this contain an element if there is an odd number of elements
	ValueType straggler;
	bool hasStraggler = false;

	//handle the last element if the container has an odd number of elements.
	if (container.size() % 2 != 0) {
		hasStraggler = true;
		straggler = container.back();
		container.pop_back();
	}

	//after that the elements are groupped in sorted pairs
	for (size_t i = 0; i < container.size(); i += 2) {
		if (container[i] < container[i + 1]) {
			pairs.push_back(std::make_pair(container[i + 1], container[i]));
		} else {
			pairs.push_back(std::make_pair(container[i], container[i + 1]));
		}
	}

	//we take the biggest element of each pair and put it in a new container mainChain
	Container mainChain;
	for (size_t i = 0; i < pairs.size(); ++i) {
		mainChain.push_back(pairs[i].first);
	}

	//recursively sort the main chain of larger elements.
	fordJohnsonSort(mainChain);

	//now for each branch (recursion) we take the rest of the numbers put them in a Container pend
	//and use jakobsthal suit to insert them
	Container pend;

	//here we iter on each pair in mainChain and we take the second one
	//and Straggler if exist and put in a pend container
	//we need the nested loop to keep the right order that may have been changed with recursion
	for (size_t i = 0; i < mainChain.size(); ++i) {
		ValueType mainElement = mainChain[i];
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (pairs[j].first == mainElement) {
				pend.push_back(pairs[j].second);
			}
		}
	}

	if (hasStraggler) {
		pend.push_back(straggler);
	}
	
	//logically pend[0] is smaller than everything in mainChain
	//it can be in first place without any research:
	if (!pend.empty()) {
		mainChain.insert(mainChain.begin(), pend[0]);
	}


	// Insert the pending elements into the sorted main chain using the Jacobsthal sequence to determine the optimal insertion order.
    std::vector<int> jacobsthal = generateJacobsthalNumbers(pend.size());
	size_t last_inserted_count = 1;
	for (size_t k = 2; k < jacobsthal.size(); ++k) {
		int jacob_val = jacobsthal[k];
		size_t group_end_idx = std::min((size_t)jacob_val, pend.size());

		for (size_t i = group_end_idx; i > last_inserted_count; --i) {
			typename Container::iterator pend_element_it = pend.begin() + (i - 1);
			typename Container::iterator insertion_point = binarySearch(mainChain, *pend_element_it, mainChain.end());
			mainChain.insert(insertion_point, *pend_element_it);
		}
		last_inserted_count = group_end_idx;
	}

	for (size_t i = last_inserted_count + 1; i <= pend.size(); ++i) {
		typename Container::iterator pend_element_it = pend.begin() + (i - 1);
		typename Container::iterator insertion_point = binarySearch(mainChain, *pend_element_it, mainChain.end());
		mainChain.insert(insertion_point, *pend_element_it);
	}

	//at the end we set container to what we sort so we can access it outside
    container = mainChain;
}

void PmergeMe::executeSort() {
	std::cout << "Original data:		";
	for (int i = 1; this->_argv[i]; i++) {
		std::cout << this->_argv[i] << " ";
	}
	std::cout << std::endl;

	clock_t start_vec = clock();
	fordJohnsonSort(this->_vec);
	clock_t end_vec = clock();
	double vecTime = double(end_vec - start_vec) / CLOCKS_PER_SEC * 1000.0;

	clock_t start_deq = clock();
	fordJohnsonSort(this->_deq);
	clock_t end_deq = clock();
	double deqTime = double(end_deq - start_deq) / CLOCKS_PER_SEC * 1000.0;

	std::cout << "Sorted vector data:	";
	for (size_t i = 0; i < this->_vec.size(); i++) {
		std::cout << this->_vec[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Sorted deque data:	";
	for (size_t i = 0; i < this->_deq.size(); i++) {
		std::cout << this->_deq[i] << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Algorithm CPU time to sort " << _argc - 1 << "elements in vet : " << vecTime << " miliseconds" << std::endl;
	std::cout << "Algorithm CPU time to sort " << _argc - 1 << "elements in deque : " << deqTime << " miliseconds" << std::endl;
}


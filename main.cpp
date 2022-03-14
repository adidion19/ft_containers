/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:35:57 by adidion           #+#    #+#             */
/*   Updated: 2022/03/10 14:30:50 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector"
#include "vector.hpp"
#include "utils.hpp"

int main()
{
	std::cout << " ---- CONSTRUCTEUR ---- " << std::endl;
	/*delimiteur*/std::vector<int> a(5, 30);
	/*delimiteur*/std::vector<int> b = a;

	std::cout << " ---- CAPACITY ---- " << std::endl;
	std::cout << b.capacity() << std::endl;
	
	std::cout << " ---- PUSH BACK ---- " << std::endl;
	std::cout << "push:";
	for (int i = 0; i < 10000; i++)
	{
		b.push_back(i + 1);
		std::cout << " " << i + 1;
	}
	std::cout << std::endl;

	std::cout << " ---- CAPACITY ---- " << std::endl;
	std::cout << b.capacity() << std::endl;

	std::cout << " ---- OPERATOR [] ---- " << std::endl;
	for (int i = 0; i < 15; i++)
	{
		std::cout << "index " << i << ": " <<  b[i] << std::endl;
	}

	std::cout << " ---- AT ---- " << std::endl;
	try
	{
		for (int i = 0; i < 30; i++)
			std::cout << i << (i >= 10 ? "  " : "   ") << b.at(i) << std::endl;
	}
	catch(const std::out_of_range& e)
	{
		std::cerr << "Exception thrown: " << e.what() << '\n';
	}

	std::cout << " ---- FRONT ---- " << std::endl;
	std::cout << b.front() << std::endl;

	std::cout << " ---- BACK ---- " << std::endl;
	std::cout << b.back() << std::endl;

	std::cout << " ---- SIZE ---- " << std::endl;
	std::cout << b.size() << std::endl;

	std::cout << " ---- MAX_SIZE ---- " << std::endl;
	std::cout << b.max_size() << std::endl;

	std::cout << " ---- ITERATOR BEGIN ---- " << std::endl;
	std::cout << *b.begin() << std::endl;

	std::cout << " ---- ITERATOR END ---- " << std::endl;
	std::cout << *b.end() << std::endl;

	std::cout << " ---- REVERSE ITERATOR BEGIN ---- " << std::endl;
	std::cout << *b.rbegin() << std::endl;

	std::cout << " ---- REVERSE ITERATOR END ---- " << std::endl;
	std::cout << *b.rend() << std::endl;

	//std::iterator<int, char>
}
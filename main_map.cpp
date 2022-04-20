/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:19:10 by adidion           #+#    #+#             */
/*   Updated: 2022/04/20 17:04:17 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include <map>
#include <cstdlib>
#include "pair.hpp"

#define NAMESPACE ft // change to STD if you want to compare with the STL

int main()
{
	std::cout << "----DEFAULT CONSTRUCTOR----" << std::endl;
	NAMESPACE::map<int, float> a;
	std::cout << "----EMPTY----" << std::endl;
	std::cout << a.empty() << std::endl;
	std::cout << "----SIZE----" << std::endl;
	std::cout << a.size() << std::endl;
	std::cout << "----MAX_SIZE----" << std::endl;
	std::cout << "/!\\, the max size could be different from the STL, and that's normal" << std::endl;
	std::cout << a.max_size() << std::endl;
	std::cout << "----OPERATOR[] + INSERT----" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << a[i] << std::endl;
	}
	std::cout << "----EMPTY----" << std::endl;
	std::cout << a.empty() << std::endl;
	std::cout << "----SIZE----" << std::endl;
	std::cout << a.size() << std::endl;
	std::cout << "----OPERATOR[] + INSERT----" << std::endl;
	a.insert(NAMESPACE::make_pair(6, 0.35f));
	std::cout << "at the index 6, there is the value " << a[6] << std::endl;
	std::cout << "----EMPTY----" << std::endl;
	std::cout << a.empty() << std::endl;
	std::cout << "----SIZE----" << std::endl;
	std::cout << a.size() << std::endl;
	std::cout << "----COPY CONSTRUCTOR----" << std::endl;
	NAMESPACE::map<int, float> b(a);
	std::cout << "----CLEAR----" << std::endl;
	a.clear();
	std::cout << "----EMPTY----" << std::endl;
	std::cout << a.empty() << std::endl;
	std::cout << "----SIZE----" << std::endl;
	std::cout << a.size() << std::endl;
	std::cout << "----SWAP----" << std::endl;
	a.swap(b);
	std::cout << "----SIZE----" << std::endl;
	std::cout << a.size() << std::endl;
	std::cout << "----COUNT----" << std::endl;
	std::cout << "is 6th index existing ? " << a.count(6) << std::endl;
	std::cout << "is 98th index existing ? " << a.count(98) << std::endl;
	std::cout << "----CLEAR----" << std::endl;
	a.clear();
	std::cout << "----INSERT----" << std::endl;
	float f = 1.0f;
	int ran;
	srand(8500); // you can change the seed for other outputs, but I didn't want to set it on time to compare easily
	for (int i = 0; i < 20; i++)
	{
		ran = rand() % 10000;
		a.insert(a.begin(), NAMESPACE::make_pair(ran, f));
		f += 1.5f;
		std::cout << "at index " << ran << " : value = " << a[ran] << std::endl;
	}
	std::cout << "----CONSTRUCTOR WITH ITERATORS + BEGIN + END----" << std::endl;
	NAMESPACE::map<int, float> c(a.begin(), a.end());
	NAMESPACE::map<int, float>::iterator it = c.begin();
	for (unsigned int i = 0; i < c.size(); i++)
	{
		std::cout << "at index " << it->first << " : value = " << c[it->first] << std::endl;
		it++;
	}
	std::cout << "----CLEAR----" << std::endl;
	a.clear();
	std::cout << "----INSERT----" << std::endl;
	a.insert(c.begin(), c.end());
	it = a.begin();
	for (unsigned int i = 0; i < a.size(); i++)
	{
		std::cout << "at index " << it->first << " : value = " << a[it->first] << std::endl;
		it++;
	}
	std::cout << "----ERASE + FIND----" << std::endl;
	std::cout << "lets erase first element" << std::endl;
	a.erase(a.begin());
	std::cout << "lets erase element 6706" << std::endl;
	a.erase(6706);
	std::cout << "lets erase element 9445 to end" << std::endl;
	a.erase(a.find(9445), a.end());
	it = a.begin();
	for (unsigned int i = 0; i < a.size(); i++)
	{
		std::cout << "at index " << it->first << " : value = " << a[it->first] << std::endl;
		it++;
	}
	std::cout << "----UPPER_BOUND----" << std::endl;
	it = a.upper_bound(8429);
	std::cout << "at index " << it->first << " : value = " << a[it->first] << std::endl;
	std::cout << "----LOWER_BOUND----" << std::endl;
	it = a.lower_bound(4427);
	std::cout << "at index " << it->first << " : value = " << a[it->first] << std::endl;
	std::cout << "----EQUAL_RANGE----" << std::endl;
	NAMESPACE::pair<NAMESPACE::map<int, float>::iterator, NAMESPACE::map<int, float>::iterator> eq = a.equal_range(4427);
	std::cout << "lower_bound at index " << eq.first->first << " : value = " << a[eq.first->first] << std::endl;
	std::cout << "upper_bound at index " << eq.second->first << " : value = " << a[eq.second->first] << std::endl;
	std::cout << "----RBEGIN + REND----" << std::endl;
	NAMESPACE::map<int, float>::reverse_iterator rit = a.rbegin(), rite = a.rend();
	while (rit != rite)
	{
		std::cout << "at index " << rit->first << " : value = " << a[rit->first] << std::endl;
		rit++;
	}
	std::cout << "----OPERATORS----" << std::endl;
	std::cout << "a == c : "<< (a == c) << std::endl;
	std::cout << "a != c : "<< (a != c) << std::endl;
	std::cout << "a >= c : "<< (a >= c) << std::endl;
	std::cout << "a < c : "<< (a < c) << std::endl;
}
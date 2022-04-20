/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:52:51 by adidion           #+#    #+#             */
/*   Updated: 2022/04/20 14:45:35 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#include "stack.hpp"
#include <stack>
#include <string>
#include "map.hpp"
#include <map>
#include <cstdlib>
#include "pair.hpp"

#define NAMESPACE ft // change to STD if you want to compare with the STL

int main()
{
	std::cout << "VECTOR" << std::endl << std::endl;
	{
		std::cout << "~~~~TEST WITH INT~~~~~" << std::endl;
		NAMESPACE::vector<int> a;
		std::cout << "----MAX_SIZE----" << std::endl;
		std::cout << a.max_size() << " (is constant, no need to retest)" << std::endl;
		std::cout << "----SIZE----" << std::endl;
		std::cout << a.size() << std::endl;
		std::cout << "----CAPACITY----" << std::endl;
		std::cout << a.capacity() << std::endl;
		std::cout << "----EMPTY----" << std::endl;
		std::cout << a.empty() << std::endl;
		std::cout << "----PUSH_BACK + operator[] + RESERVE----" << std::endl;
		int j = 1;
		for (int i = 0; i < 30; i++)
		{
			a.push_back((j += 3) % 2 ? j : -j);
			std::cout << "Index " << i << " : value = " << a[i] << std::endl;
		}
		std::cout << "----SIZE----" << std::endl;
		std::cout << a.size() << std::endl;
		std::cout << "----CAPACITY----" << std::endl;
		std::cout << a.capacity() << std::endl;
		std::cout << "----EMPTY----" << std::endl;
		std::cout << a.empty() << std::endl;
		std::cout << "----RESERVE----" << std::endl;
		a.reserve(50);
		std::cout << "----SIZE----" << std::endl;
		std::cout << a.size() << std::endl;
		std::cout << "----CAPACITY----" << std::endl;
		std::cout << a.capacity() << std::endl;
		std::cout << "----AT----" << std::endl;
		std::cout << a.at(5) << std::endl;
		std::cout << a.at(15) << std::endl;
		try
		{
			std::cout << a.at(60) << std::endl;
			std::cerr << "it should throw an exception" << std::endl;
		}
		catch (std::out_of_range a)
		{
			std::cout << "An exception has been throw (and that's normal :p)" << std::endl;
		}
		std::cout << "----FRONT----" << std::endl;
		std::cout << a.front() << std::endl;
		std::cout << "----BACK----" << std::endl;
		std::cout << a.back() << std::endl;
		std::cout << "----COPY_CONSTRUCTOR----" << std::endl;
		NAMESPACE::vector<int> b(a);
		std::cout << "----ASSIGN----" << std::endl;
		std::cout << "before : size = " << a.size() << " && capacity = " << a.capacity() << std::endl;
		a.assign(10, 400);
		std::cout << "after : size = " << a.size() << " && capacity = " << a.capacity() << std::endl;
		std::cout << "----CLEAR----" << std::endl;
		a.clear();
		std::cout << "----SIZE----" << std::endl;
		std::cout << a.size() << std::endl;
		std::cout << "----OPERATOR=----" << std::endl;
		a = b;
		std::cout << "----SIZE----" << std::endl;
		std::cout << a.size() << std::endl;
		std::cout << "----POP_BACK + RESIZE----" << std::endl;
		for (int i = 0; i < 20; i++)
		{
			a.pop_back();
		}
		for (unsigned int i = 0; i < a.size(); i++)
		{
			std::cout << "Index " << i << " : value = " << a.at(i) << std::endl;
		}
		std::cout << "----INSERT + BEGIN + END----" << std::endl;
		std::cout << "lets remplace the value of the index 0 by 900" << std::endl;
		a.insert(a.begin(), 900);
		std::cout << "Index " << 0 << " : value = " << a[0] << std::endl;
		std::cout << "lets copy b in the end of a by using insert" << std::endl;
		a.insert(a.end(), b.begin(), b.end());
		std::cout << "lets add 5 x 200 to the result" << std::endl;
		a.insert(a.end(), 5, 200);
		for (unsigned int i = 0; i < a.size(); i++)
		{
			std::cout << "Index " << i << " : value = " << a[i] << std::endl;
		}
		std::cout << "----ERASE + BEGIN + END----" << std::endl;
		std::cout << "lets remove the end element" << std::endl;
		a.erase(a.end() - 1);
		std::cout << "lets remove the two first elements" << std::endl;
		NAMESPACE::vector<int>::iterator it = a.begin();
		it = it + 2;
		a.erase(a.begin(), it);
		for (unsigned int i = 0; i < a.size(); i++)
		{
			std::cout << "Index " << i << " : value = " << a.at(i) << std::endl;
		}
		std::cout << "----SWAP----" << std::endl;
		a.swap(b);
		for (unsigned int i = 0; i < a.size(); i++)
		{
			std::cout << "Index " << i << " : value = " << a.at(i) << std::endl;
		}
		std::cout << "----OPERATORS----" << std::endl;
		std::cout << "a == b : "<< (a == b) << std::endl;
		std::cout << "a != b : "<< (a != b) << std::endl;
		std::cout << "a > b : "<< (a > b) << std::endl;
		std::cout << "a < b : "<< (a < b) << std::endl;
		std::cout << "~~~~MINI TEST WITH CONST CHAR *~~~~" << std::endl;
		std::cout << "----CONSTRUCTOR WITH VALUE----" << std::endl;
		NAMESPACE::vector<const char *> c(4, "coucou");
		std::cout << "----CONSTRUCTOR WITH ITERATORS----" << std::endl;
		NAMESPACE::vector<const char *> d(c.begin(), c.end());
		for (unsigned int i = 0; i < d.size(); i++)
		{
			std::cout << "Index " << i << " : value = " << d[i] << std::endl;
		}
	}
	std::cout << "STACK" << std::endl << std::endl;
	{
		NAMESPACE::stack<int> a;
		std::cout << "~~~TEST WITH INT :~~~" << std::endl;
		std::cout << "----EMPTY----" << std::endl;
		std::cout << a.empty() << std::endl;
		std::cout << "----SIZE----" << std::endl;
		std::cout << a.size() << std::endl;
		std::cout << "----PUSH----" << std::endl;
		for (int i = 0; i < 30; i++)
		{
			a.push(i * 3);
			std::cout << "at index " << i << " : value = " << i * 3 << std::endl;
		}
		std::cout << "----EMPTY----" << std::endl;
		std::cout << a.empty() << std::endl;
		std::cout << "----SIZE----" << std::endl;
		std::cout << a.size() << std::endl;
		std::cout << "----TOP----" << std::endl;
		std::cout << a.top() << std::endl;
		std::cout << "----POP----" << std::endl;
		for (int i = 0; i < 5; i++)
		{
			a.pop();
		}
		std::cout << "----SIZE----" << std::endl;
		std::cout << a.size() << std::endl;
		std::cout << "----TOP----" << std::endl;
		std::cout << a.top() << std::endl;
		NAMESPACE::stack<float> b;
		std::cout << std::endl;
		std::cout << "~~~TEST WITH FLOAT :~~~" << std::endl;
		std::cout << "----EMPTY----" << std::endl;
		std::cout << b.empty() << std::endl;
		std::cout << "----SIZE----" << std::endl;
		std::cout << b.size() << std::endl;
		std::cout << "----PUSH----" << std::endl;
		float f = -0.5f;
		for (int i = 0; i < 30; i++)
		{
			b.push(f);
			std::cout << "at index " << i << " : value = " << f << std::endl;
			f += 0.6f;
		}
		std::cout << "----EMPTY----" << std::endl;
		std::cout << b.empty() << std::endl;
		std::cout << "----SIZE----" << std::endl;
		std::cout << b.size() << std::endl;
		std::cout << "----TOP----" << std::endl;
		std::cout << b.top() << std::endl;
		std::cout << "----POP----" << std::endl;
		for (int i = 0; i < 5; i++)
		{
			b.pop();
		}
		std::cout << "----SIZE----" << std::endl;
		std::cout << b.size() << std::endl;
		std::cout << "----TOP----" << std::endl;
		std::cout << b.top() << std::endl;
	}
	std::cout << "MAP" << std::endl << std::endl;
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
}
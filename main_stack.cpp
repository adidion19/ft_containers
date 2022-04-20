/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:53:49 by adidion           #+#    #+#             */
/*   Updated: 2022/04/19 14:24:24 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include <stack>
#include <string>

#define NAMESPACE std // to change to std if you want to compare with the STL

int main()
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
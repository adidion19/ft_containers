#include "binary_tree.hpp"
#include <map>
#include "map.hpp"
//#include "pair.hpp"



int main()
{
	// let us try to insert some data into tree and try to visualize the tree as well as traverse.
	ft::Binary_tree<char, int> a;
	a.insert(ft::pair<char, int>('a', 4));
	a.insert(ft::pair<char, int>('b', 52));
	a.insert(ft::pair<char, int>('x', 42));
	a.insert(ft::pair<char, int>('e', 554));
	a.ft_print();
	std::cout << std::endl;

	a.delete_one((ft::pair<char, int>('a', 4)));
	a.delete_one((ft::pair<char, int>('b', 4)));

	a.ft_print();
}
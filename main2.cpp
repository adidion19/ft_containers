#include "binary_tree.hpp"
#include <map>



int main()
{
	// let us try to insert some data into tree and try to visualize the tree as well as traverse.
	Binary_tree<char, int> a;

	a.insert(ft::pair<char, int>('a', 4));
	a.insert(ft::pair<char, int>('b', 50));
	a.insert(ft::pair<char, int>('c', 49));
	a.insert(ft::pair<char, int>('d', 89));
	a.insert(ft::pair<char, int>('e', 89));
	a.delete_one(ft::pair<char, int>('a', 4));
}
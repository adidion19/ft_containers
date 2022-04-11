#include "binary_tree.hpp"
#include <map>
#include "map.hpp"
//#include "pair.hpp"



int main()
{
	// let us try to insert some data into tree and try to visualize the tree as well as traverse.
	ft::Binary_tree<const char, const char*> a;
	a.insert(ft::pair<const char, const char*>('a', "abc"));
	a.insert(ft::pair<const char, const char*>('b', "abcdef"));
	a.insert(ft::pair<const char, const char*>('x', "abcg"));
	a.insert(ft::pair<const char, const char*>('e', "abch"));
	a.ft_print();
	ft::Binary_tree<const char, const char*> b;
	//b = a;
	std::cout << std::endl;


	a.ft_print();

	//b.insert(ft::pair<const char, const char*>('x', "abci"));
	//b.insert(ft::pair<const char, const char*>('a', "abcj"));
	//b.insert(ft::pair<const char, const char*>('v', "abck"));
	//b.insert(ft::pair<const char, const char*>('v', "abcl"));
	//b.insert(ft::pair<const char, const char*>('w', "abcm"));
	//b.insert(ft::pair<const char, const char*>('v', "abcn"));
	std::cout << std::endl;
	//b.ft_print();
	ft::Binary_tree<const char, const char*> c;
	c = a;
	a.delete_one('a');
	a.delete_one('b');
	std::cout << std::endl;
	a.ft_print();
	c.delete_one('a');
	c.delete_one('b');
	c.delete_one('c');
	c.delete_one('x');
	c.delete_one('e');
	std::cout << std::endl;
	c.ft_print();
	std::cout << std::endl;
	b.ft_print();
}
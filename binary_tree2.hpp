/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree2.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:49:06 by adidion           #+#    #+#             */
/*   Updated: 2022/04/14 12:59:53 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE2_HPP
# define BINARY_TREE2_HPP

# include "pair.hpp"
# include "map_iterator2.hpp"

namespace ft
{
	template<class Key, class T>
	class Node
	{
		public:
			ft::pair<const Key,T>	data;
			Node *					left;
			Node *					right;
			Node *					parent;
			size_t					hight;
	};
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> >, class Node = Node<const Key, T> >
	class Binary_tree
	{
		public :
			typedef Key													key_type;
			typedef T													mapped_type;
			typedef Compare												key_compare;
			typedef ft::pair<const Key,T>								value_type;
			typedef std::allocator<ft::Node<const Key,T> >				allocator_type_node;
			typedef std::allocator<ft::pair<const Key,T> >				allocator_type;
			typedef size_t												size_type;
			typedef int													difference_type;
			typedef ft::map_iterator<value_type, Node>					iterator;
			typedef ft::map_iterator<const value_type, Node>			const_iterator;
			//typedef ft::map_reverse_iterator<value_type, Node>			reverse_iterator;
			//typedef ft::map_reverse_iterator<const value_type, Node>	const_reverse_iterator;
		private:
			Node *null_node;
			Node *root;
			key_compare _k;
			allocator_type _alloc;
			allocator_type_node _alloc_node;
		public:
			Binary_tree(const key_compare& cmp = key_compare(), const allocator_type& alloc = allocator_type()) : _k(cmp), _alloc(alloc)
			{
				null_node = alloc_node(value_type());
				null_node->parent = NULL;
				null_node->right = NULL;
				null_node->left = NULL;
				null_node->hight = 0;
				root = null_node;
			}
			~Binary_tree()
			{
				ft_free(begin(), end());
				_alloc_node.deallocate(null_node, 1);
			}
			Binary_tree& operator=(const Binary_tree& obj)
			{
				ft_free(begin(), end());
				const_iterator it = obj.begin(), ite = obj.end();
				while (it != ite)
				{
					insert(ft::make_pair(it->first, it->second));
					it++;
				}
				return (*this);
			}
			ft::pair<iterator, bool> insert(value_type p)
			{
				if (root == null_node)
				{
					root = insert_node(root, p);
					return (ft::make_pair(iterator(root, null_node, root), true));
				}
				else
				{
					Node *node = ft_min(root);
					while (_k(node->data.first, ft_max(root)->data.first))
					{
						if (node->data.first == p.first)
							return(ft::make_pair(iterator(node, null_node, root), false));
						node = ft_next(node);
					}
					if (ft_max(root)->data.first == p.first)
						return(ft::make_pair(iterator(node, null_node, root), false));
					root = insert_node(root, p);
					node = ft_min(root);
					while (node != null_node)
					{
						if (node->data.first == p.first)
							break ;
						node = ft_next(node);
					}
					return (ft::make_pair(iterator(node, null_node, root), true));
				}
			}
			Node * alloc_node(value_type i)
			{
				Node *node = _alloc_node.allocate(1);
				_alloc.construct(&node->data, i);
				node->left = null_node;
				node->right = null_node;
				node->parent = NULL;
				node->hight = 1;
				return (node);
			}
			Node *insert_node(Node *node, ft::pair<const Key,T> pair)
			{
				if (root == null_node)
				{
					root = alloc_node(pair);
					return (root);
				}
				if (node == null_node)
				{
					node = alloc_node(pair);
					return (node);
				}
				if (_k(pair.first, node->data.first))
				{
					node->left = insert_node(node->left, pair);
					node->left->parent = node;
				}
				else if (_k(node->data.first, pair.first))
				{
					node->right = insert_node(node->right, pair);
					node->right->parent = node;
				}
				return (sort_tree(node));
			}
			Node *delete_node(Node *node, key_type type)
			{
				if (root == null_node)
					return (root);
				if (node == null_node)
					return (node);
				if (_k(type, node->data.first))
					node->left = delete_node(node->left, type);
				else if (_k(node->data.first, type))
					node->right = delete_node(node->right, type);
				else
				{
					Node *tmp = null_node;
					if (node->left == null_node || node->right == null_node)
					{
						if (node->left != null_node)
							tmp = node->left;
						else
							tmp = node->right;
						if (tmp == null_node)
						{
							tmp = node;
							node = null_node;
						}
						else
						{
							if (node->left != null_node)
							{
								Node *tmp2 = node->parent;
								tmp = node;
								node = node->left;
								node->parent = tmp2;
							}
							else if (node->right != null_node)
							{
								Node *tmp2 = node->parent;
								tmp = node;
								node = node->right;
								node->parent = tmp2;
							}
						}
						if (!tmp->parent && tmp->left == null_node && tmp->right == null_node)
						{
							_alloc.destroy(&tmp->data);
							_alloc_node.deallocate(tmp, 1);
							root = null_node;
						}
						else
						{
							if (root == tmp)
								root = node;
							_alloc.destroy(&tmp->data);
							_alloc_node.deallocate(tmp, 1);
						}
					}
					else if (node->left != null_node && node->right != null_node)
					{
						tmp = ft_min(node->right);
						_alloc.destroy(&node->data);
						_alloc.construct(&node->data, tmp->data);
						node->right = delete_node(node->right, node->data.first);
					}
				}
				if (node == null_node)
					return (node);
				return (sort_tree(node));
			}
			int ft_sort(Node *node)
			{
				if (node == null_node || !node)
					return (0);
				return (hight(node->left) - hight(node->right));
			}
			Node *sort_tree(Node * node)
			{
				node->hight = hight(node);
				int sort = ft_sort(node);
				if (sort > 1 && ft_sort(node->left) >= 0)
					node = right_rotate(node);
				if (sort > 1 && ft_sort(node->left) < 0)
				{
					node->left = left_rotate(node->left);
					node = right_rotate(node);
				}
				if (sort < -1 && ft_sort(node->right) <= 0)
					node = left_rotate(node);
				if (sort < -1 && ft_sort(node->right) > 0)
				{
					node->right = right_rotate(node->right);
					node = left_rotate(node);
				}
				return (node);
			}
			size_t ft_highest(size_t i, size_t j)
			{
				if (_k(j, i))
					return (i);
				return (j);
			}
			size_t hight(Node* node)
			{
				if (node == null_node)
					node->hight = 0;
				else if (node->left == null_node && node->right == null_node)
					node->hight = 1;
				else if (node->left == null_node && node->right != null_node)
					node->hight = node->right->hight + 1;
				else if (node->left != null_node && node->right == null_node)
					node->hight = node->left->hight + 1;
				else
					node->hight = ft_highest(node->left->hight, node->right->hight) + 1;
				return (node->hight);
			}
			Node *left_rotate(Node *node)
			{
				Node *node2 = node->right;
				Node *child_left = node2->left;
				Node *tmp = node->parent;
				node2->left = node;
				node->right = child_left;
				node->hight = hight(node);
				node2->hight = hight(node2);
				child_left->hight = hight(child_left);
				node->parent = node2;
				node2->parent = tmp;
				child_left->parent = node;
				if (!node2->parent)
					root = node2;
				return (node2);
			}
			Node *right_rotate(Node *node)
			{
				Node *node2 = node->left;
				Node *child_right = node2->right;
				Node *tmp = node->parent;
				node2->right = node;
				node->left = child_right;
				node->hight = hight(node);
				node2->hight = hight(node2);
				child_right->hight = hight(child_right);
				node->parent = node2;
				node2->parent = tmp;
				child_right->parent = node;
				if (!node2->parent)
					root = node2;
				return (node2);
			}
			const_iterator	ft_find(const key_type& k)
			{
				if (root == null_node)
					return (end());
				Node *max = ft_max(root);
				Node *min = ft_min(root);
				while(min != max)
				{
					if (min->data.first == k)
						return(const_iterator(min, null_node, root));
					min = ft_next(min);
				}
				if (max->data.first == k)
					return(const_iterator(max, null_node, root));
				else
					return (end());
			}
			Node* ft_next(Node * node) const
			{
				Node *tmp;
				if (node->right == null_node)
				{
					tmp = node;
					while (tmp->parent && tmp == tmp->parent->right)
						tmp = tmp->parent;
					tmp = tmp->parent;
					return (tmp);
				}
				tmp = node->right;
				while (tmp->left != null_node)
					tmp = tmp->left;
				return (tmp);
			}
			void ft_free(iterator it, iterator ite)
			{
				while(it != ite)
				{
					Node *max = ft_max(root);
					Node *min = ft_min(root);
					Node *tmp = null_node;
					while (min != max)
					{
						if (min->data.first == it->first)
							tmp = ft_search(min);
						min = ft_search(min);
					}
					if (max->data.first == it->first)
						tmp = null_node;
					
					delete_node(root, it->first);
					iterator tmp2(tmp, null_node, root);
					it = tmp2;
				}
			}
			size_type	ft_count(const key_type& k)
			{
				const_iterator it = ft_find(k);
				if (ft_find(k) == end())
					return (0);
				return (1);
			}
			void delete_one (const key_type& i)
			{
				size_type ret  = 0;
				if (ft_count(i))
					ret = 1;
				delete_node(root, i);
				return ;
			}
			Node* ft_min(Node *node) const
			{
				if (node->left && node->left != null_node)
					return (ft_min(node->left));
				return (node);
			}
			Node* ft_max(Node *node) const
			{
				if (node->right && node->right != null_node)
					return (ft_min(node->right));
				return (node);
			}
			Node* ft_search(Node * node) const
			{
				Node *tmp;
				if (node->right == null_node)
				{
					tmp = node;
					while (tmp->parent && tmp == tmp->parent->right)
						tmp = tmp->parent;
					tmp = tmp->parent;
					return (tmp);
				}
				tmp = node->right;
				while (tmp->left != null_node)
					tmp = tmp->left;
				return (tmp);
			}
			iterator begin()
			{
				if (root == null_node)
					return (iterator(root, null_node, root));
				Node *tmp = ft_min(root);
				return (iterator(tmp, null_node, root));
			}
			iterator end()
			{
				return (iterator(null_node, null_node, root));
			}
			const_iterator begin() const
			{
				if (root == null_node)
					return (const_iterator(root, null_node, root));
				Node *tmp = ft_min(root);
				return (const_iterator(tmp, null_node, root));
			}
			const_iterator end() const
			{
				return (const_iterator(null_node, null_node, root));
			}
			unsigned int size() const
			{
				unsigned int size = 0;
				for(const_iterator it = this->begin(); it !=this->end(); ++it)
					size++;
				return (size);
			}
			unsigned int ft_count(Node *node, unsigned int *i) const
			{
				if (node != null_node && node->left != null_node)
					ft_count(root->left, i);
				if (node != null_node && node->right != null_node)
					ft_count(node->right, i);
				if (node != null_node)
					(*i)++;
				return (*i);
			}
			T search(const Key &n)
			{
				Node *tmp = root;
				while (tmp != null_node)
				{
					if (n < tmp->data.first)
					{
						if (tmp->left == null_node)
							return (0);
						tmp = tmp->left;
					}
					else if (n == tmp->data.first)
						return (tmp->data.second);
					else
					{
						if (tmp->right == null_node)
							return (0);
						else
							tmp = tmp->right;
					}
					return (tmp->data.second);
				}
				return (0);
			}
			// FOR ME
			void ft_print(Node*node)
			{
				if (node != null_node)
				{
					ft_print(node->left);
					ft_print(node->right);
					std::cout << node->data.second << std::endl;
				}
			}
			void ft_print()
			{
				if (root != null_node)
				{
					ft_print(root->left);
					ft_print(root->right);
					std::cout << "root : " << root->data.second << std::endl;
				}
			}
	};
}

#endif

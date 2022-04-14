/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator2.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:36:55 by adidion           #+#    #+#             */
/*   Updated: 2022/04/14 13:30:08 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR2_HPP
#define MAP_ITERATOR2_HPP

#include "iterator.hpp"
#include "binary_tree2.hpp"
# include "utils.hpp"
#include "pair.hpp"

namespace ft
{
	template<typename value_type, typename Node>
	class map_reverse_iterator;

	template<typename value_type, typename Node>
	class map_iterator
	{
		public:
			typedef std::random_access_iterator_tag			iterator_category;
			typedef value_type&								reference;
			typedef value_type*								pointer;
			typedef	typename value_type::first_type			key_type;
			typedef map_iterator<value_type, Node>			iterator_type;
			typedef	typename value_type::second_type		mapped_type;
			typedef size_t									size_type;
			typedef int										difference_type;
			//typedef ft::pair<const key_type,mapped_type>a	value_type;
		private:
			Node *root;
			Node *null_node;
			Node *a;
			Node *ft_next(Node *node)
			{
				Node *tmp;
				if (node->right == null_node)
				{
					tmp = node;
					while (tmp->parent && tmp == tmp->parent->right)
						tmp = tmp->parent;
					tmp = tmp ->parent;
					return (tmp);
				}
				tmp = node->right;
				while (tmp->left != null_node)
					tmp = tmp->left;
				return (tmp);
			}
			Node *ft_previous(Node *node)
			{
				Node *tmp;
				if (node->left == null_node || !node->left)
				{
					tmp = node;
					while (tmp->parent && tmp == tmp->parent->left)
						tmp = tmp->parent;
					tmp = tmp ->parent;
					return (tmp);
				}
				tmp = node->left;
				while (tmp->right != null_node)
					tmp = tmp->right;
				return (tmp);
			}
			Node *ft_max(Node *node) const
			{
				if (node == null_node)
					return (node);
				if (node->right && node->right != null_node)
					return (ft_max(node->right));
				return (node);
			}
			Node *ft_min(Node *node) const
			{
				if (node->left && node->left != null_node)
					return (ft_min(node->left));
				return (node);
			}
		public:
			map_iterator(): root(NULL), null_node(NULL), a(NULL)
			{
				return ;
			}
			map_iterator(Node *b, Node *n, Node *r): root(r), null_node(n), a(b)
			{
				return ;
			}
			map_iterator(const map_iterator<value_type, Node> & obj): root(obj.root), null_node(obj.null_node), a(obj.a)
			{
				return ;
			}
			~map_iterator()
			{
				return ;
			}
			map_iterator &operator=(const map_iterator &obj)
			{
				null_node = obj.null_node;
				root = obj.root;
				a = obj.a;
				return (*this);
			}
			reference operator*() const
			{
				return (a->data);
			}
			Node *base() const
			{
				return (a);
			}
			pointer operator->() const
			{
				return (&(a)->data);
			}
			operator	map_iterator<value_type const, Node>() const
			{
				return (map_iterator<value_type const, Node>(a, null_node, root));
			}
			map_iterator& operator++()
			{
				if(a == null_node)
					a = ft_min(root);
				else if (a == ft_max(root))
					a = null_node;
				else
					a = ft_next(a);
				return (*this);
			}
			map_iterator operator++(int)
			{
				map_iterator<value_type, Node> tmp(*this);
				operator++();
				return (tmp);
			}
			map_iterator& operator--()
			{
				if (a == null_node)
					a = ft_max(root);
				else
					a = ft_previous(a);
				return (*this);
			}
			map_iterator operator--(int)
			{
				map_iterator<value_type, Node> tmp(*this);
				operator--();
				return (tmp);
			}
			bool operator==(const map_iterator &obj) const
			{
				return (a == obj.a);
			}

			bool operator!=(const map_iterator &obj) const
			{
				return (a != obj.a);
			}
	};
}

#endif
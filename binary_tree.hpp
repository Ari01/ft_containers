/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:19:20 by dchheang          #+#    #+#             */
/*   Updated: 2022/04/06 11:07:57 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <memory>
#include "utils.hpp"
#include "iterator.hpp"

/***** NODE *****/
template <typename T>
struct Node
{
	typedef T	value_type;

	Node*		parent;
	Node*		left;
	Node*		right;
	bool		color;
	value_type	val;

	// init const
	Node(value_type const& v = value_type(), Node *p = NULL, Node *l = NULL, Node *r = NULL, bool c = 0) :
		parent(p), left(l), right(r), color(c), val(v) {}

	// copy const
	Node(const Node& x) :
		parent(x.parent), left(x.left), right(x.right), color(x.color), val(x.val) {}

	// destructor
	~Node() {}

	// operator=
	Node&	operator=(Node const& x)
	{
		if (this != &x)
		{
			parent = x.parent;
			left = x.left;
			right = x.right;
			color = x.color;
			val = x.val;
		}
		return (*this);
	}
};

/***** BINARY TREE *****/
template <class T, class Compare = std::less<T>, 
			class Node = Node<T>, class Alloc = std::allocator<Node> >
class BinaryTree
{
	public:
		typedef T											value_type;
		typedef Node										node_type;
		typedef Alloc										allocator_type;
		typedef Compare										value_compare;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;

	private:
		pointer			root;
		value_compare	comp;
		allocator_type	alloc;

	public:
		// default const
		BinaryTree(const value_compare& c = value_compare(),
					const allocator_type& a = allocator_type())
					: root(NULL), comp(c), alloc(a) {}

		// destructor
		~BinaryTree()
		{
			destroy(root);	
		}

		// accessors
		pointer	getRoot() const
		{
			return (root);
		}

		/* find : uses function comp to search if a key is present in the tree
		** @param : k, the key to find
		** @return : a pointer to the elem whose key match k if it exists
		** otherwhise, returns NULL */
		pointer	find(const value_type &val)
		{
			pointer x = root;

			while (x != NULL)
			{
				if (comp(val, x->val))
					x = x->left;
				else if (comp(x->val, val))
					x = x->right;
				else
					return (x);
			}
			return (NULL);
		}

		/* insert (val) : uses function comp to insert an element at the right position in the tree
		** @param val : the value to insert
		** @return : if the key of the elem to insert already exists in the tree, returns NULL
		** otherwhise, returns a pointer to the new element inserted */
		ft::pair<pointer, bool>	insert(const value_type& val)
		{
			pointer	x = root;
			pointer y = NULL;

			while (x != NULL)
			{
				y = x;
				if (comp(val, x->val))
					x = x->left;
				else if (comp(x->val, val))
					x = x->right;
				else
					return (ft::make_pair(x, false));
			}
			x = alloc.allocate(1);
			alloc.construct(x, Node(val, y));
			if (y == NULL)
				root = x;
			else if (comp(val, y->val))
				y->left = x;
			else
				y->right = x;
			return (ft::make_pair(x, true));
		}

		pointer	insert(pointer position, const value_type& val)
		{
			pointer	ret;

			if (comp(val, position->val))
				return (insert(val).first);
			else if (comp(position->val, val))
			{
				if (!position->right || comp(val, position->right))
				{
					ret = alloc.allocate(1);
					alloc.construct(ret, Node(val, position, NULL, position->right));
					position->right = ret;
				}
				else
					return (insert(val).first);
			}
			return (position);
		}

		/* min : returns min key found in tree or NULL if no key was found */
		pointer	min(pointer x) const
		{
			while (x->left != NULL)
				x = x->left;
			return (x);
		}

		/* max : same as min but returns max key */
		pointer	max(pointer x)
		{
			while (x->right != NULL)
				x = x->right;
			return (x);
		}

		/* predecessor
		**@return : a pointer to the elem in the tree with the largest key smaller than x's key */
		pointer	predecessor(pointer x)
		{
			pointer y;

			if (x->left != NULL)
				return (max(x->left));
			y = x->parent;
			while (y != NULL && x == y->left)
			{
				x = y;
				y = y->parent;
			}
			return (y);
		}

		/* successor : same as predecessor but returns the smallest key greater than x's key */
		pointer	successor(pointer x)
		{
			pointer	y;

			if (x->right != NULL)
				return (min(x->right));
			y = x->parent;
			while (y != NULL && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return (y);
		}

		/* shift : switch positions of u and v in the tree according to their parents */
		void	shift(pointer u, pointer v)
		{
			if (u->parent == NULL)
				root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			if (v != NULL)
				v->parent = u->parent;
		}

		/* erase : removes del from the tree, abiding to three cases
		** (1) if del is a leaf, del's parent pointer to del is replaced with nil
		** (2) if del has only one child, the child gets elevated as child of del's parent
		** (3) if del has two children, the successor y of del takes the position of del in the tree
		** (3a) if y is the immediate right child of del, y gets elevated
		** and y's left child points to del's initial left subtree
		** (3b) else, position of y and its right child are switched and y takes the position of del
		*/
		void	erase(pointer del)
		{
			pointer	y;

			if (del->left == NULL)
				shift(del, del->right);
			else if (del->right == NULL)
				shift(del, del->left);
			else
			{
				y = successor(del);
				if (y->parent != del)
				{
					shift(y, y->right);
					y->right = del->right;
					y->right->parent = y;
				}
				shift(del, y);
				y->left = del->left;
				y->left->parent = y;
			}
			alloc.destroy(del);
			alloc.deallocate(del, 1);
		}

		void	destroy(pointer root)
		{
			if (root)
			{
				destroy(root->left);
				destroy(root->right);
				alloc.destroy(root);
				alloc.deallocate(root, 1);
			}
		}
};


/***** TREE ITERATOR ********/
template <typename T>
class TreeIte : public ft::iterator<ft::bidirectional_iterator_tag,T>
{
	friend class BinaryTree<T>;

	public:
		typedef Node<T>*																	node_pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type		value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference			reference;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;

	protected:
		node_pointer node;

	public:
		// CONSTS DESTS
		TreeIte() : node(NULL) {}
		TreeIte(node_pointer p) : node(p) {}
		TreeIte(TreeIte const& other) : node(other.node) {}
		TreeIte &operator=(TreeIte const& other)
		{
			if (this != &other)
				node = other.node;
			return (*this);
		}
		~TreeIte() {}

		// ACCESSORS
		node_pointer	base() const
		{
			return (node);
		}

		// MEMBER OPERATORS
		reference	operator*()
		{
			return (node->val);
		}

		pointer	operator->()
		{
			return (&(operator*()));
		}

		TreeIte &operator++()
		{
			node = successor(node);
			return (*this);
		}

		TreeIte operator++(int)
		{
			TreeIte tmp(*this);

			node = successor(node);
			return (tmp);
		}

		TreeIte &operator--()
		{
			node = predecessor(node);
			return (*this);
		}

		TreeIte operator--(int)
		{
			TreeIte tmp(*this);

			node = predecessor(node);
			return (tmp);
		}

		// NON MEMBER OPERATORS
		friend bool operator==(TreeIte const& lhs, TreeIte const& rhs)
		{
			return (lhs.node == rhs.node);
		}

		friend bool operator!=(TreeIte const& lhs, TreeIte const& rhs)
		{
			return (lhs.node != rhs.node);
		}
};

#endif

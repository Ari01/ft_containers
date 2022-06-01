/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:19:20 by dchheang          #+#    #+#             */
/*   Updated: 2022/06/01 08:17:28 by dchheang         ###   ########.fr       */
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
		size_type		_size;

	public:
		// default const
		BinaryTree(const value_compare& c = value_compare(),
					const allocator_type& a = allocator_type())
					: root(NULL), comp(c), alloc(a), _size(0) {}

		BinaryTree(BinaryTree const& x) : root(NULL), comp(x.comp), alloc(x.alloc), _size(0)
		{
			*this = x;
		}

		// operator=
		BinaryTree	&operator=(BinaryTree const& x)
		{
			pointer		i;
			pointer		j;
			pointer		tmp;
			
			if (this != &x)
			{
				i = min(x.root);
				j = min(root);
				tmp = j;
				while (i && j)
				{
					tmp = j;
					alloc.destroy(j);
					alloc.construct(j, Node(i->val, tmp->parent, tmp->left, tmp->right));
					j = successor(tmp);
					i = successor(i);
				}
				while (i)
				{
					tmp = insert(tmp, i->val);
					i = successor(i);
				}
				while (j)
				{
					tmp = successor(j);
					erase(j);
					j = tmp;
				}
				_size = x._size;
			}
			return (*this);
		}

		// destructor
		~BinaryTree()
		{
			destroy(&root);	
		}

		// accessors
		/* root */
		pointer	getRoot() const
		{
			return (root);
		}

		/* alloc */
		allocator_type	getAlloc() const
		{
			return (alloc);
		}

		/* size */
		size_type	size() const
		{
			return (_size);
		}

		void	setSize(size_type n)
		{
			_size = n;
		}

		/* find : uses function comp to search if a key is present in the tree
		** @param : k, the key to find
		** @return : a pointer to the elem whose key match k if it exists
		** otherwhise, returns NULL */
		pointer	find(const value_type &val) const
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
			_size++;
			if (y == NULL)
				root = x;
			else if (comp(val, y->val))
				y->left = x;
			else
				y->right = x;
			return (ft::make_pair(x, true));
		}

		/* insert (position) : if position precedes the new elem to insert, it is inserted after pos
		** else calls insert(val)
		** @param position : the position to insert the elem after 
		** @param val : the elem to insert
		** @return : a pointer to the newly inserted elem or to the existing elem if it existed */
		pointer	insert(pointer position, const value_type& val)
		{
			pointer	ret;
			pointer	successor_ptr;

			if (position && comp(position->val, val))
			{
				successor_ptr = successor(position);
				if (!successor_ptr || comp(val, successor_ptr->val))
				{
					ret = alloc.allocate(1);
					if (!successor_ptr)
					{
						alloc.construct(ret, Node(val, position));
						position->right = ret;
					}
					else
					{
						alloc.construct(ret, Node(val, successor_ptr->parent, NULL, successor_ptr));
						successor_ptr->parent->right = ret;
						successor_ptr->parent = ret;
					}
					_size++;

					return (ret);
				}
			}
			return (insert(val).first);
		}

		/* min : returns min key found in tree or NULL if no key was found */
		static pointer	min(pointer x)
		{
			while (x != NULL && x->left != NULL)
				x = x->left;
			return (x);
		}

		/* max : same as min but returns max key */
		static pointer	max(pointer x)
		{
			while (x != NULL && x->right != NULL)
				x = x->right;
			return (x);
		}

		/* predecessor
		**@return : a pointer to the elem in the tree with the largest key smaller than x's key */
		static pointer	predecessor(pointer x)
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
		static pointer	successor(pointer x)
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
			_size--;
		}

		void	swap(BinaryTree &x)
		{
			pointer		ptrtmp;
			size_type	sizetmp;

			ptrtmp = root;
			sizetmp = _size;
			root = x.root;
			_size = x._size;
			x.root = ptrtmp;
			x._size = sizetmp;
		}

		/* destroy (void) : destroys and deallocates all ndoes from the tree, size left at 0 */
		void	destroy()
		{
			destroy(&root);
		}

		/* destroy (pointer) 
		** destroys and deallocates all nodes from the subtree pointed by node 
		** modifies size accordingly */
		void	destroy(pointer *node)
		{
			if (node && *node != NULL)
			{
				destroy(&(*node)->left);
				destroy(&(*node)->right);
				alloc.destroy(*node);
				alloc.deallocate(*node, 1);
				*node = NULL;
				_size--;
			}
		}
};


/***** TREE ITERATOR ********/
template <typename T, typename node_type>
class TreeIte : public ft::iterator<ft::bidirectional_iterator_tag, T>
{
	public:
		typedef node_type*																	node_pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type		value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference			reference;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;

	protected:
		node_pointer	node;
		node_pointer	root;

	public:
		// default const
		TreeIte() : node(NULL), root(NULL) {}

		// node const
		TreeIte(node_pointer n, node_pointer r)
		{
			node = n;
			root = r;
		}

		// implicit conversion from T to const T
		operator TreeIte<const T, node_type>() const
		{
			return (TreeIte<const T, node_type>(node, root));
		}

		// copy const
		TreeIte(TreeIte const& other)
		{
			*this = other;
		}

		// operator=
		TreeIte &operator=(const TreeIte& other)
		{
			if (this != &other)
			{
				node = other.node;
				root = other.root;
			}
			return (*this);
		}

/*		template <typename T2>
		TreeIte	&operator=(TreeIte<T2, node_type> const& other)
		{
			node = other.node;
			root = other.root;
			return (*this);
		}*/

		// destructor
		~TreeIte() {}

		// ACCESSORS
		node_pointer	base() const
		{
			return (node);
		}

		node_pointer	get_root() const
		{
			return (root);
		}

		// MEMBER OPERATORS
		reference	operator*() const
		{
			return (node->val);
		}

		pointer	operator->() const
		{
			return (&(operator*()));
		}

		TreeIte &operator++()
		{
			node = BinaryTree<T, std::less<T>, node_type>::successor(node);
			return (*this);
		}

		TreeIte operator++(int)
		{
			TreeIte tmp(*this);

			operator++();
			return (tmp);
		}

		TreeIte &operator--()
		{
			if (!node)
				node = BinaryTree<T, std::less<T>, node_type>::max(root);
			else
				node = BinaryTree<T, std::less<T>, node_type>::predecessor(node);
			return (*this);
		}

		TreeIte operator--(int)
		{
			TreeIte tmp(*this);

			operator--();
			return (tmp);
		}

		// NON MEMBER OPERATORS
	/*	friend bool operator==(TreeIte const& lhs, TreeIte const& rhs)
		{
			return (lhs.node == rhs.node);
		}*/

		template <typename T2>
		friend bool operator==(TreeIte const& lhs, TreeIte<T2, node_type> const& rhs)
		{
			return (lhs.base() == rhs.base());
		}

	/*	friend bool operator!=(TreeIte const& lhs, TreeIte const& rhs)
		{
			return (lhs.node != rhs.node);
		}*/

		template <typename T2>
		friend bool operator!=(TreeIte const& lhs, TreeIte<T2, node_type> const& rhs)
		{
			return (lhs.base() != rhs.base());
		}
};

#endif

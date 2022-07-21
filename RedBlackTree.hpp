#pragma once
#include <iostream>
#include <memory>
#include "Colors.hpp"
#include "pair.hpp"
// #include "BidirectionalIterator.hpp"
#include "IteratorsTraits.hpp"
#include "RbIterator.hpp"
#include "RbReverseIterator.hpp"
#include "Utility.hpp"
#define RED_N 1
#define BLACK_N 0

namespace ft
{

	// template <class T1, class T2>
	// std::ostream& operator <<(std::ostream& os, const ft::pair<T1, T2>& my_pair)
	// {
	// 	os << "first: " << my_pair.first << " " << "second: " << my_pair.second ;
	// 	return os;
	// }

	template< class T = ft::pair < const class L, class Key >,//
				class Compare = std::less<T>,			
				class Allocator = std::allocator<T> >	//// RbTree::allocator_type
	class RbTree
	{
	public:
		typedef Allocator										allocator_type;
		// typedef std::allocator <Node>						node_allocator;
		typedef Node < T > 										Node_t;
		typedef typename Allocator::template
		rebind < Node_t >::other								node_allocator;
		// typedef typename base_allocator::pointer				base_pointer;
		typedef typename node_allocator::pointer				node_pointer;
		// rebind<Node<T> >::other								node_allocator;

		typedef Compare											key_compare;

		node_pointer											root_p;
		node_pointer											nill_node;
		key_compare												_compare;
		node_allocator											_node_allocator;
		size_t													_size;


		typedef Rb_iterator	< T >								iterator;
		typedef Rb_iterator < const T >							const_iterator;
		typedef Rb_ReverseIterator< T >							reverse_iterator;
		typedef Rb_ReverseIterator< const T >					const_reverse_iterator;
		typedef typename std::size_t							size_type;
		typedef typename std::ptrdiff_t							difference_type;

		//copy constructor
		RbTree (const RbTree & rhs): _compare(rhs._compare), _size(0)
		{
			// std::cout << "copy const" << std::endl;
			nill_node = create_nil_node();
			root_p = nill_node;
			root_p->parent = nill_node;
			if (this != &rhs)
				*this = rhs;
		}

		// default constructor
		RbTree(const key_compare& comp= key_compare() , const allocator_type& alloc = allocator_type()): _compare(comp), _node_allocator(alloc), _size(0)//{}//_node_allocator 
		{
			nill_node = create_nil_node();
			root_p = nill_node;
			root_p->parent = nill_node;
			// std::cout << "__Hello red black tree"<< std::endl;
		}

		//destructor
		~RbTree()
		{
			clear();
			free_node(nill_node);
			// std::cout << "__Good buy red black tree"<< std::endl;
		};

		RbTree& operator=( const RbTree & rhs )//<typename ft::remove_const< T >::type>
		{
			if (this == &rhs)
				return *this;
			// if(nill_node && size)
			clear();
			root_p = nill_node;
			root_p->parent = nill_node;
			const_iterator ib = rhs.begin();
			const_iterator ie = rhs.end();
			while(ib!= ie)
			{
				insert(*ib);
				ib++;
			}
			return *this;
		}

	private:

		void inorder_tree_walk(node_pointer p) const
		{
			if(p && p!= nill_node)/// 
			{
				inorder_tree_walk(p->left);
				if(p->red == RED_N){
					std::cout << BRED;
					std::cout << "kv: " << p->_kv << " ";
					std::cout << SHALLOW;
				}
				else
				{
					std::cout << BGBLUE;
					std::cout << "kv: " << p->_kv << " ";
					std::cout << SHALLOW;
				}
				inorder_tree_walk(p->right);
			}
		}

		void rb_insert_node(node_pointer z)
		{
			std::cout << GREEN;
			node_pointer x, y;
			x = root_p; //node being compared with z
			y = nill_node;// y will be parent of z
			while(x!= nill_node)//descend until reaching the sentinel;
			{
				y = x;
				if(_compare(z->_kv, x->_kv))// if(z->_kv < x->_kv)
				{
					x = x->left;
					// std::cout << "fist" << std::endl;
				}
				else {
					// std::cout << "second" << std::endl;
					x = x->right;
				}
			}
			z->parent = y;
			//found the location - insert z with parent y
			if(y == nill_node){

				root_p = z;
			}
			else if (_compare(z->_kv , y->_kv))//else if (z->_kv < y->_kv)
			{
				y->left = z;
			}
			else {
				y->right = z;
			}
			z->left = nill_node;
			z->right = nill_node;
			z->red = RED_N;//RED
			std::cout << SHALLOW;
			_size++;
		} 

		void rb_insert_fixup(node_pointer z)
		{
			while(z->parent->red == RED_N)//z->parent is RED
			{
				if(z->parent == z->parent->parent->left)//z's parent a left child
				{
					node_pointer y;
					y = z->parent->parent->right;
					if(y->red == RED_N)//red
					{
						z->parent->red = BLACK_N;// black
						y->red = BLACK_N; //black
						z->parent->parent->red = RED_N;// red
						z = z->parent->parent;
					}
					else
					{
						if(z == z->parent->right)
						{
							z = z->parent;
							left_rotate(z);
						}
						z->parent->red = BLACK_N; // black
						z->parent->parent->red = RED_N; // red
						right_rotate(z->parent->parent);
					}
				}
				else
				{
					node_pointer y;
					y = z->parent->parent->left;
					if(y->red == RED_N)//red
					{
						z->parent->red = BLACK_N;// black
						y->red = BLACK_N; //black
						z->parent->parent->red = RED_N;// red
						z = z->parent->parent;
					}
					else
					{
						if(z == z->parent->left)
						{
							z = z->parent;
							right_rotate(z);
						}
						z->parent->red = BLACK_N; // black
						z->parent->parent->red = RED_N; // red
						left_rotate(z->parent->parent);
					}
				}
			}
			root_p->red = BLACK_N;//BLACK
		}

		void left_rotate(node_pointer x)
		{
			node_pointer y;
			y = x->right; // turn y's left subtree into x's right subtree
			x->right = y->left; 
			if(y->left != nill_node)// if y's left subtree is not empty... or not sentinel//
			{
				y->left->parent = x;
			}
			y->parent = x->parent;
			if(x->parent == nill_node)
			{
				root_p = y;
			}
			else if(x == x->parent->left){

				x->parent->left = y;
			}
			else{
				x->parent->right = y;
			}
			y->left = x;
			x->parent = y;
		}

		void right_rotate(node_pointer y)
		{
			node_pointer x;
			x = y->left; // turn x's left subtree into y's right subtree
			y->left = x->right; 
			if(x->right != nill_node)// if x's left subtree is not emptx... or not sentinel//
			{
				x->right->parent = y;
			}
			x->parent = y->parent;
			if(y->parent == nill_node)
			{
				root_p = x;
			}
			else if(y == y->parent->right){

				y->parent->right = x;
			}
			else
			{
				y->parent->left = x;
			}
			x->right = y;
			y->parent = x;
		}

		node_pointer create_node(T const &z)
		{
			// std::cout << "I am going to create a node with " << z << std::endl;
			node_pointer new_node_p = 0;
			Node_t new_node(nill_node, nill_node, root_p, z, RED_N);
			try
			{
				new_node_p = _node_allocator.allocate(1);
			}
			catch(std::bad_alloc)
			{
				std::cout << "Oh, but I can not allocate memory....." << std::endl;
			}
			_node_allocator.construct(new_node_p, new_node);
			return new_node_p;
		}

		void free_node(Node_t *z)
		{
			_node_allocator.destroy(z);
			_node_allocator.deallocate(z, 1);
		}

		node_pointer create_nil_node()
		{
			node_pointer new_node_p = 0;
			Node_t new_node(NULL, NULL, NULL, T(), BLACK_N);
			new_node_p = _node_allocator.allocate(1);
			_node_allocator.construct(new_node_p, new_node);
			return new_node_p;
		}

		void rb_delete(Node_t * z)
		{
			if (z == nill_node){
				return;
			}
			Node < T > * temp = z;
			node_pointer y = z;
			bool y_original_red = y->red;
			node_pointer x = nill_node;
			if (z->left == nill_node)//the node has just one right son
			{
				x = z->right;
				rb_transplant(z, z->right);//replace z by its right child
			}
			else if(z->right == nill_node)//the node has just one left son
			{
				x = z->left;
				rb_transplant(z,z->left);//replace z by its left child
			}
			else// the node has two sons
			{	
				y = rb_minimum(z->right);
				y_original_red = y->red;
				x = y->right;
				if (y->parent == z )
					x->parent = y;
				else
				{
					rb_transplant(y, y->right);
					y->right =z->right;
					y->right->parent =y;
				}
				rb_transplant(z, y);
				y->left =z->left;
				y->left->parent = y;
				y->red =z->red;
			}
			if (y_original_red == BLACK_N)
			{
				rb_delete_fixup(x);
			}
			if (temp)
				free_node(temp);
			--_size;
			// std::cout << "rb_delete I have deleted the node" << std::endl;
		}

		void rb_delete_fixup(Node_t * x)
		{
			node_pointer w = nill_node;
			while (x != root_p  && x->red == BLACK_N)
			{
				if (x == x->parent->left)
				{
					w = x->parent->right;
					if (w->red == RED_N)
					{
						w->red = BLACK_N;
						x->parent->red = RED_N;
						left_rotate(x->parent);
						w = x->parent->right;
					}
					if (w->left->red == BLACK_N && w->right->red == BLACK_N)
					{
						w->red = RED_N;
						x = x->parent;
					}
					else 
					{
						if (w->right->red == BLACK_N)
						{
							w->left->red = BLACK_N;
							w->red = RED_N;
							right_rotate(w);
							w = x->parent->right;
						}
					w->red = x->parent->red;
					x->parent->red = BLACK_N;
					w->right->red = BLACK_N;
					left_rotate(x->parent);
					x = root_p;
					}
				}
				else
				{
					w = x->parent->left;
					if (w->red == RED_N){
						w->red = BLACK_N;
						x->parent->red = RED_N;
						right_rotate(x->parent);
						w = x->parent->left;
					}
					if (w->right->red == BLACK_N && w->left->red == BLACK_N)
					{
						w->red = RED_N;
						x = x->parent;
					}
					else
					{
						if (w->left->red == BLACK_N)
						{
							w->right->red = BLACK_N;
							w->red = RED_N;
							left_rotate(w);
							w = x->parent->left;
						}
						w->red = x->parent->red;
						x->parent->red = BLACK_N;
						w->left->red = BLACK_N;
						right_rotate(x->parent);
						x = root_p;
					}
				}
			}
			x->red = BLACK_N;
			std::cout << SHALLOW;
		}

	public:

		void clear()
		{
			node_pointer z;
			z = root_p;
			while(z != nill_node)/// 
			{
				rb_delete(root_p);
				z = root_p;
			}
		}

		//_______________________________________________________
		// Node_t* search(Node_t * root,T key) const// everything is fine!
		// {
		// 	std::cout << "____oh I'm here.. at least" << std::endl;
		// 	if(!root)
		// 		return NULL;
		// 	//to do& try and catch
		// 	if (key == root->_kv){
		// 		std::cout << "____oh I'm here.. at least" << std::endl;
		// 		return root;
		// 	}
		// 	if(_compare(key ,root->_kv))//if(key < root->_kv)
		// 		return search(root->left, key);
		// 	if(key >= root->_kv)
		// 		return search(root->right, key);
		// 	return NULL;
		// }


		Node_t* iterative_search( const T val) const// everything is fine!
		{
			node_pointer root = root_p;
			while(root!= nill_node && (_compare(root->_kv, val) || _compare(val, root->_kv)))// val.first != root->_kv.first)
			{
				if(_compare(val , root->_kv))//if(key < root->_kv)
					root = root->left;
				else 
					root = root->right;
			}
			if(root == nill_node)
				return nill_node;
			return root;
		}


		// // typename EnableIf<!IsSame<T, ft::pair < const L, Key >::value, void>::type
		// Node_t* iterative_search( const T key) const// everything is fine!
		// {
		// 	node_pointer root = root_p;
		// 	while(root!= nill_node && key != root->_kv)
		// 	{
		// 		if(_compare(key , root->_kv))//if(key < root->_kv)
		// 			root = root->left;
		// 		else 
		// 			root = root->right;
		// 	}
		// 	if(root == nill_node)
		// 		return nill_node;
		// 	return root;
		// }

		iterator lower_bound(const T key)
		{
			// bool left = false;
			// node_pointer x = root_p;
			// node_pointer y = root_p;
			// while (x != nill_node && key.first != x->_kv.first) // ??
			// {
			// 	y = x;
			// 	if (_compare(key, x->_kv))
			// 	{
			// 		left = true;
			// 		x = x->left;
			// 	}
			// 	else
			// 	{
			// 		left = false;
			// 		x = x->right;
			// 	}
			// }
			// if (!_compare(key, x->_kv) && !_compare(x->_kv, key) && x != nill_node)
			// 	return(iterator(x, root_p, nill_node));
			// else
			// {
			// 	if (left == true)
			// 		return(iterator(y, root_p, nill_node));
			// 	return(iterator(successor(y), root_p, nill_node));
			// }
			iterator last = end();
			for (iterator first = begin(); first != last; ++first){
				if(!_compare(*first, key))
					return (first);
			}
			return (last);
		}

		const_iterator lower_bound(const T key) const
		{
			// bool left = false;
			// node_pointer x = root_p;
			// node_pointer y = root_p;
			// while (x != nill_node && key != x->_kv.first) // ??
			// {
			// 	y = x;
			// 	if (_compare(key, x->_kv))
			// 	{
			// 		left = true;
			// 		x = x->left_;
			// 	}
			// 	else
			// 	{
			// 		left = false;
			// 		x = x->right_;
			// 	}
			// }
			// if (!_compare(key, x->_kv) && !_compare(x->_kv, key) && x != nill_node)
			// 	return(const_iterator(x, root_p, nill_node));
			// else
			// {
			// 	if (left == true)
			// 		return(const_iterator(y, root_p, nill_node));
			// 	return(const_iterator(successor(y), root_p, nill_node));
			// }
			const_iterator last = end();
			for (const_iterator first = begin(); first != last; ++first){
				if(!_compare(*first, key))
					return (first);
			}
			return (last);
		}

		iterator upper_bound(const T key)
		{
			iterator last = end();
			for (iterator first = begin(); first != last; ++first){
				if(_compare( key, *first))
					return (first);
			}
			return (last);
			// bool left = false;
			// node_pointer x = root_p;
			// node_pointer y = root_p;
			// while (x != nill_node && key.first != x->_kv.first) // ?
			// {
			// 	y = x;
			// 	// if (k < x->_kv.first)
			// 	if (_compare(key, x->_kv))
			// 	{
			// 		left = true;
			// 		x = x->left;
			// 	}
			// 	else
			// 	{
			// 		left = false;
			// 		x = x->right;
			// 	}
			// }
			// if (!_compare(key, x->_kv) && !_compare(x->_kv, key) && x != nill_node)
			// 	return(iterator(successor(x), nill_node, root_p));
			// else
			// {
			// 	if (left == true)
			// 		return(iterator(y, nill_node , root_p));
			// 	return(iterator(successor(y), nill_node, root_p));
			// }
			
		}

		const_iterator upper_bound(const T key) const
		{
			// 			bool left = false;
			// node_pointer x = root_p;
			// node_pointer y = root_p;
			// while (x != nill_node && key.first != x->_kv.first) // ?
			// {
			// 	y = x;
			// 	// if (k < x->_kv.first)
			// 	if (_compare(key, x->_kv))
			// 	{
			// 		left = true;
			// 		x = x->left;
			// 	}
			// 	else
			// 	{
			// 		left = false;
			// 		x = x->right;
			// 	}
			// }
			// if (!_compare(key, x->_kv) && !_compare(x->_kv, key) && x != nill_node)
			// 	return(const_iterator(successor(x), nill_node, root_p));
			// else
			// {
			// 	std::cout << "hoho2" << std::endl;
			// 	if (left == true)
			// 		return(const_iterator(y, nill_node , root_p));
			// 	return(const_iterator(successor(y), nill_node, root_p));
			// }
			const_iterator last = end();
			for (const_iterator first = begin(); first != last; ++first){
				if(_compare( key, *first))
					return (first);
			}
			return (last);
		}

		//Returns an iterator pointing to the first element that is not less than
		//(i.e. greater or equal to) key. <= KEY

		// Node_t* iterative_search( const L key) const// everything is fine!
		// {
		// 	// if(!root)
		// 	// 	return NULL;
		// 	node_pointer root = root_p;
		// 	//to do& try and catch
		// 	while(root!= nill_node && key = root->_kv.first)
		// 	{
		// 		if(_compare(key , root->_kv.first))//if(key < root->_kv)
		// 			root = root->left;
		// 		else 
		// 			root = root->right;
		// 	}
		// 	if(root == nill_node)
		// 		return nill_node;
		// 	// if(root == nill_node)
		// 	//  	return nill_node;
		// 	return root;
		// }

		// template <class T = ft::pair<class L, class B>
		// Node* iterative_search( T key) const// everything is fine!
		// {
		// 	// if(!root)
		// 	// 	return NULL;
		// 	node_pointer root = root_p;
		// 	//to do& try and catch
		// 	while(root!= nill_node && key.first != root->_kv.first)
		// 	{
		// 		if(_compare(key , root->_kv))//if(key < root->_kv)
		// 			root = root->left;
		// 		else 
		// 			root = root->right;
		// 	}
		// 	if(root == nill_node)
		// 		return NULL;
		// 	// if(root == nill_node)
		// 	//  	return nill_node;
		// 	return root;
		// }

		//_______________________________________________________
		Node_t* rb_minimum(Node_t * root) const// everything is fine!
		{
			// std::cout << "I am in minimum now" << std::endl;
			// if(root == nill_node)
			// 	return root;
			while (root->left!= nill_node && root->left!=NULL)//root->left && 
				root = root->left;
			// std::cout << "The end of minimum now" << std::endl;
			return root;
		}
		//_______________________________________________________
		Node_t* rb_maximum(Node_t * root) const// everything is fine!
		{
			// std::cout << "I am in maximum now" << std::endl;
			// if(root == nill_node)
			// 	return root;
			while (root->right && root->right!= nill_node )
				root = root->right;
			// std::cout << "The end of maximum now" << std::endl;
			return root;
		}
		//_______________________________________________________
		void rb_transplant(Node_t * u, Node_t * v) // everything is fine!
		{
			// std::cout << "I am rb_transplant now" << std::endl;
			if(u->parent == nill_node){
				root_p = v;
			}
			else if (u == u->parent->left)
				u->parent->left = v;
			else{
				u->parent->right = v;
			}
				v->parent = u->parent;
			// std::cout << "the end of rb_transplant" << std::endl;
		}

	// _______________________________________________________!

		Node_t* successor(Node_t * x)// everything is fine!
		{
			if(x->right != nill_node)//leftmost node in right subtree
				return rb_minimum(x->right);
			Node_t * y;
			y = x->parent;
			while(y != nill_node && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

	//_______________________________________________________!

		Node_t* predecessor(Node_t * x)// everything is fine!
		{
			if(x->left != nill_node)//leftmost node in right subtree
				return rb_maximum(x->left);
			else{
				Node_t * y;
				y = x->parent;
				while(y != nill_node && x == y->left)
				{
					x = y;
					y = y->parent;
				}
				return y;
			}
		}

		ft::pair<iterator, bool> insert_2 (T const &z)
		{ 
			bool exist = 0;
			node_pointer new_node_p = iterative_search(z);
			if (new_node_p == nill_node)
			{	
				exist = 1;
				new_node_p = create_node(z);
				rb_insert_node(new_node_p);
				rb_insert_fixup(new_node_p);
			}
			else{
				// std::cout << "the tree already has the node with this value "  << std::endl;
			}
			iterator where(new_node_p, nill_node, root_p);
			return (ft::make_pair <iterator, bool> (where, exist) );
		}

		iterator insert(T const &z)// everything is fine!
		{
			node_pointer new_node_p = iterative_search(z);
			if (new_node_p == nill_node)
			{
				node_pointer new_node_p = create_node(z);
				rb_insert_node(new_node_p);
				rb_insert_fixup(new_node_p);
			}
			else{
				// std::cout << "the node is already exists "  << std::endl;
			}
			return iterator(new_node_p, nill_node, root_p);
		}

		size_t size() const
		{
			return _size;
		}

		//Removes the node at pos
		void erase (iterator position)
		{
			rb_delete(position);
		};

		void delete_node_by_value(T const &z)
		{
			node_pointer new_node_p = iterative_search( z);
			if (new_node_p == nill_node)
			{
				std::cout <<  RED << "oh, but there's no node with that key"<< SHALLOW << std::endl;
				return;
			}
			if (new_node_p)
			{
				// std::cout <<  RED << "the node with that key exists"<< SHALLOW << std::endl;
				rb_delete(new_node_p);
			}
		}

		void delete_node_by_address(Node_t * node)
		{
			rb_delete(node);
		}

		void print()
		{
			std::cout << std::endl;
			std::cout <<  "__printing..............." << std::endl;
			if(root_p == nill_node)
			{
				std::cout << "the tree is empty"<< std::endl;
				// inorder_tree_walk(root_p->left);
			}
			if(root_p != nill_node){
				std::cout << "the tree is not empty"<< std::endl;
				std::cout <<  BGBLUE << "the key of root: "<< root_p->_kv << SHALLOW << std::endl;
				std::cout << "__________________________________________________________________"<< std::endl;
				inorder_tree_walk(root_p);
				std::cout << std::endl;
				std::cout << "__________________________________________________________________"<< std::endl;
			}
			std::cout  << std::endl;
		}

		key_compare value_compare() const
		{
			return _compare;
		};

		// swaps the contents
		void swap (RbTree &x)
		{
			std::swap(root_p, x.root_p);
			std::swap(nill_node, x.nill_node);
			std::swap(_compare, x._compare);
			std::swap(_node_allocator, x._node_allocator);
			std::swap(_size, x._size);
		};
	//______ITERATORS:__________________________________________________________________________
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		iterator begin()
		{
			return iterator(rb_minimum(root_p), nill_node, root_p);
		}

		const_iterator begin() const
		{
			return const_iterator(rb_minimum(root_p), nill_node, root_p);
		}

		iterator end()
		{
			return iterator(nill_node, nill_node, root_p);
		}
		
		const_iterator end() const
		{
			return const_iterator(nill_node, nill_node, root_p);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(rb_maximum(root_p), nill_node, root_p);
		};

		const_reverse_iterator rbegin() const{
			return const_reverse_iterator(rb_maximum(root_p), nill_node, root_p);
		};

		reverse_iterator rend()
		{
			return reverse_iterator(nill_node, nill_node, root_p);
		};

		const_reverse_iterator rend() const{
			return reverse_iterator(nill_node, nill_node, root_p);
		};

		// template < class U >
		friend bool operator== ( const RbTree<T, Compare , Allocator >& lhs, const RbTree<T, Compare , Allocator >& rhs )
		{
			return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));//(false);
		};

		friend bool operator!= ( const RbTree<T, Compare , Allocator >& lhs, const RbTree<T, Compare , Allocator >& rhs )
		{
			return !(lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));//(false);
		};

		friend bool operator<(const RbTree<T, Compare , Allocator >& lhs, const RbTree<T, Compare , Allocator >& rhs )
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

		friend bool operator>(const RbTree<T, Compare , Allocator >& lhs, const RbTree<T, Compare , Allocator >& rhs )
		{
			return (ft::lexicographical_compare( rhs.begin(), rhs.end(),lhs.begin(), lhs.end()));
		}
	};

}
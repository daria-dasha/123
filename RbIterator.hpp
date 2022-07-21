
#pragma once
#include "RbNode.hpp"
#include "IteratorsTraits.hpp"
#include "RemoveConst.hpp"

namespace ft{
		
		template < class T >
		
		class Rb_iterator
		{
		public:
			typedef Node < T >	*													iterator_type;

			typedef typename ft::iterator_traits< Node < T > *  >::value_type		value_type;
			typedef std::bidirectional_iterator_tag									iterator_category;
			typedef typename iterator_traits< Node < T > *  >::difference_type		difference_type;
			typedef typename iterator_traits< Node <typename ft::remove_const< T >::type> *  >::pointer				pointer;
			typedef typename iterator_traits< Node < T > *  >::reference			reference;
			typedef Node < T >	*					node_pointer;

			pointer																	_current_node;
			pointer																	_nill_node;
			pointer																	_root_p;
			//default

			Rb_iterator(): _current_node(0), _nill_node(0), _root_p(0)//
			{
				// std::cout << RED << "hello i am default constructor of iterator!" <<  SHALLOW << std::endl;
			};

			//pointer constructor
			Rb_iterator(pointer c, pointer n, pointer r) :  _current_node(c), _nill_node(n), _root_p(r) //
			{
				// std::cout << RED << "hello i am pointer constructor of iterator!" <<  SHALLOW << std::endl;
			};

			// template<class U>
			Rb_iterator & operator=(const Rb_iterator  &other)//<U><typename ft::remove_const< T >::type>
			{
					// std::cout << RED <<  "hello i am assign = from iterator!" <<  SHALLOW << std::endl;
				if (this == &other)
					return *this;
				else
				{
					_current_node = other._current_node;
					_nill_node = other._nill_node;
					_root_p = other._root_p;
				}
				return *this;
			}

			// copy
			// template<class U>
			// Rb_iterator(Rb_iterator <U> const &rhs) : _current_node(rhs._current_node), _nill_node(rhs._nill_node), _root_p(rhs._root_p)
			// {
			// 	// std::cout << RED <<  "hello i am copy constructor of iterator!!!!!!" <<  SHALLOW << std::endl;
			// 	// if (this != &rhs)
			// 	// 	*this = rhs;
			// }
			//
			Rb_iterator(const Rb_iterator <typename ft::remove_const< T >::type> &rhs): _current_node(rhs._current_node), _nill_node(rhs._nill_node), _root_p(rhs._root_p)// <typename ft::remove_const< T >::type>
			{
				// std::cout << RED <<  "hello i am copy constructor of iterator!!!!!!" <<  SHALLOW << std::endl;
				// if (this != &rhs)
				// 	*this = rhs;
			}

			// pointer base() { return _current_node; }
			// pointer nill_node() { return _nill_node; }
			// pointer root_p() { return _root_p; }


			//desctuctor
			virtual ~Rb_iterator()
			{
				//std::cout << RED << "goodbuy iterator!" <<  SHALLOW << std::endl;
			};

			Rb_iterator current_node(){
				return(_current_node);
			}
			
			pointer node()
			{ 
				return(_current_node);
			}

			T operator*() const
			{
				//std::cout << "i am in operator * in iterators" << std::endl;
				return (_current_node->_kv);
			}

			T* operator->() const
			{
				if(!_current_node)
				{
					std::cout << "here" << std::endl;
					// throw std::out_of_range("Map");
					return NULL;
				}
				T * m = &_current_node->_kv;
				// std::cout << "i am in operator -> in iterators" << std::endl;
				return (m);
			}

		private:
			//_______________________________________________________
			pointer successor(pointer x)// everything is fine!
			{
				// std::cout << "successor"<< std::endl;
				//to do& try and catch
				if(x == _nill_node)
					return NULL;
				if(x->right != _nill_node)//leftmost node in right subtree
					return rb_minimum(x->right);
				pointer y = _nill_node;
				y = x->parent;
				while(y != _nill_node && x == y->right)
				{
					x = y;
					y = y->parent;
				}
				return y;
			}

			//_______________________________________________________
			pointer predecessor(pointer x)// everything is fine!
			{
				// std::cout << "predecessor"<< std::endl;
				//to do& try and catch
				if(x == _nill_node)
					return NULL;
				if(x->left != _nill_node)//leftmost node in right subtree
					return rb_maximum(x->left);
				else{
					pointer y = _nill_node;
					y = x->parent;
					while(y != _nill_node && x == y->left)
					{
						x = y;
						y = y->parent;
					}
					return y;
				}
			}

			//_______________________________________________________!
			pointer rb_minimum(pointer root)// everything is fine!
			{
				while (root->left!= _nill_node)//root->left && 
					root = root->left;
				return root;
			}

			//_______________________________________________________!
			pointer rb_maximum(pointer root)// everything is fine!
			{
				if(!root)
					return NULL;
				while (root->right && root->right!= _nill_node )
					root = root->right;
				return root;
			}

		public:
			//OPERATORS
			Rb_iterator &operator++() {
				_current_node = successor(_current_node);
				return *this;
			}

			Rb_iterator operator++(int) {
				Rb_iterator tmp(*this);
				_current_node = successor(_current_node);
				return tmp;
			}

			Rb_iterator &operator--() {
				if(_current_node == _nill_node || _current_node == NULL)
				{
					_current_node = rb_maximum(_root_p);
				}
				else
					_current_node = predecessor(_current_node);
				return *this;
			}

			Rb_iterator operator--(int) {
				Rb_iterator tmp(*this);
				if(_current_node == _nill_node || _current_node == NULL)
				{
					_current_node = rb_maximum(_root_p);
				}
				else
					_current_node = predecessor(_current_node);
				return tmp;
			}

			bool operator == (const Rb_iterator  & rhs)//<typename ft::remove_const< T >::type>
			{
					return(_current_node == rhs._current_node);
			}
			
			bool operator != (const Rb_iterator  & rhs)//<typename ft::remove_const< T >::type>
			{
					return(_current_node != rhs._current_node);
			}
		};

		template <class A, class B>
		bool operator != (const Rb_iterator<A> & lhs, const Rb_iterator<B> & rhs)
		{

			return(lhs._current_node != rhs._current_node);
		}

		template <class A, class B>
		bool operator == (const Rb_iterator<A> & lhs, const Rb_iterator<B> & rhs)
		{

			return(lhs._current_node == rhs._current_node);
		}

		template <class A>
		bool operator != (const Rb_iterator<A> & lhs, const Rb_iterator<A> & rhs)
		{

			return(lhs._current_node != rhs._current_node);
		}

		template <class A>
		bool operator == (const Rb_iterator<A> & lhs, const Rb_iterator<A> & rhs)
		{

			return(lhs._current_node == rhs._current_node);
		}

}

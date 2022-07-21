
#pragma once

namespace ft{

	template < class T >
	class Rb_ReverseIterator
	{
	public:
		typedef Node < T > *													iterator_type;

		typedef std::bidirectional_iterator_tag									iterator_category;
		typedef typename ft::iterator_traits< Node < T > *>::difference_type	difference_type;
		typedef typename ft::iterator_traits< Node < T > *>::pointer			pointer;
		typedef typename ft::iterator_traits< Node < T > *>::reference			reference;


		pointer _current_node;
		pointer _nill_node;
		pointer _root_p;

		//default
		Rb_ReverseIterator() : _current_node(0), _nill_node(0), _root_p(0)//
		{
			//std::cout << RED << "hello i am default constructor of iterator!" <<  SHALLOW << std::endl;
		};

		//pointer constructor
		explicit Rb_ReverseIterator(pointer c, pointer n, pointer p) :  _current_node(c), _nill_node(n), _root_p(p)
		{
			//std::cout << RED << "hello i am pointer constructor of iterator!" <<  SHALLOW << std::endl;
		};

		Rb_ReverseIterator &
		operator=(Rb_ReverseIterator <typename ft::remove_const< T >::type> const &other)
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

		//desctuctor
		virtual ~Rb_ReverseIterator()
		{
			//std::cout << RED << "goodbuy iterator!" <<  SHALLOW << std::endl;
		};

		//copy
		Rb_ReverseIterator(Rb_ReverseIterator <typename ft::remove_const< T >::type> const &rhs) : _current_node(rhs._current_node)
		{
			// std::cout << RED <<  "hello i am copy constructor of iterator!!!!!!" <<  SHALLOW << std::endl;
			if (this != &rhs)
				*this = rhs;
		}
		pointer node()
		{
			return(_current_node);
		}

		Rb_ReverseIterator current_node(){
			return(_current_node);
		}

		T operator*() const
		{
			//std::cout << "i am in operator * in iterators" << std::endl;
			return (_current_node->_kv);
		}
		T* operator->() const
		{
			
			//std::cout << "i am in operator * in iterators" << std::endl;
			return &(_current_node->_kv);
		}

	private:
		//_______________________________________________________
		pointer successor(pointer x)// everything is fine!
		{
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
		Rb_ReverseIterator &operator--()
		{
			if(_current_node == _nill_node)
			{
				_current_node = rb_minimum(_root_p);
			}
			else 
				_current_node = successor(_current_node);
			return *this;
		}

		Rb_ReverseIterator operator--(int)
		{
			Rb_ReverseIterator tmp(*this);
			if(_current_node == _nill_node)
			{
				_current_node = rb_minimum(_root_p);
			}
			else
				_current_node = successor(_current_node);
			return tmp;
		}

		Rb_ReverseIterator &operator++()
		{
			_current_node = predecessor(_current_node);
			return *this;
		}
	
		Rb_ReverseIterator operator++(int)
		{
			Rb_ReverseIterator tmp(*this);
			_current_node = predecessor(_current_node);
			return tmp;
		}
		
		bool operator == (Rb_ReverseIterator & rhs)
		{
			return(_current_node == rhs._current_node);
		}
		
		bool operator != (Rb_ReverseIterator & rhs)
		{
			return(_current_node != rhs._current_node);
		}
	};

	template <class A>
	bool operator != (const Rb_ReverseIterator<A> & lhs, const Rb_ReverseIterator<A> & rhs)
	{
		return(lhs._current_node != rhs._current_node);
	}

	template <class A>
	bool operator == (const Rb_ReverseIterator<A> & lhs, const Rb_ReverseIterator<A> & rhs)
	{
		return(lhs._current_node == rhs._current_node);
	}
}

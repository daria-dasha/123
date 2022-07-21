

#pragma once

#include <iostream>
#include "pair.hpp"
#include "RedBlackTree.hpp"
#include "Utility.hpp"
#include "RbReverseIterator.hpp"
#include "RbIterator.hpp"

namespace ft
{

	template < class Key,												// map::key_type
				class T,												// map::mapped_type
				class Compare = std::less<Key>,							// map::Compare 
				class Alloc = std::allocator<pair<const Key,T> > >		// map::allocator_type
	class map
	{
	public:
		typedef pair<const Key, T>										value_type;
		class value_compare
		{
		public:
			Compare cmp; 
			// constructed with map's comparison object
			value_compare(Compare c): cmp(c){};

			bool operator()( const value_type& lhs, const value_type& rhs ) const
			{
				// std::cout << RED << "i am in the value_compare" << SHALLOW << std::endl;
				return cmp(lhs.first, rhs.first);
			};
		};

		typedef Key														key_type;
		typedef T														mapped_type;

		typedef	Compare													key_compare;
		typedef Alloc													allocator_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef RbTree<value_type, value_compare, allocator_type>		red_black_tree;

		typedef typename red_black_tree::iterator						iterator;
		typedef typename red_black_tree::const_iterator					const_iterator;
		typedef typename red_black_tree::reverse_iterator				reverse_iterator;
		typedef typename red_black_tree::const_reverse_iterator			const_reverse_iterator;
		typedef typename std::ptrdiff_t									difference_type;
		typedef typename std::size_t									size_type;
		typedef Node < T >												Node_t;

	private:
		red_black_tree													_mytree;
		allocator_type													_myallocator;
		key_compare														_mycomp;

	public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//______MEMBER FUNCIONS_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//(1) empty container constructor (default constructor)
		//Constructs an empty container, with no elements.
		explicit map (const key_compare& comp = key_compare(), 
		const allocator_type& alloc = allocator_type()):_mytree(value_compare(comp)), _myallocator(alloc), _mycomp(comp)
		{
			std::cout << GREEN;
			// std::cout << "hello map!" << std::endl;
			std:: cout << SHALLOW;
		};

		//	(2) range constructor
		//	Constructs a container with as many elements as the range (first,last),
		//	with each element constructed from its corresponding element in that range.
				template <class InputIterator>
		map (InputIterator first, InputIterator last,//OK!!!
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()): _mytree(value_compare(comp)), _myallocator(alloc), _mycomp(comp)
		{
			while(first != last)
			{
				insert(*first);
				++first;
			}
		};

		//(3) copy constructor
		//Constructs a container with a copy of each of the elements in x.
		map (const map& x): _mytree(x._mytree), _myallocator(x._myallocator), _mycomp(x._mycomp)//OK!!!
		{
			if (this != &x)
				*this = x;
		};

		//destructor
		~map()
		{

		};

		//For checking
		//=============
		// void rb_print(){
		// 	_mytree.print();
		// }

		map& operator=( const map& other )
		{
			if (this == &other)
				return *this;
			else{
				clear();
				_mytree = other._mytree;
				_myallocator = other._myallocator;
				_mycomp = other._mycomp;
			}

			return *this;
		}

		//Returns a copy of the allocator object associated with the map.
		allocator_type get_allocator() const//OK!!!
		{
			return(_myallocator);
		};

//______Element access______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//access or insert specified element
		mapped_type& operator[] (const key_type& k)//OK!!!
		{
			return insert(ft::make_pair(k, T())).first->second;
		};

		//access specified element with bounds checking
		//Returns a reference to the mapped value of the element
		//with key equivalent to key. If no such element exists,
		//an exception of type std::out_of_range is thrown.
		T& at( const Key& key )
		{
			iterator position = find(key);
			iterator nill_i(_mytree.nill_node, _mytree.nill_node, _mytree.root_p);
			if (position.node()== _mytree.nill_node)
				throw std::out_of_range("Map");// is it right?
			return((position.node())->_kv.second);
		};
		//access specified element with bounds checking
		const T& at( const Key& key ) const
		{
			iterator position = find(key);
			iterator nill_i(_mytree.nill_node, _mytree.nill_node, _mytree.root_p);
			if (position.node()== _mytree.nill_node)
				throw std::out_of_range("Map");// is it right?
			return((position.node())->_kv.second);
		};
//______Iterators___________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		iterator begin()//OK!!!
		{
			return iterator(_mytree.begin());
		};

		const_iterator begin() const
		{
			return const_iterator(_mytree.begin() );
		};

		iterator end()//OK!!!
		{
			return iterator(_mytree.end());
		};

		const_iterator end() const
		{
			return const_iterator(_mytree.end());
		};

		reverse_iterator rbegin()//OK!!!
		{
			return reverse_iterator (_mytree.rbegin());
		};

		const_reverse_iterator rbegin() const
		{
				return const_reverse_iterator (_mytree.rbegin());	
		};

		reverse_iterator rend()//OK!!!
		{
			return reverse_iterator (_mytree.rend());
		};

		const_reverse_iterator rend() const
		{
				return const_reverse_iterator (_mytree.rend());
		};

//______Capacity____________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Test whether container is empty
		bool empty() const//OK!!!
		{
			return!(_mytree._size);
		};

		//Returns the number of elements in the map container.
		size_type size() const//OK!!!
		{
			return(_mytree._size);
		};

		size_type max_size() const//OK!!!
		{
			return (_myallocator.max_size());
		};

//______Modifiers___________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//Removes all elements from the map container
		// (which are destroyed), leaving the container
		// with a size of 0.
		void clear()//OK!!!
		{	
			_mytree.clear();
			// may be i should change this, try and catch, so it will show how many
			// elements was deleted really.
		};

		//=============
		// single element (1)
		// Returns a pair consisting of an iterator to the inserted element
		// (or to the element that prevented the insertion)
		// and a bool denoting whether the insertion took place.
		pair<iterator,bool> insert (const value_type& val)
		{
			// std::cout << "i am in the map and inserting the value" << std::endl;
			pair<iterator,bool> ret = _mytree.insert_2(val);

			return(ret);
		};

		// with hint (2)	
		iterator insert (iterator position, const value_type& val)
		{
			(void) position;
			return (_mytree.insert(val));

		};

		// range (3)	
		template <class InputIterator>
		void insert (InputIterator first, typename EnableIf <!is_integral<InputIterator>::value, InputIterator>::type last)
		{
			for(;first!= last; ++first)
			{
				insert(*(first));
			}
		};

		// (1)	Removes the element at pos.
		void erase (iterator position)//OK!!!
		{
			_mytree.delete_node_by_address(position.node());
		};

		// (2) Removes the element (if one exists) with the key equivalent to key.
		size_type erase (const key_type& k)//OK!!!
		{
			iterator position = find(k);
			iterator nill_i(_mytree.nill_node, _mytree.nill_node, _mytree.root_p);
			if (position != nill_i)
			{
				erase(position);
				return (1);
			}
			return 0;
		};

		// (3)	Removes the elements in the range [first; last), which must be a valid range in *this
		void erase (iterator first, iterator last)//OK!!!
		{
			while(first != last)
			{
				erase(first++);
			}
		};

		// swaps the contents
		void swap (map& x)
		{
			_mytree.swap(x._mytree);
			std::swap(_myallocator, x._myallocator);
			std::swap(_mycomp, x._mycomp);
		};

//______Look_up_____________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// returns the number of elements matching specific key
		size_type count (const key_type& k) const//OK!!!
		{
			pair<Key,T> new_pair = make_pair< Key, T>(k, T());
			if(_mytree.iterative_search(new_pair) != _mytree.nill_node)
				return 1;
			return 0; 
		};

		// finds element with specific key
		iterator find (const key_type& k)//OK!!!
		{
			pair<Key,T> new_pair = ft::make_pair< Key, T>(k, T());
			return(iterator((_mytree.iterative_search(new_pair)), _mytree.nill_node, _mytree.root_p));
		};

		// finds element with specific key
		const_iterator find (const key_type& k) const//OK!!!
		{
			pair<Key,T> new_pair = make_pair< Key, T>(k, T());
			return(const_iterator((_mytree.iterative_search(new_pair)), _mytree.nill_node, _mytree.root_p));

		};

		// returns range of elements matching a specific key
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const//OK!!!
		{
			pair<Key,T> new_pair = make_pair< Key, T>(k, T());
				return (ft::make_pair(_mytree.lower_bound(new_pair), _mytree.upper_bound(new_pair)));
		};

		// returns range of elements matching a specific key
		pair<iterator,iterator> equal_range (const key_type& k)//OK!!!
		{
			pair<Key,T> new_pair = make_pair< Key, T>(k, T());
				return (ft::make_pair(_mytree.lower_bound(new_pair), _mytree.upper_bound(new_pair)));
		};
		
		// returns an iterator to the first element not less than the given key
		iterator lower_bound (const key_type& k)//OK!!!
		{
			pair<Key,T> new_pair = make_pair< Key, T>(k, T());
				return (_mytree.lower_bound(new_pair));
		};

		// returns an iterator to the first element not less than the given key
		const_iterator lower_bound (const key_type& k) const//OK!!!
		{
				pair<Key,T> new_pair = make_pair< Key, T>(k, T());
				return const_iterator(_mytree.lower_bound(new_pair));
		};

		// returns an iterator to the first element greater than the given key
		iterator upper_bound (const key_type& k)//OK!!!
		{	
			pair<Key,T> new_pair = make_pair< Key, T>(k, T());
			return (_mytree.upper_bound(new_pair));
		};

		// returns an iterator to the first element greater than the given key
		const_iterator upper_bound (const key_type& k) const//OK!!!
		{
			pair<Key,T> new_pair = make_pair< Key, T>(k, T());
			return const_iterator(_mytree.upper_bound(new_pair));
		};

//______Observers___________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// returns the function that compares keys
		key_compare key_comp() const//OK!!!
		{
			return(_mycomp);
		};

		// returns the function that compares keys in objects of type value_type
		value_compare value_comp() const//OK!!!
		{
			return (_mytree.value_compare());
		};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//______NON MEMBER FUNCIONS_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		friend bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
			// return(lhs._mytree == rhs._mytree);
			return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		};

		friend bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
			return!(lhs._mytree == rhs._mytree);
		};

		friend bool operator<(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
		{
			return (lhs._mytree < rhs._mytree);
		};

		friend bool operator>(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
		{
			return (rhs._mytree < lhs._mytree);
		};
		friend bool operator<=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
		{
			return !(lhs > rhs);
		};

		friend bool operator>=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
		{
			return !(lhs < rhs);
		};

	};

	template <class Key, class T, class Compare, class Alloc>
		void swap (map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs)
	{
			lhs.swap(rhs);
	};

}

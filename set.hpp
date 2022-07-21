

#pragma once

#include <iostream>
#include "RedBlackTree.hpp"
#include "Utility.hpp"
#include "RbReverseIterator.hpp"
#include "RbIterator.hpp"

namespace ft
{

	template < class T,									// set::key_type/value_type
				class Compare = std::less<T>,				// set::key_compare/value_compare
				class Alloc = std::allocator<T>	>		// set::allocator_type
	class set
	{
	public:
											
		typedef T														key_type;
		typedef T														value_type;
		typedef	Compare													key_compare;
		typedef	Compare													value_compare;
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
		explicit set (const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()):_mytree(comp), _myallocator(alloc), _mycomp(comp)
		{
			std::cout << GREEN;
			// std::cout << "hello set!" << std::endl;
			std:: cout << SHALLOW;
		};

		//	(2) range constructor
		//	Constructs a container with as many elements as the range (first,last),
		//	with each element constructed from its corresponding element in that range.
		template <class InputIterator>
		set (InputIterator first, InputIterator last,//OK!!!
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()): _mytree(comp), _myallocator(alloc), _mycomp(comp)
		{
			while(first != last)
			{
				insert(*first);
				++first;
			}
		};

		//(3) copy constructor
		//Constructs a container with a copy of each of the elements in x.
		set (const set& x): _mytree(x._mytree), _myallocator(x._myallocator), _mycomp(x._mycomp)//OK!!!
		{
			if (this != &x)
				*this = x;
		};

		//destructor
		~set()
		{

		};

		//For checking
		//=============
		// void rb_print(){
		// 	_mytree.print();
		// }

		set& operator=( const set& other )
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

		//Returns a copy of the allocator object associated with the set.
		allocator_type get_allocator() const//OK!!!
		{
			return(_myallocator);
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

		//Returns the number of elements in the set container.
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

		//Removes all elements from the set container
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
			// std::cout << "i am in the set and inserting the value" << std::endl;
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
		void swap (set& x)
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
			if(_mytree.iterative_search(k) != _mytree.nill_node)
				return 1;
			return 0; 
		};

		// finds element with specific key
		iterator find (const key_type& k)//OK!!!
		{
			return(iterator((_mytree.iterative_search(k)), _mytree.nill_node, _mytree.root_p));
		};

		// finds element with specific key
		const_iterator find (const key_type& k) const//OK!!!
		{
			return(const_iterator((_mytree.iterative_search(k))), _mytree.nill_node, _mytree.root_p);
		};

		// returns range of elements matching a specific key
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const//OK!!!
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		};

		// returns range of elements matching a specific key
		pair<iterator,iterator> equal_range (const key_type& k)//OK!!!
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		};
		
		// returns an iterator to the first element not less than the given key
		iterator lower_bound (const key_type& k)//OK!!!
		{
			return (_mytree.lower_bound(k));
		};

		// returns an iterator to the first element not less than the given key
		const_iterator lower_bound (const key_type& k) const//OK!!!
		{
			return const_iterator(_mytree.lower_bound(k));
		};

		// returns an iterator to the first element greater than the given key
		iterator upper_bound (const key_type& k)//OK!!!
		{	
			return (_mytree.upper_bound(k));
		};

		// returns an iterator to the first element greater than the given key
		const_iterator upper_bound (const key_type& k) const//OK!!!
		{
			return const_iterator(_mytree.upper_bound(k));
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
		friend bool operator== ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs ){
			return(lhs._mytree == rhs._mytree);
		};

		friend bool operator!= ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs ){
			return!(lhs._mytree == rhs._mytree);
		};

		friend bool operator<(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
		{
			return (lhs._mytree < rhs._mytree);
		};

		friend bool operator>(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
		{
			return (rhs._mytree < lhs._mytree);
		};
		friend bool operator<=(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
		{
			return !(lhs > rhs);
		};

		friend bool operator>=(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
		{
			return !(lhs < rhs);
		};

	};

	template <class Key, class T, class Compare, class Alloc>
		void swap (set<T,Compare,Alloc>& lhs, set<T,Compare,Alloc>& rhs)
	{
			lhs.swap(rhs);
	};

}

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <string>
#include <memory>
#include <iterator>
#include <exception>
#include <list>


#include "Colors.hpp"

#include "IteratorsTraits.hpp"
#include "ReverseIterator.hpp"
#include "RandomAccessIterator.hpp"
#include "RemoveConst.hpp"
#include "Utility.hpp"

//сделать второй свап

namespace ft
{
	template < class T , class Allocator = std::allocator<T> >//
	class vector
	{
	public:
		//typedef определяет внутренний тип
		typedef T														value_type;
		typedef Allocator												allocator_type;

		//typename означает, что поинтер это подтип класса аллокатор-тайп
		//без тайпнейм это было бы просто значение
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;

		typedef typename ft::random_access_iterator <value_type>		iterator;
		typedef ft::random_access_iterator <const value_type>			const_iterator;
		typedef typename ft::reverse_iterator <value_type>				reverse_iterator;
		typedef const ft::reverse_iterator < const value_type>			const_reverse_iterator;
		typedef typename std::size_t									size_type;
		typedef typename std::ptrdiff_t									difference_type;

	private:
		allocator_type													_myallocator;
		size_type														_size;
		size_type														_capacity;
		pointer															_p;

	public:
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//______MEMBER FUNCIONS_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//______default(1) 
//		Constructs an empty container, with no elements.
		explicit vector (const allocator_type& alloc = allocator_type()): _myallocator(alloc), _size(0), _capacity(0), _p(NULL)
		{
			//explicit допускает только обычную семантику конструирования и не допусксает неявные преобразования

			//			std::cout << GREEN;
			//			std::cout << "hello default_Vector!" << std::endl;
			//			std:: cout << SHALLOW;
		}

//______fill(2)
//		Constructs a container with n elements. Each element is a copy of val.
		explicit vector (size_type n, const value_type& val = value_type(), 
		const allocator_type& alloc = allocator_type()): _myallocator(alloc),
		_size(n), _capacity(n), _p(NULL)
		{
			try{
				_p = _myallocator.allocate(_capacity);
			}
			catch(std::bad_alloc){
				std::cout << "Oh, but I can not allocate memory....." << std::endl;
			}
			(void) val;
			for (size_type i = 0; i < _size; ++i)
			{
				_myallocator.construct(_p + i, val);
			}

			//	std::cout << GREEN;
			//	std::cout << "hello fill_Vector!" << std::endl;
			//	std:: cout << SHALLOW;
		}

//______range(3)
//		Constructs a container with as many elements as the range (first,last),
//		with each element constructed from its corresponding element in that range,
//		in the same order.
		template <class InputIterator>
		vector (InputIterator first, typename EnableIf <!is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type& alloc = allocator_type()): _myallocator(alloc),
			_size(0), _capacity(0), _p(NULL)
		{
			assign(first, last);
//			std::cout << GREEN;
//			std::cout << "hello fill_Vector!" << std::endl;
//			std:: cout << SHALLOW;
		}

//______copy(3)
//		Constructs a container with a copy of each of the elements in rhs, in the same order
		vector (const vector& rhs): _size(rhs._size), _capacity(rhs._capacity), _p(_myallocator.allocate(_capacity))
		{
			if (this != &rhs)
				*this = rhs;
//			std::cout << GREEN;
//			std::cout << "hello copy_Vector!" << std::endl;
//			std:: cout << SHALLOW;
		}

//______This destroys all container elements, and deallocates all the storage
		//capacity allocated by the vector using its allocator.
		virtual ~vector()
		{
			clear();
			//deallocate memory for p
			if (_p)
				_myallocator.deallocate(_p, _capacity);
//			std::cout << RED;
//			std::cout << "goodbuy Vector!" << std::endl;
//			std::cout << SHALLOW;
		}

//______Assigns new contents to the container,
//		replacing its current contents,
//		and modifying its size accordingly
		vector& operator=( const vector& other )
		{
			if (this == &other)
				return *this;
			clear();
			if (_p)
				_myallocator.deallocate(_p, _capacity);
			_size = other.size();
			_capacity = _size;
			try{
				_p = _myallocator.allocate(_capacity);
			}
			catch(std::bad_alloc){
				std::cout << "Oh, but I can not allocate memory....." << std::endl;
			}
			for(size_type i = 0; i < _size; ++i)
			{
				_myallocator.construct(_p + i, other[i]);
			}
			return *this;
		}

//______ITERATORS:__________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		iterator begin()
		{
			return iterator(_p);
		}
		const_iterator begin() const
		{
			return const_iterator(_p);
		}
		iterator end(){
			return iterator(_p + _size);
		}
		const_iterator end() const
		{
			return const_iterator(_p + _size);
		}

		reverse_iterator rbegin(){
			return reverse_iterator(_p + _size - 1);
		};

		const_reverse_iterator rbegin() const{
			return const_reverse_iterator(_p + _size - 1);
		};

		reverse_iterator rend(){
			return reverse_iterator(_p - 1);
		};

		const_reverse_iterator rend() const{
			return const_reverse_iterator(_p - 1);
		};


//______CAPACITY:___________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//Returns the number of elements in the vector.
		size_type size() const
		{
			return(_size);
		}

		//Returns the maximum number of elements that the vector can hold.
		size_type max_size() const{
			return (_myallocator.max_size());
		};


//______Resizes the container to contain count elements.
//		If the current size is greater than count,
//		the container is reduced to its first count elements.
//		If the current size is less than count,
//		1) additional default-inserted elements are appended
//		2) additional copies of value are appended.
		 void resize (size_type n, value_type val = value_type())
		 {
			if( n > _size)
			{
				iterator it = begin();
				for(size_t i = _size; i < n; ++i)
					push_back(val);
			}
			else
			{
				for(size_t i = n; i < _size; ++i)
					_myallocator.destroy(_p + i);
			}
			_size = n;
		}
//______Return size of allocated storage capacity
		size_type capacity() const
		{
			return(_capacity);
		}

//______Test whether vector is empty
		//Returns whether the vector is empty
		//(i.e. whether its size is 0).
		bool empty() const
		{
			return(_size == 0);
		}

//______Request a change in capacity
		//Requests that the vector capacity be at least enough to contain n elements.
		//If n is greater than the current vector capacity,
		// the function causes the container to reallocate its storage
		// increasing its capacity to n (or greater).
		//In all other cases, the function call does not cause a reallocation
		// and the vector capacity is not affected.
		//This function has no effect on the vector size and cannot alter its elements.
		void reserve (size_type n)
		{
			if(n > _capacity)
			{
				if(n > max_size())
					throw std::length_error("Oh, but I can not reserve the value more than max size..");
				else
				{
					size_t newcapacity = n;
					pointer newp(NULL);
					//allocate memory for newp
					try{
						newp = _myallocator.allocate(newcapacity);
					}
					catch(std::bad_alloc)
					{
						std::cout << "Oh, but I can not allocate memory....." << std::endl;
					}
					//and place there the value of old p[i]
					for(size_type i = 0; i < _size; ++i)
					{
					 _myallocator.construct(newp + i, _p[i]);
					}
					 //start destructor for old p
					 for(size_type i = 0; i < _size; ++i)
					 {
						 _myallocator.destroy(_p + i);
					 }
					 //deallocate memory for p
					 if(_p)
						_myallocator.deallocate(_p, _capacity);
					 //initiate p as a newp
					 _p = newp;
					 _capacity = newcapacity;
				}

			}
		 }

//______ELEMENT ACCESS:_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		reference operator[] (size_type n)
		{
			return(_p[n]);
		}
		const_reference operator[] (size_type n) const
		{
			return(_p[n]);
		}
		reference at (size_type n)
		{
			if(n >= _size)
				throw std::out_of_range("Vector");// is it right?
			return(_p[n]);
		}
		const_reference at (size_type n) const
		{
			if(n >= _size)
				throw std::out_of_range("Vector");// is it right?
			return(_p[n]);
		}
		reference front()// I should ask about ub
		{
			//Calling this function on an empty container causes undefined behavior.
			return(_p[0]);
		}
		const_reference front() const//I should ask about ub
		{
			//Calling this function on an empty container causes undefined behavior.
			return(_p[0]);
		}
		reference back()//I should ask about ub
		{
			//calling this function on an empty container causes undefined behavior.
			return(_p[_size - 1]);
		}
		const_reference back() const//I should ask about ub
		{
			//calling this function on an empty container causes undefined behavior.
			return(_p[_size - 1]);
		}

//______Modifiers___________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		template <class InputIterator>
		void assign (InputIterator first, typename EnableIf <!is_integral<InputIterator>::value, InputIterator>::type last)
		{
//			std::cout << " I am in assign by iterators" << std::endl;
			clear();
			size_t diff = (last - first);
			if((!_capacity)|| (_capacity < diff))
			{
				pointer newp;
				try{
					newp = _myallocator.allocate(diff);
				}
				catch(std::bad_alloc)
				{
					std::cout << "Oh, but I can not allocate memory....." << std::endl;
				}
				if(_p)
					_myallocator.deallocate(_p, _capacity);
				_p = newp;
				_capacity = diff;

			}
			for(size_type i = 0; first + i < last; ++i)
			{
				_myallocator.construct(_p + i, *(first + i));
			}
			_size+= diff;
		}


//______fill(2)
//		In the fill version (2),
//		the new contents are n elements, each initialized to a copy
//		of val. If a reallocation happens,the storage needed is
//		allocated using the internal allocator.
		void assign (size_type n, const value_type& val)
		{
			clear();
			if((!_capacity)|| (_capacity < n))
			{
				pointer newp;
				try{
					newp = _myallocator.allocate(n);
				}
				catch(std::bad_alloc){
					std::cout << "Oh, but I can not allocate memory....." << std::endl;
				}
				if (_p)
					_myallocator.deallocate(_p, _capacity);
				_p = newp;
				_capacity = n;
			}
			for(size_type i = 0; i < n; ++i)
			{
				_myallocator.construct(_p + i, val);
				++_size;
			}
		}
	
		void push_back(const value_type& val)
		{
			if(_size == _capacity)
			{
				size_t newcapacity;
				if(_capacity)
					newcapacity = _capacity * 2;
				else//(!_capacity)
					newcapacity = _capacity + 1;
				reserve(newcapacity);
			}
			_myallocator.construct(_p + _size, val);
			_size++;
		}

		void pop_back()
		{
			--_size;
			_myallocator.destroy(_p + _size);

		}

//______insert a single element (1)
//		insert value before pos
		iterator insert (iterator position, const value_type& val)
		{
			iterator start = begin();
			size_t count = position - start;
			insert(position, 1, val);

////			std::cout << "I am insert 1 : " <<  std::endl;
//			 iterator start = begin();
////			 while(1);
//			 size_t count = position - start;
//			if(_size + 1 > _capacity)
//			{
////				std::cout << "size = capacity : " <<  std::endl;
//				size_t newcapacity = _size *2;
//				size_t newsize = _size * 2;
//				pointer newp;
//				try{
//					newp = _myallocator.allocate(newcapacity);
//				}
//				catch(std::bad_alloc)
//				{
//					std::cout << "Oh, but I can not allocate memory....." << std::endl;
//				}
//				//allocate memory for newp and place there the value from the old p[i]
////				for(size_t i = 0; i < _size - it_l; ++i)
////				{
////					_p[it_f + i] = _p[it_l + i];
////				}
//				for(size_type i = 0; i < count; ++i)
//				{
//					_myallocator.construct(newp + i, _p[i]);
//				}
//				//allocate the new val
//				_myallocator.construct(newp + count, val);
//				//allocate memory for newp and place there the value from the old p[i]
//				for(size_type i = count; i < newsize; ++i)
//				{
//					_myallocator.construct(newp + i + 1, _p[i]);
//				}
////				_myallocator.construct(newp + _size, val);
//				//start destructor for old p
//				for(size_type i = 0; i < _size; ++i)
//				{
//	//				std::cout << "i am hrere" <<  std::endl;
//					_myallocator.destroy(_p + i);
//				}
//				//deallocate memory for p
//				if(_p)
//					_myallocator.deallocate(_p, _capacity);
//				//initiate p as a newp
//				_p = newp;
//				_size++;
//				_capacity = newcapacity;
//			}
//			else
//			{
////				std::cout << "it is enough space " <<  std::endl;
//				_myallocator.construct(_p + _size, _p[_size - 1]);
//				for(size_t i = _size + 1; i > count; --i)
//				{
//					_p[i] = _p[i-1];
//				}
//				_size++;
//			}
//			_p[count] = val;
////			_myallocator.construct(_p + count, val);
			return iterator(_p + count);
		 }

//______insert fill (2)
//______inserts count copies of the value before pos
		 void insert (iterator position, size_type n, const value_type& val){
			 

			iterator start = begin();
			size_t i_pos = (position - start);
			//if it is not enough space for inserting the elements
			if(_size + n >= _capacity)
			{
				size_t newcapacity ;//= 1;
				if (!_p)
				{
					newcapacity = n;
				}
				else
				{
					newcapacity = _capacity;
					if(newcapacity < _size + n)
					{
						newcapacity *=2;

					}
					if(newcapacity < _size + n)
					{
						newcapacity = _size + n;
					}
				}
				size_t newsize = _size + n;
				pointer newp = 0;
				//allocate memory for newp
				try{
					newp = _myallocator.allocate(newcapacity);
				}
				catch(std::bad_alloc)
				{
					std::cout << "Oh, but I can not allocate memory....." << std::endl;
				}
				//and place there the value of old p[i]
				size_t num = 0;
				try{
					for(size_type i = 0; i < i_pos; ++i)
					{
						_myallocator.construct(newp + i, _p[i]);
						num++;
					}
					for(size_t i = i_pos; i < i_pos + n; ++i)
					{
						_myallocator.construct(newp + i_pos, val);
						num++;
					}
					for(size_type i = i_pos + n; i < newsize; ++i)
					{
						_myallocator.construct(newp + i, _p[i - n]);
						num++;
					}
					//start destructor for old p
					for(size_type i = 0; i < _size; ++i)
					{
						_myallocator.destroy(_p + i);
					}
					//deallocate memory for p
					if(_p)
						_myallocator.deallocate(_p, _capacity);
					//initiate p as a newp
					_p = newp;
					_capacity = newcapacity;
				}

				catch(...){
					for(size_type i = 0; i < num; ++i)
					{
						_myallocator.destroy(newp + i);
					}
					_myallocator.deallocate(newp, newcapacity);
					throw;
				}
			}
			//if it is enough space for inserting the elements
			else
			{
				//move elements
				for(size_t i = 0; i < n; ++i)
				{
					_myallocator.construct(_p + _size + n - 1 - i , _p[_size - i - 1]);
				}
				for(size_t i = _size - 1; i > i_pos; --i)
				{
					 _p[i] = _p[i - n];
				}
			}
			for(size_t i = 0; i < n; ++i)
			{
			 _p[i_pos + i] = val;
			}
				_size+= n;

		}

//______insert range(3)
		template <class InputIterator>
		void insert (iterator position, InputIterator first, typename EnableIf <!is_integral<InputIterator>::value, InputIterator>::type last)
		{
			iterator start = begin();
			size_t i_pos = (position - start);
			size_t dif = last - first;
			if(_size + dif >= _capacity)
			{
				size_t newcapacity = 1;
				if (!_p){
					newcapacity = dif;
				}
				else {
					newcapacity = _capacity;
					if (newcapacity < _size + dif) {
						newcapacity *= 2;

					}
					if (newcapacity < _size + dif) {
						std::cout << "oh here" << std::endl;
						newcapacity = _size + dif;
					}
				}
				size_t newsize = _size + dif;
				pointer newp = 0;
				try{
					newp = _myallocator.allocate(newcapacity);
				}
				catch(std::bad_alloc)
				{
					std::cout << "Oh, but I can not allocate memory....." << std::endl;
				}
				size_t num = 0;
				//allocate memory for newp and place there the value of old p[i]
				try{
					for(size_type i = 0; i < i_pos; ++i)
					{
						_myallocator.construct(newp + i, _p[i]);
						num++;
					}
					for(size_t i = 0; i < dif; ++i)
					{
						_myallocator.construct(newp + i_pos + i, *first);
						++first;
						num++;
					}
					for(size_type i = i_pos + dif; i < newsize; ++i)
					{
						_myallocator.construct(newp + i, _p[i - dif]);
						num++;
					}
					//start destructor for old p
					for(size_type i = 0; i < _size; ++i)
					{
						_myallocator.destroy(_p + i);
					}
					//deallocate memory for p
					if(_p)
						_myallocator.deallocate(_p, _capacity);
					//initiate p as a newp
					_p = newp;
					_capacity = newcapacity;
					_size+= dif;
				}
				catch(...){
					for(size_type i = 0; i < num; ++i)
					{
						_myallocator.destroy(newp + i);
					}
					_myallocator.deallocate(newp, newcapacity);
					throw;
				}
			}
			else
			{
				std::cout << "it is enough space " <<  std::endl;
				//construct new elements
				for(size_t i = 0; i <= dif; ++i)
				{
					_myallocator.construct(_p + _size + dif - 1 - i , _p[_size - 1 - i]);
				}
				//move elements
				for(size_t i = _size - 1; i > i_pos; --i)
				{
					_p[i] = _p[i - dif];
				}
				_size+= dif;
				for(size_t i = 0; i < dif; ++i)
				{
					_p[i_pos + i] = *first;
					++first;
				}
			}
		};

		iterator erase (iterator position)
		{
			iterator start = begin();
			size_t i_pos = (position - start);
			for(size_t i = i_pos; i < _size; ++i)
				_p[i] = _p[i+1];
			_myallocator.destroy(_p + _size - 1);
			_size --;
			return iterator(_p + i_pos);
		}


//______Removes the elements in the range [first, last).
		iterator erase (iterator first, iterator last)
		{
			iterator start = begin();
			size_t it_f= first - start;
			size_t it_l = last - start;
			
			for(size_t i = 0; i < _size - it_l; ++i)
			{
				_p[it_f + i] = _p[it_l + i];
			}
			
			for(size_t i = it_l; i < _size ; ++i)
			{
				_myallocator.destroy(_p + i);
			}
			_size -= it_l - it_f;
			return iterator(_p + it_f);
		}

		void clear()
		{
			if(_size)
			{
				for(size_t i = 0; i < _size; i++)
				{
				_myallocator.destroy(_p + i);
				}
			}
			_size = 0;
		}

		void swap (vector& x)
		{
			ft::swap(_size, x._size);
			ft::swap(_capacity, x._capacity);
			ft::swap(_p, x._p);
			ft::swap(_myallocator, x._myallocator);
		}

//______Allocator___________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		allocator_type get_allocator() const{
			return(_myallocator);
		};

	};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//______NON MEMBER FUNCIONS_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	template< class T, class Alloc >
	bool operator==( const ft::vector<T,Alloc>& lhs,const ft::vector<T,Alloc>& rhs ){
			return(lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

	template< class T, class Alloc >
	bool operator!=( const ft::vector<T,Alloc>& lhs,const ft::vector<T,Alloc>& rhs ){
			return!(lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

	template< class T, class Alloc >
	bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ){
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	};

	template< class T, class Alloc >
	bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ){
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	};

	template< class T, class Alloc >
	bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ){
		return !(lhs > rhs);
	};

	template< class T, class Alloc >
	bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ){
		return !(lhs < rhs);
	};

};
	namespace std
	{
		template< class T, class Alloc >
		void swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs )
		{
		lhs.swap(rhs);
		};
	}

#endif

// https://habr.com/ru/post/274827/

// https://habr.com/ru/post/505632/

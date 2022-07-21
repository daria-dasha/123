
#pragma once
#include "IteratorsTraits.hpp"
#include "vector.hpp"
#include "RemoveConst.hpp"

namespace ft {
	template<class value>
	class random_access_iterator
	{
	public:
		typedef value *															iterator_type;
		typedef typename ft::iterator_traits<value *>::iterator_category		iterator_category;

		//value на что итератор указывает	
		typedef typename ft::iterator_traits<value *>::value_type				value_type;
		typedef typename ft::iterator_traits<value *>::difference_type			difference_type;
		typedef typename ft::iterator_traits<value *>::pointer					pointer;
		typedef typename ft::iterator_traits<value *>::reference				reference;
		
	public:
		pointer _ptr_first;

	public:
		//default
		random_access_iterator() : _ptr_first(NULL)
		{
			_ptr_first = 0;
				// std::cout << RED << "hello i am default constructor of iterator!" <<  SHALLOW << std::endl;
		};

		//pointer constructor
		random_access_iterator(pointer p) : _ptr_first(p)
		{
			// std::cout << RED << "hello i am pointer constructor of iterator!" <<  SHALLOW << std::endl;
		};

		//copy
		// template<class U><U>
		random_access_iterator(const random_access_iterator<typename std::remove_const<value_type>::type > & src) : _ptr_first(&(*src))//
		{
				// std::cout << RED <<  "hello i am copy constructor of iterator!" <<  SHALLOW << std::endl;
		}

		random_access_iterator &
		operator=( const random_access_iterator <typename ft::remove_const<value_type>::type>  &other)// 
		{
			// std::cout << "hahaa" << std::endl;
			_ptr_first = &(*other);
			return *this;
		}
		
		//desctuctor
		virtual ~random_access_iterator()
		{
			//std::cout << RED << "goodbuy iterator!" <<  SHALLOW << std::endl;
		};

		//OPERATORS
		random_access_iterator &operator++()
		{
			++_ptr_first;
			return *this;
		}

		random_access_iterator operator++(int)
		{
			random_access_iterator tmp(*this);
			++_ptr_first;
			return tmp;
		}

		random_access_iterator &operator--() {
			--_ptr_first;
			return *this;
		}

		random_access_iterator operator--(int) {
			random_access_iterator tmp(*this);
			--_ptr_first;
			return tmp;
		}

		random_access_iterator& operator+=(const difference_type& d)
		{
			_ptr_first += d;
			return (*this);
		}
		random_access_iterator& operator-=(const difference_type& d)
		{
			_ptr_first -= d;
			return (*this);
		}

		random_access_iterator operator+(const size_t &d) const {
			return _ptr_first + d;
		}

		random_access_iterator operator-(const size_t &d) const {
			return _ptr_first - d;
		}

		bool operator<(const random_access_iterator &other) const {
			return _ptr_first < other._ptr_first;
		}

		bool operator>(const random_access_iterator &other) const {
			return _ptr_first > other._ptr_first;
		}

		size_t operator-(random_access_iterator<value_type> &other) const
		{
			//	std::cout << "i am in operator - in iterator" << std::endl;
			return (this->_ptr_first - other._ptr_first);
		}

		size_t operator+(random_access_iterator<value_type> &other) const {
			//	std::cout << "i am in operator - in iterator" << std::endl;
			return (this->_ptr_first + other._ptr_first);
		}

		reference operator*() const {
			//std::cout << "i am in operator * in iterators" << std::endl;
			return (*(_ptr_first));
		}
		reference operator->() const {
			//std::cout << "i am in operator * in iterators" << std::endl;
			return (_ptr_first);
		}
		reference operator[](difference_type d) const {
			return *(_ptr_first + d);
		}

		// bool operator == (const random_access_iterator & rhs)
		// {
		// 		return(_ptr_first == rhs._ptr_first);
		// }
		
		// bool operator != (const random_access_iterator & rhs)
		// {
		// 		return (_ptr_first != rhs._ptr_first);
		// }

		friend bool operator==(
				const random_access_iterator<value>& lhs,
				const random_access_iterator<value>& rhs)
		{
			return (lhs._ptr_first == rhs._ptr_first);
		}

		friend bool operator!=(
			const random_access_iterator<value>& lhs,
			const random_access_iterator<value>& rhs)
		{
			return !(lhs._ptr_first == rhs._ptr_first);
		}

	};
}
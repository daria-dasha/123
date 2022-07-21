
#pragma once
#include "IteratorsTraits.hpp"
#include "vector.hpp"
#include "RemoveConst.hpp"

namespace ft{
	template <class value>
	class reverse_iterator
	{
	public:
		typedef value	*														iterator_type;
		typedef typename ft::iterator_traits<value *>::iterator_category		iterator_category;

		//value на что итератор указывае
		typedef typename ft::iterator_traits<value *>::value_type				value_type;
		typedef typename ft::iterator_traits<value *>::iterator_category		iterator;
		typedef typename ft::iterator_traits<value *>::difference_type			difference_type;
		typedef typename ft::iterator_traits<value *>::pointer					pointer;
		typedef typename ft::iterator_traits<value *>::reference				reference;

	protected:
		pointer _ptr_first;

	public:
		//default
		reverse_iterator() : _ptr_first(NULL)
		{
		//	std::cout << RED << "hello i am default constructor of iterator!" <<  SHALLOW << std::endl;
		};

		//pointer constructor
		reverse_iterator(pointer p) : _ptr_first(p)
		{
			//	std::cout << RED << "hello i am pointer constructor of iterator!" <<  SHALLOW << std::endl;
		};

		//copy
		reverse_iterator(const reverse_iterator &rhs) : _ptr_first(rhs._ptr_first)
		{
			//std::cout << RED <<  "hello i am copy constructor of iterator!" <<  SHALLOW << std::endl;
			if (this != &rhs)
				*this = rhs;
		}

		reverse_iterator &
		operator=(reverse_iterator<typename ft::remove_const<value_type>::type> const &other)
		{
			//std::cout << RED <<  "hello i am assign = from iterator!" <<  SHALLOW << std::endl;
			if (this == &other)
				return *this;
			else
				_ptr_first = other._ptr_first;
			return *this;
		}

		//desctuctor
		virtual ~reverse_iterator()
		{
			//std::cout << RED << "goodbuy iterator!" <<  SHALLOW << std::endl;
		};

		//OPERATORS
		reverse_iterator &operator++()
		{
			--_ptr_first;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(*this);
			--_ptr_first;
			return tmp;
		}

		reverse_iterator &operator--()
		{
			++_ptr_first;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(*this);
			++_ptr_first;
			return tmp;
		}

		reverse_iterator& operator+=(const difference_type& d)
		{
			_ptr_first -= d;
			return (*this);
		}
		reverse_iterator& operator-=(const difference_type& d)
		{
			_ptr_first += d;
			return (*this);
		}

		reverse_iterator operator+(const size_t &d) const {
			return _ptr_first - d;
		}

		reverse_iterator operator-(const size_t &d) const {
			return _ptr_first + d;
		}

		bool operator<(const reverse_iterator &other) const {
			return _ptr_first < other._ptr_first;
		}

		bool operator>(const reverse_iterator &other) const {
			return _ptr_first > other._ptr_first;
		}

		size_t operator-(reverse_iterator<value_type> &other) const {
			return (this->_ptr_first + other._ptr_first);
		}

		size_t operator+(reverse_iterator<value_type> &other) const {
			return (this->_ptr_first - other._ptr_first);
		}

		reference operator*() const {
			return *(_ptr_first);
		}

		reference operator->() const {
			return (_ptr_first);
		}

		reference operator[](difference_type d) const {
			return *(_ptr_first - d);
		}

	};

}

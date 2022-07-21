

#pragma once
#include <iostream>
#include <ostream>

namespace ft{

	//This class couples together a pair of values,
	// which may be of different types (T1 and T2).
	// The individual values can be accessed through
	// its public members first and second.
	template <class T1, class T2>
	struct pair
	{
	public:
		typedef T1			first_type;
		typedef T2			second_type;

		first_type			first;
		second_type			second;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//______MEMBER FUNCIONS_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//default constructor(1)
		//Constructs a pair object with its elements value-initialized.
		pair():first(T1()), second(T2()){
			// std::cout << "Hello! I am pair constructor 1: default" << std::endl;
		};

		//copy / move constructor (and implicit conversion)(2)
		// The object is initialized with the contents of the pr pair object.
		// The corresponding member of pr is passed to the constructor of each of its members.
		template<class U, class V>
		pair (const pair<U,V>& pr): first(pr.first), second(pr.second)
		{
			// std::cout << "Hello! I am pair constructor 2: copy" << std::endl;
		};

		//initialization constructor(3)
		pair (const first_type& a, const second_type& b):first(a), second(b){
			// std::cout << "Hello! I am pair constructor 3: initialization" << std::endl;
		};

		~pair(){
			// std::cout << "Goodbuy from the pair!" << std::endl;
		}

		//implicitly declared:
		//copy (1)
		pair& operator= (const pair& pr)
		{
			first = pr.first;
			second = pr.second;
			return *this;
		};
	};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//______NON MEMBER FUNCIONS_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }


	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		// std::cout << "Hello! I am in make_pair" << std::endl;
		return ( pair<T1,T2>(x,y) );
	};

	// template <class T1, class T2>
	// std::ostream& operator <<(std::ostream& os, const pair<T1, T2>& my_pair)
	// {
	// 	os << "first: " << my_pair.first << " " << "second: " << my_pair.second << std::endl;
	// 	return os;
	// }
}
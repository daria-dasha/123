#include <iostream>
#include "Colors.hpp"
#include <fstream>
// set 1 to use ft::set header. set 0 to use ft::set header.
#if 1 //CREATE A REAL STL EXAMPLE
	#include <set>
	#include <stack>
	#include <vector>
	namespace ft = std;
	#define MESSAGE "Check_std_container"
#else
	#include "set.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
	#include "Utility.hpp"
	#define MESSAGE "Check_ft_container"
#endif

template<typename K, typename V>
void print_set(ft::set<K, V> const &m)
{
	std::cout  << "set contains: ";
	for (typename ft::set <K, V>::const_iterator it = m.begin(); it != m.end(); ++it) {
		std::cout  << (*it) << " ";
	}
	std::cout << std::endl;
}

void check_begin_end()
{
	int myints[] = {75,23,65,42,13};
	ft::set<int> myset (myints,myints+5);

	std::cout << "myset contains:";
	for (ft::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';
	}

void check_clear()
{
	ft::set<int> myset;

	myset.insert (100);
	myset.insert (200);
	myset.insert (300);

	std::cout << "myset contains:";
	for (ft::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	myset.clear();
	myset.insert (1101);
	myset.insert (2202);

	std::cout << "myset contains:";
	for (ft::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void check_size() //OK!
{
	ft::set<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';	
	for (int i=0; i<10; ++i) myints.insert(i);
	std::cout << "1. size: " << myints.size() << '\n';	
	myints.insert (100);
	std::cout << "2. size: " << myints.size() << '\n';	
	myints.erase(5);
	std::cout << "3. size: " << myints.size() << '\n';	

}

void check_empty() //OK!
{
	ft::set<int> myset;

	myset.insert(20);
	myset.insert(30);
	myset.insert(10);

	std::cout << "myset contains:";
	while (!myset.empty())
	{
		std::cout << ' ' << *myset.begin();
		myset.erase(myset.begin());
	}
	std::cout << '\n';
}

void check_find() //OK!
{
	ft::set<int> myset;
	ft::set<int>::iterator it;

	// set some initial values:
	for (int i=1; i<=5; i++) myset.insert(i*10);    // set: 10 20 30 40 50

	it=myset.find(20);
	myset.erase (it);
	myset.erase (myset.find(40));

	std::cout << "myset contains:";
	for (it=myset.begin(); it!=myset.end(); ++it)
	  std::cout << ' ' << *it;
	std::cout << '\n';
}

void check_get_allocator()
{
	ft::set<int> myset;
	int * p;
	unsigned int i;

	// allocate an array of 5 elements using myset's allocator:
	p=myset.get_allocator().allocate(5);

	// assign some values to array
	for (i=0; i<5; i++) p[i]=(i+1)*10;

	std::cout << "The allocated array contains:";
	for (i=0; i<5; i++) std::cout << ' ' << p[i];
	std::cout << '\n';

	myset.get_allocator().deallocate(p,5);
}

void check_count()
{
	ft::set<int> myset;

	// set some initial values:
	for (int i=1; i<5; ++i) myset.insert(i*3);    // set: 3 6 9 12

	for (int i=0; i<10; ++i)
	{
		std::cout << i;
		if (myset.count(i)!=0)
			std::cout << " is an element of myset.\n";
		else
			std::cout << " is not an element of myset.\n";
	}
}

void check_max_size()
{
	int i;
	ft::set<int> myset;

	if (myset.max_size()>1000)
	{
		for (i=0; i<1000; i++) myset.insert(i);
		std::cout << "The set contains 1000 elements.\n";
	}
	else std::cout << "The set could not hold 1000 elements.\n";
}

void check_rbegin_rend()
{
	int myints[] = {21,64,17,78,49};
	ft::set<int> myset (myints,myints+5);

	ft::set<int>::reverse_iterator rit;

	std::cout << "myset contains:";
	for (rit=myset.rbegin(); rit != myset.rend(); ++rit)
		std::cout << ' ' << *rit;

	std::cout << '\n';
}

bool	fncomp (int lhs, int rhs) {return lhs<rhs;}

struct classcomp {
	bool operator() (const int& lhs, const int& rhs) const
	{return lhs<rhs;}
};

void check_constructor()
{
	ft::set<int> first;                           // empty set of ints
	print_set(first);
	int myints[]= {10,20,30,40,50};
	ft::set<int> second (myints,myints+5);        // range
	print_set(second);
	ft::set<int> third (second);                  // a copy of second
	print_set(third);
	ft::set<int> fourth (second.begin(), second.end());  // iterator ctor.
	print_set(fourth);
	ft::set<int,classcomp> fifth;                 // class as Compare
	print_set(fifth);
	bool(*fn_pt)(int,int) = fncomp;
	ft::set<int,bool(*)(int,int)> sixth (fn_pt);  // function pointer as Compare


}

void check_key_compare()
{
	ft::set<int> myset;
	int highest;

	ft::set<int>::key_compare mycomp = myset.key_comp();

	for (int i=0; i<=5; i++) myset.insert(i);

	std::cout << "myset contains:";

	highest=*myset.rbegin();
	ft::set<int>::iterator it=myset.begin();
	do {
		std::cout << ' ' << *it;
	} while ( mycomp(*(++it),highest) );

	std::cout << '\n';
}

void check_value_compare()
{
	ft::set<int> myset;

	ft::set<int>::value_compare mycomp = myset.value_comp();

	for (int i=0; i<=5; i++) myset.insert(i);

	std::cout << "myset contains:";

	int highest=*myset.rbegin();
	ft::set<int>::iterator it=myset.begin();
	do {
		std::cout << ' ' << *it;
	} while ( mycomp(*(++it),highest) );

	std::cout << '\n';
}

void check_upper_bound_lower_bound()
{
	ft::set<int> myset;
	ft::set<int>::iterator itlow,itup;

	for (int i=1; i<10; i++) myset.insert(i*10); // 10 20 30 40 50 60 70 80 90

	itlow=myset.lower_bound (30);                //       ^
	itup=myset.upper_bound (60);                 //                   ^

	myset.erase(itlow,itup);                     // 10 20 70 80 90

	std::cout << "myset contains:";
	for (ft::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void check_erase()
{
	ft::set<int> myset;
	ft::set<int>::iterator it;

	// insert some values:
	for (int i=1; i<10; i++) myset.insert(i*10);  // 10 20 30 40 50 60 70 80 90

	it = myset.begin();
	++it;                                         // "it" points now to 20

	myset.erase (it);

	myset.erase (40);

	it = myset.find (60);
	myset.erase (it, myset.end());

	std::cout << "myset contains:";
	for (it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void check_equal_range()
{
	ft::set<int> myset;

	for (int i=1; i<=5; i++) myset.insert(i*10);   // myset: 10 20 30 40 50
	std::cout << "Size : " << int (myset.size()) << '\n';

	ft::pair<ft::set<int>::const_iterator,ft::set<int>::const_iterator> ret;
	ret = myset.equal_range(30);

	std::cout << "the lower bound points to: " << *ret.first << '\n';
	std::cout << "the upper bound points to: " << *ret.second << '\n';
}

void check_equality_operator()
{
	int myints[]={ 12,82,37,64,15 };
	ft::set<int> first (myints,myints+5);   // set with 5 ints
	ft::set<int> second;                    // empty set

	second = first;                          // now second contains the 5 ints
	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';

	first = ft::set<int>();                 // and first is empty

	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
};

void check_insert()
{
	ft::set<int> myset;
	ft::set<int>::iterator it;
	ft::pair<ft::set<int>::iterator,bool> ret;

	// set some initial values:
	for (int i=1; i<=5; ++i) myset.insert(i*10);    // set: 10 20 30 40 50
	std::cout << "Size : " << int (myset.size()) << '\n';
	ret = myset.insert(20);               // no new element inserted
	std::cout << "Size : " << int (myset.size()) << '\n';
	if (ret.second==false) it=ret.first;  // "it" now points to element 20
	std::cout << "Size : " << int (myset.size()) << '\n';
	myset.insert (it,25);                 // max efficiency inserting
	myset.insert (it,24);                 // max efficiency inserting
	myset.insert (it,26);                 // no max efficiency inserting
	std::cout << "Size : " << int (myset.size()) << '\n';
	int myints[]= {5,10,15};              // 10 already in set, not inserted
	myset.insert (myints,myints+3);
	std::cout << "Size : " << int (myset.size()) << '\n';
	std::cout << "myset contains:";
	for (it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}


template < class T >
void print_all(T & my)
{
	std::cout << "vector contains:";
	std::cout << GREEN;
	for(size_t i = 0; i < my.size(); ++ i)
		std::cout << " " <<  my[i] ;
	std::cout<<SHALLOW;
	std::cout << RED;
	std::cout << " | | ";
	for(size_t i = my.size(); i < my.capacity(); ++ i)
		std::cout << " " <<  my[i] ;
	std::cout<<SHALLOW;
	std::cout << std::endl;
}
void check_invalidations_of_iterators()
{
	ft::set < int> m1;
	m1.insert(5);
	m1.insert(6);
	m1.insert(7);
	ft::set < int, int >::iterator it1 = m1.end();
	it1--;
	std::cout << RED << "it 1: " << *it1 << SHALLOW  << std::endl;
	m1.insert(4);
	std::cout << RED << "it 1: " << *it1 << SHALLOW  << std::endl;
	m1.erase(7);
	std::cout << RED << "it 1: " << *it1 << SHALLOW  << std::endl;
}

void check_iterators()
{
	ft::set <int> m;
	m.insert(5);
	m.insert(5);
	ft::set<int>::iterator it = m.begin();
	ft::set<int>::const_iterator itc = m.end();
	itc = it;
	// it = itc;
}

int main()
{
	std::cout << GREEN << MESSAGE << SHALLOW << std::endl;
	std::cout << RED << "set" << SHALLOW << std::endl;
	// check_begin_end();
	// check_clear();
	// check_size();
	// check_empty();
	// check_find();
	// check_get_allocator();
	// check_count();
	// check_max_size();
	// check_rbegin_rend();
	// check_constructor();
	// check_key_compare();
	// check_value_compare();
	// check_upper_bound_lower_bound();
	// check_erase();
	// check_equal_range();
	// check_equality_operator();
	// check_insert();
	check_invalidations_of_iterators();
	// check_iterators();
	return 0;
}

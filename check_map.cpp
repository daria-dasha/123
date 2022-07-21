#include <iostream>
#include "Colors.hpp"
#include <fstream>
// set 1 to use std::map header. set 0 to use ft::map header.
#if 1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
	#define MESSAGE "Check_std_container"
#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
	#include "Utility.hpp"
	#define MESSAGE "Check_ft_container"
#endif

// template<typename K, typename V>
// void print_map(ft::map<K, V> const &m)
// {
// 	for (typename ft::map <K, V>::iterator it = m.cbegin(); it != m.cend(); ++it) {
// 		std::cout << "{" << (*it).first << ": " << (*it).second << "}\n";
// 	}
// }

void check_begin_end()
{
	ft::map<char,int> mymap;

	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;
	mymap['d'] = 300;
	// ft::map<char,int>::iterator it=mymap.begin();
	// show content:
	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
		std::cout << std::endl;
	ft::map<char,int>::iterator it =mymap.end();
	it--;
	while(1)
	{
		if(it == mymap.begin())
		{
			std::cout << it->first << " => " << it->second << '\n';
			return;
		}
		std::cout << it->first << " => " << it->second << '\n';
 		it--;
	}
}

void check_clear()
{
	ft::map<char,int> mymap;
	mymap['x']=100;
	mymap['y']=200;
	mymap['z']=300;
	std::cout << "mymap contains:\n";
	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
	  std::cout << it->first << " => " << it->second << '\n';
	mymap.clear();
	mymap['a']=1101;
	mymap['b']=2202;
	std::cout << "mymap contains:\n";
	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void check_size()
{
	ft::map<char,int> mymap;
	mymap['a']=101;
	mymap['b']=202;
	mymap['c']=302;
	std::cout << "mymap.size() is " << mymap.size() << '\n';
}

void check_empty()
{
	ft::map<char,int> mymap;
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	std::cout << mymap.empty() << std::endl;
	while (!mymap.empty())
	{
		std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
		mymap.erase(mymap.begin());
	}
}

void check_find()
{
	ft::map<char,int> mymap;
	ft::map<char,int>::iterator it;
	mymap['a']=50;
	mymap['b']=100;
	mymap['c']=150;
	mymap['d']=200;
	it = mymap.find('b');
	if (it != mymap.end())
		mymap.erase (it);
	// print content:
	std::cout << "elements in mymap:" << '\n';
	std::cout << "a => " << mymap.find('a')->second << '\n';
	std::cout << "c => " << mymap.find('c')->second << '\n';
	std::cout << "d => " << mymap.find('d')->second << '\n';
}

void check_get_allocator()
{
	int psize;
	ft::map<char,int> mymap;
	ft::pair<const char,int>* p;
	// allocate an array of 5 elements using mymap's allocator:
	p=mymap.get_allocator().allocate(5);
	// assign some values to array
	psize = sizeof(ft::map<char,int>::value_type)*5;
	std::cout << "The allocated array has a size of " << psize << " bytes.\n";
	mymap.get_allocator().deallocate(p,5);
}

void check_count()
{
	ft::map<char,int> mymap;
	char c;
	mymap ['a']=101;
	mymap ['c']=202;
	mymap ['f']=303;
	for (c='a'; c<'h'; c++)
	{
		std::cout << c;
		if (mymap.count(c)>0)
			std::cout << GREEN << " is an element of mymap.\n" << SHALLOW;
		else 
			std::cout << " is not an element of mymap.\n";
	}
}

void check_max_size()
{
	int i;
	ft::map<int,int> mymap;
	if (mymap.max_size()>1000)
	{
		for (i=0; i<1000; i++) mymap[i]=0;
		std::cout << "The map contains 1000 elements.\n";
	}
	else std::cout << "The map could not hold 1000 elements.\n";
}

void check_square_brackets()
{
	ft::map<char,std::string> mymap;
	mymap['a']="an element";
	mymap['b']="another element";
	mymap['c']=mymap['b'];
	std::cout << "mymap['a'] is " << mymap['a'] << '\n';
	std::cout << "mymap['b'] is " << mymap['b'] << '\n';
	std::cout << "mymap['c'] is " << mymap['c'] << '\n';
	std::cout << "mymap['d'] is " << mymap['d'] << '\n';
	std::cout << "mymap now contains " << mymap.size() << " elements.\n";
	// mymap.rb_print();
}

void check_rbegin_rend()
{
	ft::map<char,int> mymap;

	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;
	mymap['b'] = 400;

	// show content:
	ft::map<char,int>::reverse_iterator rit;
	std::cout << "from begin to end: " << std::endl;
	for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
		std::cout << rit->first << " => " << rit->second << '\n';
	rit = mymap.rend();
	rit--;
	std::cout << std::endl;
	std::cout << "from end-- to begin: " << std::endl;
	for (; rit!=mymap.rbegin(); --rit)
		std::cout << rit->first << " => " << rit->second << '\n';
	// mymap.rb_print();
}

void check_constructor()
{
	ft::map<char,int> mymap;

	// first insert function version (single parameter):
	mymap.insert ( ft::pair< char,int>('a',100) );
	mymap.insert ( ft::pair< char,int>('z',200) );

	ft::pair<ft::map<char,int>::iterator,bool> ret;
	ret = mymap.insert ( ft::pair<char,int>('z',500) );
	if (ret.second==false)
	{
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}

	// second insert function version (with hint position):
	ft::map<char,int>::iterator it = mymap.begin();
	mymap.insert (it, ft::pair<char,int>('b',300));	// max efficiency inserting
	mymap.insert (it, ft::pair<char,int>('c',400));	// no max efficiency inserting

	// mymap.rb_print();
	// third insert function version (range insertion):
	ft::map <char,int> anothermap;
	anothermap.insert(mymap.begin(),mymap.find('c'));

	// showing contents:
	std::cout << "mymap contains:\n";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it=anothermap.begin(); it!=anothermap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void check_key_compare()
{
	ft::map<char,int> mymap;

	ft::map<char,int>::key_compare mycomp = mymap.key_comp();
	mymap['a']=100;
	mymap['b']=200;
	mymap['c']=300;
	std::cout << "mymap contains:\n";
	char highest = mymap.rbegin()->first;	 // key value of last element
	ft::map<char,int>::iterator it = mymap.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( mycomp((*it++).first, highest) );
	std::cout << '\n';
}

void check_value_compare()
{
	ft::map<char,int> mymap;

	mymap['x']=1001;
	mymap['y']=2002;
	mymap['z']=3003;

	std::cout << "mymap contains:\n";

	ft::pair<char,int> highest = *mymap.rbegin(); // last element

	ft::map<char,int>::iterator it = mymap.begin();
	do {
	std::cout << it->first << " => " << it->second << '\n';
	} while ( mymap.value_comp()(*it++, highest) );
}

void check_upper_bound_lower_bound()
{
	ft::map<char,int> mymap;
	ft::map<char,int>::iterator itlow,itup;

	mymap['a']=20;
	mymap['b']=40;
	mymap['c']=60;
	mymap['d']=80;
	mymap['e']=100;

	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << std::endl;
	itlow=mymap.lower_bound ('b');  // itlow points to b
	itup=mymap.upper_bound ('d');   // itup points to e (not d!)
	
	std::cout << "lower bound " << itlow->first << std::endl;
	std::cout << "upper bound " << itup->first << std::endl;
	mymap.erase(itlow,itup);		// erases [itlow,itup)

	// print content:
	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	ft::map<int,int> map2;
	map2.insert(ft::make_pair(10, 10));
	map2.insert(ft::make_pair(20, 20));
	map2.insert(ft::make_pair(30, 30));
	map2.insert(ft::make_pair(40, 40));
	map2.insert(ft::make_pair(50, 50));
	map2.insert(ft::make_pair(60, 60));
	// map2.rb_print();
	ft::map<int,int>::iterator itl;
	itl = map2.lower_bound(1);
	std::cout << itl->first << " => " << itl->second << '\n';
	itl = map2.lower_bound(11);
	std::cout << itl->first << " => " << itl->second << '\n';
	itl = map2.lower_bound(21);
	std::cout << itl->first << " => " << itl->second << '\n';

}

void check_erase()
{
	ft::map<char,int> mymap;
	ft::map<char,int>::iterator it;
	// insert some values:
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=40;
	mymap['e']=50;
	mymap['f']=60;
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "SIZE: " << mymap.size() << std::endl;
	std::cout << std::endl;

	// erasing by iterator
	std::cout << "erasing by iterator with key 'b'" << std::endl;
	it=mymap.find('b');
	mymap.erase (it);
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "SIZE: " << mymap.size() << std::endl;
	std::cout << std::endl;

	// erasing by key
	std::cout << "erasing by key 'c'" << std::endl;
	std::cout << "erase by key returned: " << mymap.erase ('c') << std::endl;
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "SIZE: " << mymap.size() << std::endl;
	std::cout << std::endl;

	// erasing by range
	std::cout << "erasing by range from 'e' to end" << std::endl;
	it=mymap.find ('e');
	mymap.erase ( it, mymap.end() );
	// show content:
	for (it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "SIZE: " << mymap.size() << std::endl;
	// mymap.rb_print();
}

void check_equal_range()
{
	ft::map<char,int> mymap;
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	ft::pair < ft::map<char,int>::iterator,ft::map<char,int>::iterator > ret;
	ret = mymap.equal_range('b');
	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';
	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';
}

void check_at()
{
	ft::map<std::string,int> mymap;
	mymap["alpha"] = 100;
	mymap["beta"] = 200;
	mymap["gamma"] = 300;

	mymap.at("alpha") = 10;
	mymap.at("beta") = 20;
	mymap.at("gamma") = 30;
	ft::map<std::string,int>::iterator it=mymap.begin();
	// show content:
	for (; it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << std::endl;
}

void check_operator_assign()
{
	ft::map<char,int> mymap;

	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;
	mymap['d'] = 300;
	ft::map<char,int>::iterator it=mymap.begin();
	// // show content:
	for (; it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << std::endl;
	
	// ft::map<char,int> newmap;
	// newmap = mymap;
	// for (ft::map<char,int>::iterator it=newmap.begin(); it!=newmap.end(); ++it)
	// 	std::cout << it->first << " => " << it->second << '\n';
	// std::cout << std::endl;
}

void check_equality_operator()
{
		ft::map<char,int> mymap;

		mymap['b'] = 100;
		mymap['a'] = 200;
		mymap['c'] = 300;
		mymap['d'] = 300;

		ft::map<char,int> mymap1;

		mymap1['b'] = 100;
		mymap1['a'] = 200;
		mymap1['c'] = 300;
		mymap1['d'] = 300;
	if(mymap == mymap1)
		std::cout << "maps are equal!" << std::endl;
};

void check_insert()
{
	ft::map<char,int> mymap;
	// first insert function version (single parameter):
	mymap.insert ( ft::pair<char,int>('a',100) );
	mymap.insert ( ft::pair<char,int>('z',200) );

	ft::pair<ft::map<char,int>::iterator,bool> ret;
	ret = mymap.insert ( ft::pair<char,int>('z',500) );
	if (ret.second==false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}
	else {
		std::cout << "element 'z'has been created";
		std::cout << " with a value of " << ret.first->second << '\n';
	}
	// second insert function version (with hint position):
	ft::map<char,int>::iterator it = mymap.begin();
	mymap.insert (it, ft::pair<char,int>('b',300));	// max efficiency inserting
	mymap.insert (it, ft::pair<char,int>('c',400));	// no max efficiency inserting

	// third insert function version (range insertion):
	ft::map<char,int> anothermap;
	anothermap.insert(mymap.begin(),mymap.find('c'));

	// showing contents:
	std::cout << "mymap contains:\n";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it=anothermap.begin(); it!=anothermap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
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

// // /*Uncomment to see errors*/
void check_iterators()
{
	
	ft::map <int, int> m;
	m.insert(ft::make_pair(5, 5));
	ft::map<int, int>::iterator it = m.begin();
	ft::map<int, int>::const_iterator itc = m.end();
	itc = it;
	// it = itc;
}

// print out a std::pair
template <class Os, class U, class V>
Os& operator<<(Os& os, const std::pair<U, V>& p) {
	return os << p.first << ":" << p.second;
}
 
// print out a container
// template <class Os, class Co>
// Os& operator<<(Os& os, const Co& co) {
// 	os << "{";
// 	for (& i : co) { os << ' ' << i; }
// 	return os << " }\n";
// }
template <class T1, class T2>
std::ostream& operator <<(std::ostream& os, const ft::pair<T1, T2>& my_pair)
{
	os << my_pair.first << ":" << my_pair.second << " ";
	return os;
}

template< class Os, typename K, typename M>
Os& operator<<(Os& os, ft::map<K, M> const &m)
{
	os << "{";
	for (typename ft::map <K, M>::const_iterator it = m.begin(); it != m.end(); ++it)
		{ os << ' ' << *it; }
	os << "} ";
	return os << "\n" ;
}
 
void check_swap()
{
	ft::map <std::string, std::string> m1, m2;
	m1.insert(ft::make_pair("γ", "gamma"));
	m1.insert(ft::make_pair("β", "beta")); 
	m1.insert(ft::make_pair("α", "alpha"));	
	m1.insert(ft::make_pair("γ", "gamma"));

	m2.insert(ft::make_pair("ε", "epsilon"));
	m2.insert(ft::make_pair("δ", "delta"));
	m2.insert(ft::make_pair("ε", "epsilon"));
 
	const ft::pair<std::string, std::string> & ref = *(m1.begin());
	ft::map< std::string, std::string> ::const_iterator iter = (m1.begin());
	iter++;
 
	std::cout << "──────── before swap ────────\n"
			  << "m1: " << m1 << "m2: " << m2 << "ref: " << ref
			  << "\niter: " << *iter << '\n';
 
	m1.swap(m2);
 
	std::cout << "──────── after swap ────────\n"
			  << "m1: " << m1 << "m2: " << m2 << "ref: " << ref
			  << "\niter: " << *iter << '\n';
 
	// Note that every iterator referring to an element in one container before
	// the swap refers to the same element in the other container after the swap.
	// Same is true for references.
}


int main()
{
	std::cout << GREEN << MESSAGE << SHALLOW << std::endl;
	std::cout << RED << "MAP" << SHALLOW << std::endl;
	// check_begin_end();
	// check_clear();
	// check_size();
	// check_empty();
	// check_find();
	// check_get_allocator();
	// check_count();
	// check_max_size();
	// check_square_brackets();
	// check_rbegin_rend();
	// check_constructor();
	// check_key_compare();
	// check_value_compare();
	// check_upper_bound_lower_bound();
	// check_erase();
	// check_equal_range();
	// check_at();
	// check_operator_assign();
	// check_equality_operator();
	// check_insert();
	check_swap();
	// check_iterators();
	
	return 0;
}

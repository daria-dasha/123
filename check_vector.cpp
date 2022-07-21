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

template < class T >
void print_all(T & my)
{
	std::cout << "vector contains:";
	std::cout << GREEN;
	for(size_t i = 0; i < my.size(); ++ i)
	    std::cout << " " <<  my[i] ;
	std::cout<< SHALLOW;
	std::cout << RED;
	std::cout << " | | ";
	for(size_t i = my.size(); i < my.capacity(); ++ i)
	    std::cout << " " <<  my[i] ;
	std::cout<< SHALLOW;
	std::cout << std::endl;
}

void check_push_back_pop_back_size_capacity()
{
	ft::vector <int> z;
	print_all(z);
	for(int i = 0; i <3 ; ++i)
	{
		std::cout << "capacity: " << z.capacity() << std::endl;
		std::cout << "size: " << z.size() << std::endl;
		z.push_back(5);
		print_all(z);
		std::cout << "capacity: " << z.capacity() << std::endl;
		std::cout << "size: " << z.size() << std::endl << std::endl;
	}
	for(int i = 0; i < 3 ; ++i)
	{
//		z.pop_back();
		print_all(z);
		std::cout << "capacity: " << z.capacity() << std::endl;
		std::cout << "size: " << z.size() << std::endl << std::endl;
	}
}

void check_operator_index_at() {
	ft::vector <int> p(2, 8);
	print_all(p);
	std::cout << "p[0]: " << p[0] << std::endl;
	std::cout << "p[-5]: " << p[-5] << std::endl;
	std::cout << "p[25]: " << p[25] << std::endl;
	std::cout << "at 0: " << p.at(0) << std::endl;
//	std::cout << "at -5: " << p.at(-5) << std::endl;
	std::cout << "at 25: " << p.at(25) << std::endl;
}

void check_front()
{
	ft::vector<int> myvector;
	std::cout <<" front : " << myvector.front() << std::endl;
	myvector.push_back(78);
	myvector.push_back(16);
	// now front equals 78, and back 16
	std::cout <<" front : " << myvector.front() << std::endl;
	std::cout <<" back : " << myvector.back() << std::endl;
	myvector.front() -= myvector.back();
	std::cout << "myvector.front() is now " << myvector.front() << '\n';
}

void check_empty()
{
	ft::vector<int> myvector;
	int sum (0);
	
	for (int i=1;i<=10;i++) myvector.push_back(i);
	
	while (!myvector.empty())
	{
		sum += myvector.back();
		myvector.pop_back();
	}
	
	std::cout << "total: " << sum << '\n';
}

void check_clear()
{
	ft::vector<int> myvector(10, 5);
	print_all(myvector);
	myvector.clear();
	print_all(myvector);
}

void check_resize(){
	ft::vector <int> v;
	std::cout << YELLOW <<  "capacity: " << v.capacity() << std::endl << SHALLOW;
	std::cout << YELLOW << "size: " << v.size() << std::endl << SHALLOW;
	print_all(v);
	v.push_back(5);
	v.push_back(4);
	v.push_back(3);
	v.push_back(1);
	std::cout << YELLOW <<  "capacity: " << v.capacity() << std::endl << SHALLOW;
	std::cout << YELLOW << "size: " << v.size() << std::endl << SHALLOW;
	print_all(v);
	v.resize(10);
	std::cout << YELLOW <<  "capacity: " << v.capacity() << std::endl << SHALLOW;
	std::cout << YELLOW << "size: " << v.size() << std::endl << SHALLOW;
	print_all(v);
	v.resize(4);
	std::cout << YELLOW <<  "capacity: " << v.capacity() << std::endl << SHALLOW;
	std::cout << YELLOW << "size: " << v.size() << std::endl << SHALLOW;
	print_all(v);
	v.resize(0);
	std::cout << YELLOW <<  "capacity: " << v.capacity() << std::endl << SHALLOW;
	std::cout << YELLOW << "size: " << v.size() << std::endl << SHALLOW;
	print_all(v);
	v.resize(2);
	std::cout << YELLOW <<  "capacity: " << v.capacity() << std::endl << SHALLOW;
	std::cout << YELLOW << "size: " << v.size() << std::endl << SHALLOW;
	print_all(v);
}

void check_reserve()
{
	ft::vector<int>::size_type sz;
	
	ft::vector <int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i=0; i<100; ++i) {
		foo.push_back(i);
		if (sz!=foo.capacity()) {
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	ft::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);   // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i=0; i<100; ++i) {
		bar.push_back(i);
		if (sz!=bar.capacity()) {
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
}

void check_erase_rbegin()
{

	ft::vector <int> v;
	// set some values (from 1 to 10)
	print_all(v);
	for (int i = 1; i <= 10; i++)
		v.push_back(i);
	print_all(v);
	// v the 6th element
	ft::vector<int>::iterator ib = v.begin();
	ft::vector<int>::iterator ie = v.end() - 1;

	ft::vector<int>::reverse_iterator rb = v.rbegin();
	ft::vector<int>::reverse_iterator re = v.rend() - 1;
	
	std::cout << "it is iterator begin: " << *ib << std::endl;
	std::cout << "it is iterator end: " << *ie << std::endl;

	std::cout << "it is reverse iterator begin: " << *rb << std::endl;
	std::cout << "it is reverse iterator end: " << *re << std::endl;
	std::cout << "pointer: " << (*(v.erase (v.begin()+5))) << std::endl;
	print_all(v);
	//erase the first 3 elements:
	std::cout << "pointer: " << (*(v.erase (v.begin(),v.begin()+3))) << std::endl;
	print_all(v);
	std::cout << '\n';
}

void check_insert()
{

	ft::vector<int> myvector;
	for (int i=0; i<3; ++i)
	    myvector.push_back(i);
	ft::vector<int>::iterator it;
//		std::cout << "myvector ";
//		print_all(myvector);
//		it = myvector.begin();
//		myvector.insert ( it , 200 );
//		std::cout << "myvector ";
//		print_all(myvector);
//		it = myvector.begin();
//		myvector.insert ( it , 300 );
//		std::cout << "myvector ";
//		print_all(myvector);
//		it = myvector.begin();
//		myvector.insert (it,2,555);
//		std::cout << "myvector ";
//		print_all(myvector);
//		it = myvector.begin();
//		myvector.insert (it,2,500);
//		std::cout << "myvector ";
//		print_all(myvector);
////	"it" no longer valid, get a new one:
	it = myvector.begin();
	ft::vector<int> anothervector;
	for (int i=7; i<10; ++i)
	    anothervector.push_back(i);
	myvector.insert (it+2,anothervector.begin(),anothervector.end());
	std::cout << "anothervector ";
	print_all(anothervector);
	std::cout << "myvector ";
	print_all(myvector);
	it = myvector.begin();
	myvector.insert (it,anothervector.begin(),anothervector.end());
	std::cout << "myvector ";
	print_all(myvector);

	ft::vector <int> third;
	print_all(third);
	ft::vector<int>::iterator b = third.begin();
	third.insert(b, anothervector.begin(),anothervector.end());
	print_all(third);
	b = third.begin();
	third.insert(b, anothervector.begin(),anothervector.end());
	print_all(third);
}

void check_operator_assign()
{
	ft::vector<int> m;
	for (int i=0; i<10; ++i)
		m.push_back(i);
	print_all(m);
	ft::vector<int> other;
	other = m;
	print_all(other);
}

void check_assign()
{
	ft::vector<int> first;
	for (int i=0; i<10; ++i)
		first.push_back(i);
	ft::vector<int> second;
	std::cout << "first: ";
	print_all(first);
	std::cout << "second: ";
	print_all(second);
	std::cout << "capacity: " << first.capacity() <<  std::endl;
	std::cout << "size: " << first.size() << std::endl;
	first.assign (7,100);// 7 ints with a value of 100
	std::cout << "first:___ ";
	print_all(first);

	ft::vector<int>::iterator it;
	it=first.begin()+1;
	std::cout << *it << std::endl;
	std::cout << "first: ";
	print_all(first);

	second.assign (it,first.end()-1); // the 5 central values of first
	std::cout << "second: ___";
	print_all(second);

	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';

	ft::vector<int> my;
	for(int i = 0; i < 5; ++i)
	{
		my.push_back(i);
	}
	print_all(my);
	ft::vector<int>::iterator start= my.begin()+2;
	std::cout << *start;
	my.push_back(*start);
	print_all(my);
	print_all(my);

	ft::vector<int> hah;
	hah.assign(my.begin(), my.end());
	print_all(hah);
}

void check_erase_begin()
{
	ft::vector <int> v;
	// set some values (from 1 to 10)
	print_all(v);
	for (int i = 1; i <= 10; i++)
		v.push_back(i);
	print_all(v);
	// v the 6th element
	ft::vector<int>::iterator m = v.begin();
	std::cout << "it is iterator begin: " << *m << std::endl;
	std::cout << "pointer: " << (*(v.erase (v.begin()+5))) << std::endl;
	print_all(v);
	//	 erase the first 3 elements:
	std::cout << "pointer: " << (*(v.erase (v.begin(),v.begin()+3))) << std::endl;
	print_all(v);
	std::cout << '\n';
}

void check_iterators()
{
	ft::vector <int> m;
	m.push_back(5);
	ft::vector<int>::iterator it = m.begin();
	ft::vector<int>::const_iterator itc = m.end();
	itc = it;
	// it = itc;
}

void check_invalidations_of_iterators()
{
	ft::vector <int> m1;
	m1.push_back(5);
	m1.push_back(6);
	m1.push_back(7);

	ft::vector < int>::iterator it1 = m1.end();
	it1--;
	std::cout << RED << "it 1: " << &it1 << SHALLOW  << std::endl;
	m1.push_back(4);
	ft::vector < int>::iterator it2 = it1;
	std::cout << RED << "it 2: " << &it2 << SHALLOW  << std::endl;
	m1.push_back(5);
	ft::vector < int>::iterator it3 = it1;
	std::cout << RED << "it 3: " << &it3 << SHALLOW  << std::endl;
}

// template<class Os, class Co> Os& operator<<(Os& os, const Co& co) {
// 	os << "{";
// 	for (typename Co::const_iterator it = m.begin(); it != m.end(); ++it) 
// 	{ os << ' ' << i; }
// 	return os << " } ";
// }

template< class Os, typename K>
Os& operator<<(Os& os, ft::vector<K> const &m)
{
	os << "{";
	for (typename ft::vector <K>::const_iterator it = m.begin(); it != m.end(); ++it)
		{ os << ' ' << *it; }
	os << " } ";
	return os ;
}

void check_swap(){
	ft::vector<int> a1, a2;
	a1.push_back(1);
	a1.push_back(2);
	a1.push_back(3);
	a2.push_back(4);
	a2.push_back(5);

	ft::vector<int>::const_iterator it1 = std::next(a1.begin());
	ft::vector<int>::const_iterator it2 = std::next(a2.begin());
	
	int& ref1 = a1.front();
	int& ref2 = a2.front();
	
	std::cout << a1 <<  a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
	a1.swap(a2);
	std::cout <<  a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
	
	// Note that after swap the iterators and references stay associated with their
	// original elements, e.g. it1 that pointed to an element in 'a1' with value 2
	// still points to the same element, though this element was moved into 'a2'.
}

int main()
{
	std::cout << GREEN << MESSAGE << SHALLOW << std::endl;
	std::cout << RED << "VECTOR" << SHALLOW << std::endl;
	// check_push_back_pop_back_size_capacity();
	// check_operator_index_at();
	// check_front();
	// check_empty();
	// check_clear();
	// check_resize();	
	// check_reserve();
	// check_erase_begin();	
	// check_insert();
	// check_operator_assign();
	// check_erase_begin();
	check_swap();
	// check_iterators();

}
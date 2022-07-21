#include <iostream>
#include "Colors.hpp"
#include <fstream>
#include <deque>
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

int main() 
{
	std::cout << GREEN << MESSAGE << SHALLOW << std::endl;
	std::cout << RED << "STACK" << SHALLOW << std::endl;
	// std::stack<int> mystack;

	ft::stack<int, std::deque<int> > mystack;

	std::cout << mystack.empty() << std::endl;
	mystack.push(1);
	std::cout << mystack.top() << std::endl;
	mystack.pop();
	mystack.push(3);
	mystack.push(5);
	mystack.push(737);
	while (!mystack.empty()) 
	{
		std::cout << mystack.top() << std::endl; 
		mystack.pop(); 
	}
}

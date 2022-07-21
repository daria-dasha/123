#include <iostream>
#include "Colors.hpp"
#include <fstream>
// set 1 to use std::map header. set 0 to use ft::map header.
#if 0 //CREATE A REAL STL EXAMPLE
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
	ft::pair<int, int> my;
	std::cout <<  my.first << std::endl;
	std::cout <<  my.first << std::endl;
	
	
	ft::pair <std::string,int> planet, homeplanet;
	
	planet = ft::make_pair("Earth",6371);
	
	homeplanet = planet;
	
	std::cout << "Home planet: " << homeplanet.first << '\n';
	std::cout << "Planet size: " << homeplanet.second << '\n';
	return 0;
}


#pragma once
#include <iostream>
#include "Colors.hpp"
#include "pair.hpp"
#include "RemoveConst.hpp"
namespace ft
{
	template < class value >
	class Node
	{
	public:
		typedef Node < value >	Node_;
		typedef Node_ *			Node_pointer;

		Node_pointer			left;
		Node_pointer			right;
		Node_pointer			parent;
		value					_kv;
		bool					red;

	public:

		explicit Node (value key = value()): 
		left(0), right(0), parent(0), _kv(key), red(1)
		{
			// std::cout << "default" << std::endl;
		};
		explicit Node (Node * l, Node * r, Node * p, value key, bool isred): 
		left(l), right(r), parent(p), _kv(key), red(isred)
		{
			// std::cout << RED << "hello i am default constructor of Node!" <<  SHALLOW << std::endl;
		};

		Node( const Node <typename ft::remove_const< value >::type> & other ): left(other.left), right(other.right), parent(other.parent), _kv(other._kv), red(other.red)
		{
		};

		//copy
		Node &operator=(const Node  <typename ft::remove_const< value >::type> &other)
		{
			//	std::cout << RED <<  "hello i am assign = from iterator!" <<  SHALLOW << std::endl;
			if (this == &other)
				return *this;
			else
			{
				this->left = other.left;
				this->right = other.right;
				this->parent = other. parent;
				this->_kv = other._kv;
				this->red = other.red;
			}
			return *this;
		}

		//desctuctor
		virtual ~Node()
		{
			//std::cout << RED << "goodbuy iterator!" <<  SHALLOW << std::endl;
		};

	};
}








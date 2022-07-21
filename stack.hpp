#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>
//#include <vector>//temporarily
#include "vector.hpp"


namespace ft{
	template< class T, class Container = ft::vector<T> > class stack
	{
	public:
		//typedef определяет внутренний тип
		typedef Container			container_type;
		typedef T					value_type;
		typedef size_t				size_type;

	protected:
		container_type				c;
	public:

		// explicit запрещает автоматическое преобразование типа для
		// конструктора с одним аргументом (ошибка Сlass s; s= 40),
		// исключает инициализацию с автоматическим преобразованием типа при
		// присваивании (ошибка Stack s = 40) Работает только Stack s(40)

		explicit stack( const Container& cont = Container() ):c(cont)
		{

		};
		stack( const stack& other ):c(other.c)
		{

		};
		~stack()
		{
		};

		bool empty() const{
			// Test whether container is empty
			// Returns whether the stack is empty: i.e. whether its size is zero.
			// This member function effectively calls member empty of the underlying container object.
			return c.empty();
		};

		size_type size() const{
			// Return size
			// Returns the number of elements in the stack.
			// This member function effectively calls member size of the underlying container object.
			return(c.size());
		};

		value_type& top(){
			// Access next element
			// Returns a reference to the top element in the stack.
			// Since stacks are LIFO (last-in first-out) containers, the top element is the last element inserted into the stack.
			// This member function effectively calls member back of the underlying container object.
			return(c.back());
		};

		const value_type& top() const{
			return(c.back());
		};

		void push (const value_type& val){
			// Insert element
			// Inserts a new element at the top of the stack, above its current top element. The content of this new element is initialized to a copy of val.
			// This member function effectively calls the member function push_back of the underlying container object.
			c.push_back(val);
		};

		void pop(){
			// Remove top element
			// Removes the element on top of the stack, effectively reducing its size by one.
			// The element removed is the latest element inserted into the stack, whose value can be retrieved by calling member stack::top.
			// This calls the removed element's destructor.
			// This member function effectively calls the member function pop_back of the underlying container object.
			c.pop_back();
		};

		stack &	operator=( stack const & rhs ){
			if(c != rhs.c)
			{
				c = rhs.c;
				return (*this);
			}
		};

		template <class A, class Cont>
		friend bool operator== (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs);
		template <class A, class Cont>
		friend bool operator!= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs);
		template <class A, class Cont>
		friend bool operator<  (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs);
		template <class A, class Cont>
		friend bool operator<= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs);
		template <class A, class Cont>
		friend bool operator>  (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs);
		template <class A, class Cont>
		friend bool operator>= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs);

	};

	template <class A, class Cont>
	bool operator== (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
	{
		return(lhs.c == rhs.c);
	};
	template <class A, class Cont>
	bool operator!= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
	{
		return(lhs.c != rhs.c);
	};

	template <class A, class Cont>
	bool operator<  (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
	{
			return(lhs.c < rhs.c);
	};

	template <class A, class Cont>
	bool operator<= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
	{
		return(lhs.c <= rhs.c);
	};

	template <class A, class Cont>
	bool operator>  (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
	{
		return(lhs.c > rhs.c);
	};

	template <class A, class Cont>
	bool operator>= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
	{
		return(lhs.c >= rhs.c);
	};

}

#endif

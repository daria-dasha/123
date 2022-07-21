

#pragma once

namespace ft{
	template <class T>
	struct remove_const {
	public:
		typedef T type;
	};
	template <class T>
	struct remove_const <const T>{
	public:
		typedef T type;
	};
}


#pragma once

#include "LexicographicalCompare.hpp"
#include "IteratorsTraits.hpp"

namespace ft{

	template <bool condition, typename Type = void>
	struct EnableIf{};

	template <typename Type>
	struct EnableIf <true, Type>
	{
		typedef Type type;
	};


	template<class T, bool v>
	struct integral_constant {
		static const bool value = v;
		typedef T						value_type;
		typedef integral_constant		type;
		operator value_type() const {
			return value;}
		};

	template <class T>
	struct is_integral							: public ft::integral_constant<T, false> {};

	template <>
	struct is_integral<bool>					: public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<char>					: public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<signed char>				: public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<unsigned char>			: public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<char16_t>				: public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<char32_t>				: public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<wchar_t>					: public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<short>					: public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<unsigned short>			: public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<int>						: public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<unsigned int>			: public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<long>					: public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<unsigned long>			: public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<long long>				: public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<unsigned long long>		: public ft::integral_constant<bool, true> {};


	template <class T> void swap ( T& a, T& b )
	{
		T c(a); a=b; b=c;
	}

	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1!=last1) {
			if (!(*first1 == *first2))	 // or: if (!pred(*first1,*first2)), for version 2
				return false;
			++first1; ++first2;
		}
		return true;
	}


};

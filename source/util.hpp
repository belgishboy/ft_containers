#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include <iostream>
//#include <type_traits>
//#include <algorithm>
#include <utility>

namespace ft
{
	//Enable_if
	template <bool, class _Tp = void> 
	struct enable_if {};
	template <class _Tp> 
	struct enable_if<true, _Tp> {typedef _Tp type;};

	//Is_integral
	template <class _Tp>
	struct is_integral
	{
		typedef _Tp		value_type;
		const static bool _value = false;
		operator value_type() const {return _value;};
		value_type operator()() const {return _value;};
	};

	template <>
	struct is_integral<bool>
	{ const static bool _value = true; };
	template <>
	struct is_integral<char>
	{ const static bool _value = true; };
	template <>
	struct is_integral<signed char>
	{ const static bool _value = true; };
	template <>
	struct is_integral<unsigned char>
	{ const static bool _value = true; };
	template <>
	struct is_integral<char16_t>
	{ const static bool _value = true; };
	template <>
	struct is_integral<char32_t>
	{ const static bool _value = true; };
	template <>
	struct is_integral<wchar_t>
	{ const static bool _value = true; };
	template <>
	struct is_integral<short>
	{ const static bool _value = true; };
	template <>
	struct is_integral<unsigned short>
	{ const static bool _value = true; };
	template <>
	struct is_integral<int>
	{ const static bool _value = true; };
	template <>
	struct is_integral<unsigned int>
	{ const static bool _value = true; };
	template <>
	struct is_integral<long>
	{ const static bool _value = true; };
	template <>
	struct is_integral<unsigned long>
	{ const static bool _value = true; };
	template <>
	struct is_integral<long long>
	{ const static bool _value = true; };
	template <>
	struct is_integral<unsigned long long>
	{ const static bool _value = true; };


	//Equal
	template <class _InputIterator1, class _InputIterator2, class _BinaryPredicate>
	bool equal(_InputIterator1 first1, _InputIterator1 last1, _InputIterator2 first2, _BinaryPredicate pred)
	{
		for (; first1 != last1; ++first1, (void) ++first2)
			if (!pred(*first1, *first2))
				return false;
		return true;
	}

	template <class _InputIterator1, class _InputIterator2>
	bool equal(_InputIterator1 first1, _InputIterator1 last1, _InputIterator2 first2)
	{
		while (first1!=last1) {
			if (!(*first1 == *first2))
			return false;
			++first1; ++first2;
		}
		return true;
	}

	//Lexicographical_compare
	template <class _Compare, class _InputIterator1, class _InputIterator2>
	bool lexicographical_compare(_InputIterator1 first1, _InputIterator1 last1, _InputIterator2 first2, _InputIterator2 last2, _Compare comp)
	{
		for (; first2 != last2; ++first1, (void) ++first2)
		{
			if (first1 == last1 || comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return false;
	}

	template <class _InputIterator1, class _InputIterator2>
	bool lexicographical_compare(_InputIterator1 first1, _InputIterator1 last1, _InputIterator2 first2, _InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1) return false;
			else if (*first1<*first2) return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}

	//Pair
	template <class _T1, class _T2>
	struct pair
	{
		typedef _T1 first_type;
		typedef _T2 second_type;

		_T1 first;
		_T2 second;

		pair(): first(), second()
		{};

		pair(_T1 const& _first, _T2 const& _second): first(_first), second(_second)
		{};

		template <class _U1, class _U2>
		pair(const pair<_U1, _U2>& _pair): first(_pair.first), second(_pair.second)
		{};

		~pair()
		{};

		pair& operator=(pair const& _pair) {
			first = _pair.first;
			second = _pair.second;
			return *this;
		};

		template <class _T1, class _T2>
		bool operator==( const pair<_T1,_T2>& rhs)
		{
			return this->first == rhs.first && this->second == rhs.second;
		}

		template <class _T1, class _T2>
		bool operator!=( const pair<_T1,_T2>& rhs)
		{
			return !(this == rhs);
		}

		template <class _T1, class _T2>
		bool operator< ( const pair<_T1,_T2>& rhs)
		{
			return this->first < rhs.first || (!(rhs.first < this->first) && this->second < rhs.second);
		}

		template <class _T1, class _T2>
		bool operator> ( const pair<_T1,_T2>& rhs)
		{
			return rhs < this;
		}

		template <class _T1, class _T2>
		bool operator>=( const pair<_T1,_T2>& rhs)
		{
			return !(this < rhs);
		}

		template <class _T1, class _T2>
		bool operator<=( const pair<_T1,_T2>& rhs)
		{
			return !(rhs < this);
		}
	};

	template <class _T1, class _T2>
	pair<_T1,_T2> make_pair(_T1 first, _T2 second)
	{
		return pair<_T1, _T2>(first, second);
	}
}

#endif

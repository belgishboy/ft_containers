#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include <memory>
#include <cstddef>

#include "vector.hpp"
 
namespace ft
{
	template <typename _Tp, typename _Container = ft::vector<_Tp> >
	class stack
	{
	public:
		typedef _Container                               container_type;
		typedef typename container_type::value_type      value_type;
		typedef typename container_type::reference       reference;
		typedef typename container_type::const_reference const_reference;
		typedef typename container_type::size_type       size_type;

	protected:
		container_type c;

	public:

		// stack& operator=(const stack& __q)
		// {
		// 	c = __q.c;
		// 	return *this;
		// }

		explicit stack(const container_type& _c = container_type()):c(_c)
		{}

		bool empty() const
		{
			return c.empty();
		}
		size_type size() const
		{
			return c.size();
		}
		reference top()
		{
			return c.back();
		}
		const_reference top() const
		{
			return c.back();
		}

		void push(const value_type& _v)
		{
			c.push_back(_v);
		}

		void pop()
		{
			c.pop_back();
		}
	};

	template <class _Tp, class _Container>
	bool operator==(const stack<_Tp, _Container>& lhs, const stack<_Tp, _Container>& rhs)
	{
		return lhs.c == rhs.c;
	}

	template <class _Tp, class _Container>
	bool operator< (const stack<_Tp, _Container>& lhs, const stack<_Tp, _Container>& rhs)
	{
		return lhs.c < rhs.c;
	}

	template <class _Tp, class _Container>
	bool operator!=(const stack<_Tp, _Container>& lhs, const stack<_Tp, _Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class _Tp, class _Container>
	bool operator> (const stack<_Tp, _Container>& lhs, const stack<_Tp, _Container>& rhs)
	{
		return rhs < lhs;
	}

	template <class _Tp, class _Container>
	bool operator>=(const stack<_Tp, _Container>& lhs, const stack<_Tp, _Container>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class _Tp, class _Container>
	bool operator<=(const stack<_Tp, _Container>& lhs, const stack<_Tp, _Container>& rhs)
	{
		return !(rhs < lhs);
	}
}

#endif

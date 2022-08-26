#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include <memory>
//#include <vector>

#include "reverse_iterator.hpp"
#include "rand_iterator.hpp"

namespace ft
{

	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ft::rand_iterator<T>						iterator;
		typedef ft::rand_iterator<const T>					const_iterator;
		typedef typename ft::reverse_iterator<iterator>		reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename iterator::difference_type			difference_type;
		typedef size_t										size_type;

		//CONSTRUCTORS
		vector (const allocator_type& alloc = allocator_type());//default (1)
		vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());//fill (2)
		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()); //range (3)
		vector (const vector& x); //copy (4)

		//DESTRUCTOR
		~vector(void);

		//OPERATOR
		vector& operator=(const vector& rhs);

		//ITERATOR
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		//CAPACITY
		size_type size() const;
		size_type max_size() const;
		size_type capacity() const;
		bool empty() const;
		void reserve(size_type n);

		//ELEMENT ACCESS
		reference operator[](size_type n);
		const_reference operator[](size_type n) const;
		reference at(size_type n);
		const_reference at(size_type n) const;

		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		//MODIFIERS
		assign
		void push_back(const value_type& x);
		void pop_back();


		iterator insert(const_iterator position, const value_type& x);
		iterator insert(const_iterator position, size_type n, const value_type& x);
		template <class InputIterator>
		iterator insert(const_iterator position, InputIterator first, InputIterator last);

		iterator erase(const_iterator position);
		iterator erase(const_iterator first, const_iterator last);
		void swap(vector&);
		void clear();

		//ALLOCATOR
		allocator_type get_allocator() const;

	};

	//REGIONAL OPERATORS
	template <class T, class Allocator>
	bool operator==(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs);
	template <class T, class Allocator>
	bool operator< (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs);
	template <class T, class Allocator>
	bool operator!=(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs);
	template <class T, class Allocator>
	bool operator> (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs);
	template <class T, class Allocator>
	bool operator>=(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs);
	template <class T, class Allocator>
	bool operator<=(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs);
}

#endif 

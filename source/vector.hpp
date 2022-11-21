#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include <memory>
//#include <vector>
#include<iostream>

#include "reverse_iterator.hpp"
#include "rand_iterator.hpp"
#include "util.hpp"

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

		value_type *_v;
		size_type	_used_size;
		size_type	_alloc_size;
		allocator_type _alloc;

		//CONSTRUCTORS
		vector (const allocator_type& alloc = allocator_type())//default (1)
		{
			this->_alloc = alloc;
			this->_v = NULL;
			this->_used_size = 0;
			this->_alloc_size = 0;
		};
		vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())//fill (2)
		{
			this->_alloc = alloc;
			this->_v = this->_alloc.allocate(n);
			for (this->_used_size = 0; this->_used_size < n; this->_used_size ++)
				this->_alloc.construct(&this->_v[this->_used_size], val);
			this->_alloc_size = n;
		};
		template <class InputIterator>
		vector(	InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type() ) //range (3)
		{
			this->_alloc = alloc;
			this->_v = NULL;
			this->_used_size = 0;
			this->_alloc_size = 0;
			while(first != last)
			{
				this->push_back(*first);
				first++;
			}
		};
		vector (const vector& x) //copy (4)
		{
			this->_alloc = x._alloc;
			this->_v = NULL;
			this->_used_size = 0;
			this->_alloc_size = 0;
			(*this) = x;
		};

		//DESTRUCTOR
		~vector(void)
		{
			this->clear();
			this->_alloc.deallocate(this->_v, this->_alloc_size);
		};

		//OPERATOR
		vector& operator=(const vector& rhs)
		{
			if (!this->empty())
			{
				this->clear();
				this->_alloc.deallocate(this->_v, this->_alloc_size);
			}
			this->_alloc = rhs._alloc;
			this->_v = this->_alloc.allocate(rhs._alloc_size);
			for (this->_used_size = 0; this->_used_size < rhs._used_size; this->_used_size++)
				this->_alloc.construct(&this->_v[this->_used_size], rhs[this->_used_size]);
			this->_alloc_size = rhs._alloc_size;
			return (*this);
		};

		//ITERATOR
		iterator begin()
		{
			return (iterator(this->_v));
		};
		const_iterator begin() const
		{
			return (const_iterator(this->_v));
		};
		iterator end()
		{
			return(iterator(this->begin() + this->_used_size));
		};
		const_iterator end() const
		{
			return(const_iterator(this->begin() + this->_used_size));
		};
		reverse_iterator rbegin()
		{
			return(reverse_iterator(this->end()));
		};
		const_reverse_iterator rbegin() const
		{
			return(const_reverse_iterator(this->end()));
		};
		reverse_iterator rend()
		{
			return(reverse_iterator(this->begin()));
		};
		const_reverse_iterator rend() const
		{
			return(const_reverse_iterator(this->begin()));
		};

		//CAPACITY
		size_type size() const
		{
			return(this->_used_size);
		};
		size_type max_size() const
		{
			return(this->_alloc.max_size());
		};
		void resize (size_type n, value_type val = value_type())
		{
			if (n > this->_used_size)
			{
				this->reserve(n);
				while (this->_used_size < n)
					this->push_back(val);
			}
			else if (n < this->_used_size)
			{
				for (this->_used_size --; this->_used_size > n; this->_used_size --)
					this->_alloc.destroy(&this->_v[this->_used_size]);
			}
		};
		size_type capacity() const
		{
			return(this->_alloc_size);
		};
		bool empty() const
		{
			if (this->_used_size == 0)
				return (true);
			return (false);
		};
		void reserve(size_type n)
		{
			if (n < this->_alloc_size)
				return ;
			value_type *tmp = this->_alloc.allocate(n);
			for (size_type i = 0; i < this->_used_size; i++)
				this->_alloc.construct(tmp + i, this->_v[i]);
			for (size_type i = 0; i < this->_used_size; i ++)
				this->_alloc.destroy(&this->_v[i]);
			this->_alloc.deallocate(this->_v, this->_alloc_size);
			this->_v = tmp;
			this->_alloc_size = n;
			return;
		};

		//ELEMENT ACCESS
		reference operator[](size_type n)
		{
			return(this->_v[n]);
		};
		const_reference operator[](size_type n) const
		{
			return(this->_v[n]);
		};
		reference at(size_type n)
		{
			if (n >= this->_used_size)
				throw std::out_of_range("Out of Range\n");
			return (this->_v[n]);
		};
		const_reference at(size_type n) const
		{
			if (n >= this->_used_size)
				throw std::out_of_range("Out of Range\n");
			return (this->_v[n]);
		};

		reference front()
		{
			return (this->_v[0]);
		};
		const_reference front() const
		{
			return (this->_v[0]);
		};
		reference back()
		{
			if (this->empty())
				return (this->_v[0]);
			return (this->v[this->_used_size - 1]);
		};
		const_reference back() const
		{
			if (this->empty())
				return (this->_v[0]);
			return (this->v[this->_used_size - 1]);
		};

		//MODIFIERS
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last)
		{
				this->clear();
				while (first != last) 
				{
					this->push_back(*first);
					first++;
				}
		};
		void assign (size_type n, const value_type& val)
		{
			allocator_type tmp = this->_alloc;
			this->~vector();
			*this = vector(n, val, tmp);
		};
		void push_back(const value_type& x)
		{
			if (this->_used_size == this->_alloc_size)
				this->reserve(this->_alloc_size + 5);
			this->_alloc.construct(&this->_v[this->_used_size++], x);
		};
		void pop_back()
		{
			if (this->_used_size > 0)
				this->_alloc.destroy(&this->_v[this->_used_size --]);
		};


		iterator insert(iterator position, const value_type& x)
		{
			if (position == this->end())
			{
				this->push_back(x);
				return (this->end());
			}
			else if (position > this->end())
				throw std::out_of_range("Out of Range\n");
			else
			{
				size_type index = std::distance(this->begin(), position);
				this->reserve(this->size() + 1);
				this->push_back(x);
				std::copy_backward(this->begin() + index, this->end() - 1, this->end());
				this->_v[index] = x;
				return (&this->_v[index]);
			}
		};
		void insert(iterator position, size_type n, const value_type& x)
		{
			if (n < 1)
				return;
			if (position > this->end())
				throw std::out_of_range("Out of Range\n");
			else if (position == this->end())
			{
				for (size_type i = this->_used_size + n; this->_used_size < i;)
					this->push_back(x);
			}
			else
			{
				size_type i = n;
				{
					position = this->insert(position, x);
					position ++;
					i --;
				}
			}
		};
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
			this->clear();
			while (first != last) 
			{
				position = this->insert(position, *first);
				first++;
				position ++;
			}
		};

		iterator erase(iterator position)
		{
			return this->erase(position, position+1);
		}

		iterator erase(iterator first, iterator last)
		{
			vector<value_type> tmp = *this;
			size_type start_pos = 0;
			size_type end_pos = 0;
			iterator it = this->begin();
			while (it != first && start_pos < this->_used_size) {
				it++;
				start_pos++;
			}
			end_pos = start_pos;
			while (it != last && end_pos <= this->_used_size) {
				it++;
				end_pos++;
			}
			if (start_pos == this->_used_size || end_pos > this->_used_size) {
				throw std::runtime_error("Not a valid pointer to this vector");
			}
			for (size_type i = start_pos; i < end_pos; i++) {
				this->_alloc.destroy(this->_v + i);
			}
			this->_used_size = start_pos;
			for (size_type i = end_pos; i < tmp._used_size; i++) {
				this->push_back(tmp[i]);
			}
			return iterator(this->_v + start_pos);
		}
		void swap(vector& vec)
		{
			value_type	*tmp_v = vec._v;
			size_type	tmp_used_size = vec._used_size;
			size_type	tmp_alloc_size = vec._alloc_size;
			vec._v = this->_v;
			vec._used_size = this->_used_size;
			vec._alloc_size = this->_alloc_size;
			this->_v = tmp_v;
			this->_used_size = tmp_used_size;
			this->_alloc_size = tmp_alloc_size;
		};
		void clear()
		{
			if (this->empty())
				return ;
			for (this->_used_size --; this->_used_size > 0; this->_used_size --)
				this->_alloc.destroy(&this->_v[this->_used_size]);
			this->_alloc.destroy(&this->_v[this->_used_size]);
		};

		//ALLOCATOR
		allocator_type get_allocator() const
		{
			return (this->_alloc);
		};

	};

	//REGIONAL OPERATORS
	template <class T, class Allocator>
	ft::vector<T>operator==(const ft::vector<T,Allocator>& lhs, const ft::vector<T,Allocator>& rhs);
	template <class T, class Allocator>
	ft::vector<T>operator< (const ft::vector<T,Allocator>& lhs, const ft::vector<T,Allocator>& rhs);
	template <class T, class Allocator>
	ft::vector<T>operator!=(const ft::vector<T,Allocator>& lhs, const ft::vector<T,Allocator>& rhs);
	template <class T, class Allocator>
	ft::vector<T>operator> (const ft::vector<T,Allocator>& lhs, const ft::vector<T,Allocator>& rhs);
	template <class T, class Allocator>
	ft::vector<T>operator>=(const ft::vector<T,Allocator>& lhs, const ft::vector<T,Allocator>& rhs);
	template <class T, class Allocator>
	ft::vector<T>operator<=(const ft::vector<T,Allocator>& lhs, const ft::vector<T,Allocator>& rhs);
}

#endif 

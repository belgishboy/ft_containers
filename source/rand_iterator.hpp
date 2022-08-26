#ifndef FT_RAND_ITERATOR_HPP
 #define FT_RAND_ITERATOR_HPP

 #include <iterator>
 #include <cstddef>

 #include "iterator_traits.hpp"

 namespace ft
 {
	template <typename Iter>
	class rand_iterator :  std::iterator<std::random_access_iterator_tag, Iter>
	{
		protected:
			Iter *_now;
		public:
			typedef Iter																			iterator_type;
			typedef typename std::iterator<std::random_access_iterator_tag, Iter>::difference_type	difference_type;
			typedef typename std::iterator<std::random_access_iterator_tag, Iter>::pointer			pointer;
			typedef typename std::iterator<std::random_access_iterator_tag, Iter>::reference			reference;
			typedef typename std::iterator<std::random_access_iterator_tag, Iter>::iterator_category	iterator_category;

			//CONSTRUCTORS
			rand_iterator()
			{}
			rand_iterator(Iter *rhs) : _now(rhs)
			{}
			rand_iterator (const rand_iterator& rev_it) : _now(rev_it.address())
			{}

			//DESTRUCTOR
			~rand_iterator( void )
			{}

			//ASSIGNEMENT OPERATOR
			const rand_iterator& operator=(const rand_iterator& rev_it)
			{
				this->_now = rev_it.address();
				return (*this);
			}

			
			pointer address() const
			{
				return (this->_now);
			}

			//DEREFRENCE
			reference operator*() const
			{
				return (*(this->_now));
			}
			pointer operator->() const
			{
				return &(operator*());
			}
			reference operator[](difference_type n) const
			{
				return (*(this->_now + n));
			}

			//OPERATORS
			rand_iterator& operator++()
			{
				_now ++;
				return (*this);
			}
			rand_iterator  operator++(int)
			{
				rand_iterator tmp(*this);
				++(*this);
				return (tmp);
			}
			rand_iterator& operator--()
			{
				_now --;
				return (*this);
			}
			rand_iterator  operator--(int)
			{
				rand_iterator tmp(*this);
				--(*this);
				return (tmp);
			}
			rand_iterator  operator+ (difference_type n) const
			{
				return rand_iterator(_now + n);
			}
			rand_iterator& operator+=(difference_type n)
			{
				_now += n;
				return (*this);
			}
			rand_iterator  operator- (difference_type n) const
			{
				rand_iterator tmp(*this);
				tmp -= n;
				return (tmp);
			}
			rand_iterator& operator-=(difference_type n)
			{
				_now -= n;
				return (*this);
			}

	};

	template <class Iter>
	bool operator==(const rand_iterator<Iter>& lhs, const rand_iterator<Iter>& rhs)
	{
		return (lhs.address() == rhs.address());
	}
	template <class Iter>
	bool operator<(const rand_iterator<Iter>& lhs, const rand_iterator<Iter>& rhs)
	{
		return (lhs.address() < rhs.address());
	}
	template <class Iter>
	bool operator!=(const rand_iterator<Iter>& lhs, const rand_iterator<Iter>& rhs)
	{
		return !(lhs == rhs);
	}
	template <class Iter>
	bool operator>(const rand_iterator<Iter>& lhs, const rand_iterator<Iter>& rhs)
	{
		return (rhs < lhs);
	}
	template <class Iter>
	bool operator>=(const rand_iterator<Iter>& lhs, const rand_iterator<Iter>& rhs)
	{
		return !(lhs < rhs);
	}
	template <class Iter>
	bool operator<=(const rand_iterator<Iter>& lhs, const rand_iterator<Iter>& rhs)
	{
		return !(rhs < lhs);
	}

	//EXTERNAL OPPERATORS
	template <typename Iter>
	ft::rand_iterator<Iter>operator-(const typename ft::rand_iterator<Iter>::difference_type& lhs, const ft::rand_iterator<Iter>& rhs)
	{
		ft::rand_iterator<Iter> tmp(rhs);
		tmp -= lhs;
		return (tmp);
	}

	template <typename Iter>
	ft::rand_iterator<Iter>operator+(const typename ft::rand_iterator<Iter>::difference_type& lhs, const ft::rand_iterator<Iter>& rhs)
	{
		ft::rand_iterator<Iter> tmp(rhs);
		tmp += lhs;
		return (tmp);
	}
 }
#endif
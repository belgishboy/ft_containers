#ifndef FT_ITERATOR_TRAITS_HPP
 #define FT_ITERATOR_TRAITS_HPP

 #include <iterator>
 #include <cstddef>
 
 #include "iterator_traits.hpp"
 
 namespace ft
 {
	template <typename Iterator>
	class reverse_iterator
	{
		protected:
			Iterator _now;
		public:
			typedef Iterator												iterator_type;
			typedef typename ft::iterator_traits<Iterator>::value_type	 	value_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
			typedef typename ft::iterator_traits<Iterator>::difference_type	difference_type;
			typedef typename ft::iterator_traits<Iterator>::reference		reference;
			typedef typename ft::iterator_traits<Iterator>::pointer			pointer;

			//CONSTRUCTORS
			reverse_iterator();
			reverse_iterator(Iterator x);
			template <typename Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it);

			//DESTRUCTOR
			~reverse_iterator( void );

			//ASSIGNEMENT OPERATOR
			const reverse_iterator& operator=(const reverse_iterator& rev_it);

			//BASE
			Iterator base() const
			{
				return (this->_now);
			}

			//DEREFRENCE
			reference operator*() const
			{
				iterator_type tmp = _now;
				--tmp;
				return (*tmp);
			}
			pointer operator->() const
			{
				return &(operator*());
			}
			reference operator[](difference_type n) const
			{
				return *(*this + n);
			}

			//OPERATORS
			reverse_iterator& operator++()
			{
				--_now;
				return (*this);
			}
			reverse_iterator  operator++(int)
			{
				reverse_iterator tmp(*this);
				 --_now;
				return (tmp);
			}
			reverse_iterator& operator--()
			{
				++_now;
				return (*this);
			}
			reverse_iterator  operator--(int)
			{
				reverse_iterator tmp(*this);
				 ++_now;
				return (tmp);
			}
			reverse_iterator  operator+ (difference_type n) const
			{
				return reverse_iterator(_now - n);
			}
			reverse_iterator& operator+=(difference_type n)
			{
				_now -= n;
				return (*this);
			}
			reverse_iterator  operator- (difference_type n) const
			{
				return reverse_iterator(_now + n);
			}
			reverse_iterator& operator-=(difference_type n)
			{
				_now += n;
				return (*this);
			}
			
	};
/*
template <class Iterator1, class Iterator2>
constexpr bool                          // constexpr in C++17
operator==(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool                          // constexpr in C++17
operator<(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool                          // constexpr in C++17
operator!=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool                          // constexpr in C++17
operator>(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool                          // constexpr in C++17
operator>=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
constexpr bool                          // constexpr in C++17
operator<=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);
*/
	//EXTERNAL OPPERATORS
	template <typename Iterator>
	ft::reverse_iterator<Iterator>operator-(const typename ft::reverse_iterator<Iterator>::difference_type& lhs, const ft::reverse_iterator<Iterator>& rhs);

	template <typename Iterator>
	ft::reverse_iterator<Iterator>operator+(const typename ft::reverse_iterator<Iterator>::difference_type& lhs, const ft::reverse_iterator<Iterator>& rhs);
 }
#endif

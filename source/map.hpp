#pragma once

#include "tree.hpp"
#include "util.hpp"
#include "stack.hpp"
#include <functional>
#include <exception>
#include <stdexcept>

namespace ft
{

template <class Key, class T, class Compare = std::less<Key> , class Alloc = std::allocator<pair<const Key,T> > >
class map
{
public:

	typedef Key																			key_type;
	typedef T																			mapped_type;
	typedef pair<const key_type, mapped_type>											value_type;
	typedef const pair<const key_type, mapped_type>										const_value_type;
	typedef Compare																		key_compare;
	typedef typename Alloc::template rebind<tree_node<value_type> >::other				allocator_type;
	typedef value_type&																	reference;
	typedef const value_type&															const_reference;
	typedef value_type*																	pointer;
	typedef const value_type*															const_pointer;
	typedef ptrdiff_t																	difference_type;
	typedef size_t																		size_type;
	typedef ft::tree_<key_type, mapped_type, value_type, key_compare, allocator_type>		binarySearchTree;
	typedef typename binarySearchTree::nodePtr											nodePtr;
	typedef typename binarySearchTree::constNodePtr										constNodePtr;
	typedef typename ft::tree_Iterator<nodePtr, value_type>								iterator;
	typedef typename ft::tree_Iterator<constNodePtr, const_value_type>					const_iterator;
	typedef ft::reverse_iterator<iterator>												reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>										const_reverse_iterator;
	
private:
	binarySearchTree																	tree;
	Compare																				compare;
	allocator_type																		allocator;


public:

	class value_compare
		: std::binary_function<value_type, value_type, bool>
	{
		public:
			friend class map;

			bool operator() (const value_type& lhs, const value_type& rhs) const
			{
				return (comp(lhs.first, rhs.first));
			}

		protected:
			value_compare(key_compare c)
				: comp(c) {}

			key_compare comp;
	};

	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: tree(binarySearchTree()), compare(comp), allocator(alloc) { }

	template<typename InputIterator>
	map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: tree(binarySearchTree()), compare(comp), allocator(alloc)
	{
		InputIterator temp = first;
		for(;temp != last; ++temp)
			tree.insert(tree.root, *temp, tree.root->parent);
	}

	map (const map& x)
		:tree(binarySearchTree()), compare(x.compare), allocator(x.allocator)
	{
		tree.copyTree(x.tree.root, this->tree.root, x.tree.nil);
	}

	~map() { }

	map&	operator= (const map& rhs) {
		this->clear();
		tree.copyTree(rhs.tree.root, this->tree.root, rhs.tree.nil);
		compare	= rhs.compare;
		allocator	= rhs.allocator;
		return *this;
	}

	bool empty() const
	{
		return tree.size() == 0;
	}

	size_type size() const
	{
		return tree.size();
	}
	size_type max_size() const
	{
		return allocator.max_size();
	}

	mapped_type& operator[] (const key_type& k)
	{
		return (this->insert(ft::make_pair(k,mapped_type()))).first->second;
	}

	mapped_type& at(const key_type& k)
	{
		iterator element = this->find(k);
		if (element == end())
			throw std::out_of_range("map::at out of range");
		return (*element).second;
	}

	ft::pair<iterator, bool> insert (const value_type& val)
	{
		size_t prevTreeSize = tree.getTreeSize();
		iterator it = iterator(tree.insert(tree.root, val, tree.root->parent));
		if (tree.getTreeSize() == prevTreeSize)
			return (ft::make_pair<iterator, bool>(it, false));
		else
			return (ft::make_pair<iterator, bool>(it, true));
	}

	iterator insert (iterator position, const value_type& val)
	{
		(void)position;
		return iterator(tree.insert(tree.root, val, tree.root->parent));
	}

	template <class InputIterator>
	void insert (InputIterator first, InputIterator last)
	{
		(tree.insert(first, last));
	}

	void erase (iterator position)
	{
		if (size() == 0)
			return;
		tree.erase(position.treeNode);
	}

	size_type erase (const key_type& k)
	{
		iterator element = this->find(k);
		if (element != end())
		{
			tree.erase((this->find(k)).treeNode);
			return 1;
		}
		else return 0;
	}
	
	void erase (iterator first, iterator last)
	{
		iterator toDelete;
		while (first != last)
		{
			toDelete = first;
			first++;
			tree.erase(toDelete.treeNode);
		}
	}

	iterator find(const key_type& k)
	{
		return(tree.find(tree.root, k));
	}
	
	const_iterator find (const key_type& k) const
	{
		return(tree.find(tree.root, k));
	}

	size_type count (const key_type& k) const
	{
		return(tree.find(tree.root, k) != tree.end());
	}

	iterator lower_bound(const key_type& k)
	{
		return(tree.lower_bound(tree.root, k));
	}
	
	const_iterator lower_bound (const key_type& k) const
	{
		return(tree.lower_bound(tree.root, k));
	}

	iterator upper_bound(const key_type& k)
	{
		return(tree.upper_bound(tree.root, k));
	}
	
	const_iterator upper_bound (const key_type& k) const
	{
		return(tree.upper_bound(tree.root, k));
	}

	ft::pair<iterator,iterator> equal_range(const key_type& k)
	{
		return(ft::make_pair(tree.lower_bound(tree.root, k),tree.upper_bound(tree.root, k)));
	}
	
	ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
	{
		return(ft::make_pair(tree.lower_bound(tree.root, k), tree.upper_bound(tree.root, k)));
	}

	void clear()
	{
		tree.clear(tree.root);
	}

	void swap (map& x)
	{
		tree.swap(x.tree);
	}

	key_compare key_comp() const
	{
		return compare;
	}
	
	value_compare value_comp() const
	{
		return value_compare(compare);
	}

	allocator_type get_allocator() const {return allocator_type(tree.allocator);}

	iterator begin() throw()
	{
		return iterator(tree.begin());
	}

	const_iterator begin() const throw()
	{
		return const_iterator(tree.begin());
	}

	iterator end() throw()
	{
		return iterator(tree.end());
	}

	const_iterator end() const throw()
	{
		return const_iterator(tree.end());
	}

	reverse_iterator rbegin() throw()
	{
		return (tree.rbegin());
	}

	const_reverse_iterator rbegin() const throw()
	{
		return (tree.rbegin());
	}

	reverse_iterator rend() throw()
	{
		return (tree.rend());
	}

	const_reverse_iterator rend() const throw()
	{
		return (tree.rend());
	}

	template<typename _K1, typename _T1, typename _C1, typename _A1>
	friend bool operator==(const map<_K1, _T1, _C1, _A1>&, const map<_K1, _T1, _C1, _A1>&);

	template<typename _K1, typename _T1, typename _C1, typename _A1>
	friend bool operator<(const map<_K1, _T1, _C1, _A1>&, const map<_K1, _T1, _C1, _A1>&);

};

	template<typename _K1, typename _T1, typename _C1, typename _A1>
	bool operator== (const map<_K1,_T1,_C1,_A1> & lhs, const map<_K1,_T1,_C1,_A1> & rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<typename _K1, typename _T1, typename _C1, typename _A1>
	bool operator< (const map<_K1,_T1,_C1,_A1> & lhs, const map<_K1,_T1,_C1,_A1> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<typename _Key, typename _Tp, typename _Compare, typename Allocator>
	inline bool operator!=(const map<_Key, _Tp, _Compare, Allocator>& lhs, const map<_Key, _Tp, _Compare, Allocator>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename _Key, typename _Tp, typename _Compare, typename Allocator>
	inline bool operator>(const map<_Key, _Tp, _Compare, Allocator>& lhs, const map<_Key, _Tp, _Compare, Allocator>& rhs)
	{
		return rhs < lhs;
	}

	template<typename _Key, typename _Tp, typename _Compare, typename Allocator>
	inline bool operator<=(const map<_Key, _Tp, _Compare, Allocator>& lhs, const map<_Key, _Tp, _Compare, Allocator>& rhs)
	{
		return !(rhs < lhs);
	}

	template<typename _Key, typename _Tp, typename _Compare, typename Allocator>
	inline bool operator>=(const map<_Key, _Tp, _Compare, Allocator>& lhs, const map<_Key, _Tp, _Compare, Allocator>& rhs)
	{
		return !(lhs < rhs);
	}

}

namespace ft
{
	template<class Key, class T, class Compare, class Alloc >
	inline void swap(ft::map<Key, T, Compare, Alloc>& a, ft::map<Key, T, Compare, Alloc>& b)
	{
		a.swap(b);
	};
}
#pragma once

#include <memory>
#include <exception>
#include <limits>
#include "reverse_iterator.hpp"
#include "rand_iterator.hpp"
#include "util.hpp"
#include <iostream>
#include <stdexcept>

namespace ft
{

	template<typename value_type>
	struct tree_node
	{
		tree_node*		parent;
		value_type		_value;
		tree_node*		left;
		tree_node*		right;

		tree_node() 
			:parent(NULL), left(NULL), right(NULL) {}
		
		tree_node (value_type val) 
			:parent(NULL), _value(val), left(NULL), right(NULL) {}
		
		~tree_node() {}
	};

		template<typename nodePtr>
		nodePtr nilNode(nodePtr node)
		{
			while (node->parent != NULL)
				node = node->parent;
			return node;
		}

		template<typename nodePtr>
		nodePtr min(nodePtr node)
		{
			if (node != nilNode(node))
			{
				while (node->left != nilNode(node))
					node = node->left;
			}
			return node;
		}

		template<typename nodePtr>
		nodePtr max(nodePtr node)
		{
			if (node != nilNode(node))
			{
				while (node->right != nilNode(node))
					node = node->right;
			}
			return node;
		} 

		template<typename nodePtr>
		nodePtr rootNode(nodePtr node)
		{
			if (node->parent == NULL)
			{	
				if (node->left != NULL)
					node = node->left;
				else if (node->right != NULL)
					node = node->right;
			}
			while (node->parent != nilNode(node))
				node = node->parent;
			return node;
		}

		template<typename nodePtr>
		nodePtr predecessor(nodePtr node)
		{
			nodePtr rootPtr = rootNode(node);
			nodePtr nilPtr = nilNode(node);
			if (node == nilPtr)
				return (max(rootPtr));
			else if (node == min(rootPtr))
				return nilPtr;
			else if (node->left != nilPtr)
				return max(node->left);
			else
			{
				nodePtr predecessorNode = node->parent;
				while (predecessorNode != nilPtr && node == predecessorNode->left)
				{
					node = predecessorNode;
					predecessorNode = predecessorNode->parent;
				}
				return predecessorNode;
			}
		}

		template<typename nodePtr>
		nodePtr successor(nodePtr node)
		{
			nodePtr root = rootNode(node);
			nodePtr nil = nilNode(node);
			if (!node)
				return (min(root));
			else if (node == nil)
				return min(root);
			else if (node == max(root))
				return nil;
			else if (node->right != nil)
				return min(node->right);
			else
			{
				nodePtr successorNode = node->parent;
				while (successorNode != nil && node == successorNode->right)
				{
					node = successorNode;
					successorNode = successorNode->parent;
				}
				return successorNode;
			}
		}

	template<typename nP, typename v_t>
	struct tree_Iterator
	{
		typedef nP										nodePointer;
		typedef v_t										value_type;
		typedef value_type&								reference;
		typedef const value_type&						constReference;
		typedef value_type*								pointer;
		typedef std::bidirectional_iterator_tag			iterator_category;
		typedef ptrdiff_t								difference_type;
		typedef tree_Iterator<nodePointer, value_type>	tree_It;

		tree_Iterator() throw()
			: tree_Node() { }

		explicit tree_Iterator(nodePointer obj) throw()
			: tree_Node(obj) { }

		template<typename Iter, typename val_type>
		tree_Iterator(const tree_Iterator<Iter, val_type>& iter) throw()
			: tree_Node(iter.base())
		{}

		const nodePointer base() const throw()
		{
			return tree_Node;
		}

		reference operator*() throw()
		{
			return this->tree_Node->_value;
		}

		constReference operator*() const throw()
		{
			return this->tree_Node->_value;
		}

		pointer operator->() throw()
		{
			return &(this->tree_Node->_value);
		}

		pointer operator->() const throw()
		{
			return &(this->tree_Node->_value);
		}

		tree_It& operator++() throw()
		{
			this->tree_Node = successor(tree_Node);
			return *this;
		}

		tree_It operator++(int) throw()
		{
			tree_It temp = *this;
			this->tree_Node = successor(tree_Node);
			return temp;
		}

		tree_It& operator--() throw()
		{
			tree_Node = predecessor(tree_Node);
			return *this;
		}

		tree_It operator--(int) throw()
		{
			tree_It temp = *this;
			tree_Node = predecessor(tree_Node);
			return temp;
		}

		bool operator==(const tree_It& rhs) const throw()
		{
			return tree_Node == rhs.tree_Node;
		}

		bool operator!=(const tree_It& rhs) const throw()
		{
			return tree_Node != rhs.tree_Node;
		}

		nodePointer tree_Node;
	};


	template<class kT, class mapped_type, class value_type, class key_compare, class Allocator = std::allocator<tree_node<value_type> > >
	class tree_
	{
	public:
		typedef kT													key_type;
		typedef typename Allocator::template rebind<tree_node<value_type> >::other 	nodeAllocactor;
		typedef struct tree_node<value_type>											node;
		typedef node*																	nodePtr;
		typedef const node*																constNodePtr;
		typedef typename ft::tree_Iterator<nodePtr, value_type>							nodeIterator;
		typedef const typename ft::tree_Iterator<constNodePtr, const value_type>			nodeConstIterator;
		typedef ft::reverse_iterator<nodeIterator>		 								reverse_iterator;
		typedef ft::reverse_iterator<nodeConstIterator> 								const_reverse_iterator;
	private:
		size_t																			treeSize;
		nodeAllocactor																	allocator;
		key_compare																		comp;
	public:
		nodePtr																			nil;
		nodePtr																			root;


	nodePtr newNode(value_type val, nodePtr parent = NULL)
	{
		nodePtr newNode = allocator.allocate(1);
		allocator.construct(newNode, val);
		if (!parent)
		{
			newNode->parent = NULL;
			newNode->left = NULL;
			newNode->right = NULL;
		}
		else
		{
			newNode->parent = parent;
			newNode->left = nil;
			newNode->right = nil;
		}
		return newNode;
	}


	public:
		tree_(nodeAllocactor alloc = nodeAllocactor())
			: treeSize(0), allocator(alloc), nil(newNode(value_type())), root(this->nil)
		{}


		~tree_()
		{
			clear(root);
			allocator.destroy(nil);
			allocator.deallocate(nil, 1);
		}

	public:
		void clear(nodePtr node)
		{
			if (node != nil) {
				clear(node->left);
				clear(node->right);
				deleteNode(node);
			}
		}

		void deleteNode(nodePtr node)
		{
			if (node->parent != nil)
			{
				if (node == node->parent->left)
					node->parent->left = nil;
				else if (node == node->parent->right)
					node->parent->right = nil;
			}
			else
				root = nil;
			allocator.destroy(node);
			allocator.deallocate(node, 1);
			treeSize--;
		}

		nodePtr getRoot()
		{
			return(this->root);
		}

		size_t getTreeSize()
		{
			return(this->treeSize);
		}

		nodePtr insert(nodePtr node, value_type val, nodePtr parent)
		{
			static nodePtr insertedNode = NULL;
			static int depth = 0;
			++depth;
			if (node == nil)
			{
				++treeSize;
				if (root == nil)
				{
					insertedNode = newNode(val, nil);
					root = insertedNode;
					nil->left = root;
					nil->right = root;
					--depth;
					return (root);
				}
				insertedNode = newNode(val, parent);
				if (comp(insertedNode->_value.first, nil->left->_value.first))
					nil->left = insertedNode;
				else if (comp(nil->right->_value.first, insertedNode->_value.first))
					nil->right = insertedNode;
				--depth;
				return (insertedNode);
			}
			else
			{
				if (val.first == node->_value.first)
					insertedNode = node;
				else if (comp(val.first, node->_value.first))
					node->left = insert(node->left, val, node);
				else if (comp(node->_value.first, val.first))
					node->right = insert(node->right, val, node);
			}
			--depth;
			if (depth == 0)
				return insertedNode;
			return node;
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			for ( ; first != last; ++first)
				insert(this->root, *first, this->root->parent);
		}

		void erase (nodePtr position)
		{
			if (position == nil)
				return;
			if (position->left != nil && position->right != nil)
			{
				nodePtr minOfNode = min(position->right);
				if (position != root)
				{
					if (position == position->parent->right)
						position->parent->right = position->right;
					else if (position == position->parent->left)
						position->parent->left = position->right;
					position->right->parent= position->parent;
				}
				else
				{
					position->right->parent = nil;
					root = position->right;
				}
				position->left->parent = minOfNode;
				minOfNode->left = position->left;
			}
			else if (position->left == nil && position->right == nil)
			{
				if (position == root)
					root = nil;
				if (position != root && position == position->parent->left)
					position->parent->left = nil;
				else if (position != root && position == position->parent->right)
					position->parent->right = nil;
			}
			else
			{
				nodePtr child = (position->left == nil ? position->right : position->left);
				if (position == root)
				{
					child->parent = nil;
					root = child;
				}
				else if (position == position->parent->left)
				{
					position->parent->left = child;
					child->parent = position->parent;
				}
				else if (position == position->parent->right)
				{
					position->parent->right = child;
					child->parent = position->parent;
				}
			}
			if (position == nil->right)
				position->left != nil ? nil->right = position->left : nil->left = position->parent;
			if (position == nil->left)
				position->right != nil ? nil->left = position->right : nil->left = position->parent;
			allocator.destroy(position);
			allocator.deallocate(position, 1);
			treeSize--;
		}

		size_t size() const
		{
			return (this->treeSize);
		}

		bool empty() const
		{
			return (this->root == nil);
		}

		nodeIterator begin() throw()
		{
			return nodeIterator(min(this->root));
		}

		nodeConstIterator begin() const throw()
		{
			return nodeConstIterator(min(this->root));
		}

		nodeIterator end() throw()
		{
			return nodeIterator(this->nil);
		}

		nodeConstIterator end() const throw()
		{
			return nodeConstIterator(this->nil);
		}

		reverse_iterator rbegin() throw()
		{
			return (reverse_iterator(nodeIterator(nil)));
		}

		const_reverse_iterator rbegin() const throw()
		{
			return (const_reverse_iterator(nodeConstIterator(max(this->root))));
		}

		reverse_iterator rend() throw()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const throw()
		{
			return const_reverse_iterator(begin());
		}

		nodeIterator find (nodePtr node, const key_type& k)
		{
			if (k == node->_value.first || node == nil)
				return nodeIterator(node);
			if (comp(k,node->_value.first))
				return nodeIterator(find(node->left, k));
			else
				return nodeIterator(find(node->right, k));
		}

		nodeConstIterator find (const nodePtr node, const key_type& k) const
		{
			if (k == node->_value.first || node == nil)
				return nodeConstIterator(node);
			if (comp(k,node->_value.first))
				return nodeConstIterator(find(node->left, k));
			else
				return nodeConstIterator(find(node->right, k));
		}

		nodeIterator lower_bound(nodePtr node, const key_type& k)
		{
			nodePtr x = node;
			nodePtr y = min(root);
			while (x != nil)
			{
				if (k == x->_value.first)
					return nodeIterator(x);
				else if (comp(k, x->_value.first))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			if (x == nil && !(comp(k, y->_value.first)))
				return nodeIterator(x);
			else
				return nodeIterator(y);
		}
		
		nodeConstIterator lower_bound (const nodePtr node, const key_type& k) const
		{
			nodePtr x = node;
			nodePtr y = min(root);
			while (x != nil)
			{
				if (k == x->_value.first)
					return nodeConstIterator(x);
				else if (comp(k, x->_value.first))
				{
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			}
			if (x == nil && !(comp(k, y->_value.first)))
				return nodeConstIterator(x);
			else
				return nodeConstIterator(y);
		}

	nodeIterator upper_bound(nodePtr node, const key_type& k)
		{
			if (comp(k, nil->left->_value.first))
				return nodeIterator(nil->left);
			else if (!comp(k, nil->right->_value.first))
				return nodeIterator(nil);
			while (!(node->left == nil && node->right == nil))
			{
				if (node->_value.first == k)
					return ++nodeIterator(node);
				if (node->left != nil && comp(k, node->_value.first))
					node = node->left;
				else if (node->right != nil && !comp(k, node->right->_value.first))
					node = node->right;
				else
					break;
			}
			return ++nodeIterator(node);
			
		}
		
		nodeConstIterator upper_bound (const nodePtr node, const key_type& k) const
		{
			nodePtr returnNode = node;
			if (comp(k, nil->left->_value.first))
				return nodeConstIterator(nil->left);
			else if (!comp(k, nil->right->_value.first))
				return nodeConstIterator(nil);
			while (!(returnNode->left == nil && returnNode->right == nil))
			{
				if (returnNode->_value.first == k)
					return nodeConstIterator(++nodeIterator(returnNode));
				if (returnNode->left != nil && comp(k, returnNode->_value.first))
					returnNode = returnNode->left;
				else if (returnNode->right != nil && !comp(k, returnNode->right->_value.first))
					returnNode = returnNode->right;
				else
					break;
			}
			return nodeConstIterator(++nodeIterator(returnNode));
		}

		void swap(tree_& x)
		{
			std::swap(this->root, x.root);
			std::swap(this->treeSize, x.treeSize);
			std::swap(this->nil, x.nil);
			std::swap(this->comp, x.comp);
			std::swap(this->allocator, x.allocator);
		}

		void copyTree(nodePtr nodeFrom, nodePtr nodeTo, nodePtr nilFrom)
		{
			if (nodeFrom == nilFrom)
				return;
			insert(nodeTo, nodeFrom->_value, nodeTo->parent);
			copyTree(nodeFrom->left, nodeTo->left, nilFrom);
			copyTree(nodeFrom->right, nodeTo->right, nilFrom);
		}
	};
}
#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
		//Helper functions for Insert
    int height(AVLNode<Key, Value>* node) const;
    void value_of_Balance(AVLNode<Key, Value>* node) const;
    AVLNode<Key, Value>* fixRotation(AVLNode<Key, Value>* node, bool isLeftRotation);
    AVLNode<Key, Value>* make_Insert_Balance(AVLNode<Key, Value>* node);
    AVLNode<Key, Value>* insert_helper(AVLNode<Key, Value>* node, const std::pair<const Key, Value> &item);
		//Helper functions for Remove
		AVLNode<Key, Value>* predecessor(AVLNode<Key, Value>* node);
		void make_Remove_Balance(AVLNode<Key, Value>* node, int diff);
		void remove_helper(AVLNode<Key, Value>* node, const Key& key);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    // TODO
    this->root_ = insert_helper(static_cast<AVLNode<Key, Value>*>(this->root_), new_item);
}
/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
	// TODO
	remove_helper(static_cast<AVLNode<Key, Value>*>(this->root_), key); 
}

//height
template<typename Key, typename Value>
int AVLTree<Key, Value>::height(AVLNode<Key, Value>* node) const
{
    if(node == nullptr) return 0;
    int Lheight = height(node->getLeft());
    int Rheight = height(node->getRight());
    if(Lheight > Rheight) return (1 + Lheight);
    else return (1 + Rheight);
}
//value_of_Balance
template<typename Key, typename Value>
void AVLTree<Key, Value>::value_of_Balance(AVLNode<Key, Value>* node) const
{
    if(node == nullptr) return; 
		else{
        int Lheight = height(node->getLeft());
        int Rheight = height(node->getRight());
        int balanceVal = Lheight - Rheight;
        node->setBalance(balanceVal);
    }
}
//fixRotation
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::fixRotation(AVLNode<Key, Value>* node, bool isLeftRotation){
	if(isLeftRotation == true){
		AVLNode<Key, Value>* p = node->getRight();
		AVLNode<Key, Value>* g = p->getLeft();
		p->setLeft(node);
		node->setRight(g);
		p->setParent(node->getParent());
		node->setParent(p);
		if(g) g->setParent(node);
		if(node == this->root_) this->root_ = p;
		value_of_Balance(p); //parent first
		value_of_Balance(node);
		return p;
	}
	AVLNode<Key, Value>* n = node->getLeft();
	AVLNode<Key, Value>* g = n->getRight();
	n->setRight(node);
	node->setLeft(g);
	n->setParent(node->getParent());
	node->setParent(n);
	if(g) g->setParent(node);
	if(node == this->root_) this->root_ = n;
	value_of_Balance(node);
	value_of_Balance(n);
	return n;
}
//make the node to balanced node
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::make_Insert_Balance(AVLNode<Key, Value>* node)
{
	if(node == nullptr) return nullptr;
	value_of_Balance(node);
	//left
	if(node->getBalance() > 1) { 
		if((node->getLeft()->getBalance()) >= 0) return fixRotation(node, false);
		else if((node->getLeft()->getBalance()) < 0){
				node->setLeft(fixRotation(node->getLeft(), true));
				return fixRotation(node, false);
		}
	}
		//right
	if(node->getBalance() < -1){
		if((node->getRight()->getBalance()) <= 0) return fixRotation(node, true); 
		else if((node->getRight()->getBalance()) > 0){
			node->setRight(fixRotation(node->getRight(), false));
			return fixRotation(node, true);
		}
	}
	return node;
}
//insert_helper
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::insert_helper(AVLNode<Key, Value>* node, const std::pair<const Key, Value>& item)
{
	value_of_Balance(node);
	if(node == nullptr) return new AVLNode<Key, Value>(item.first, item.second, nullptr);
	if(item.first == node->getKey()) node->setValue(item.second);
	else if(item.first > node->getKey()){
			AVLNode<Key, Value>* Rchild = insert_helper(node->getRight(), item);
			node->setRight(Rchild);
			Rchild->setParent(node);
	}
	else if(item.first < node->getKey()){
			AVLNode<Key, Value>* Lchild = insert_helper(node->getLeft(), item);
			node->setLeft(Lchild);
			Lchild->setParent(node);
	}
	return make_Insert_Balance(node);
}
//---------------------------------------------------------------------------------------------
//Definitions of Remove Helper function
//predecessor
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::predecessor(AVLNode<Key, Value>* node){
    return static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::predecessor(node));
}
//make Balanced tree after removal
template<class Key, class Value>
void AVLTree<Key, Value>::make_Remove_Balance(AVLNode<Key, Value>* node, int diff){
	if(node == nullptr) return;
	int valDiff = 0;
	AVLNode<Key, Value>* p = node->getParent();
	if(p != nullptr){
		valDiff = -1;
		if(node == p->getLeft()){
			valDiff = 1;
		}
	}
	node->setBalance(node->getBalance() + diff);
	AVLNode<Key, Value>* makeBalanceNode = make_Insert_Balance(node);
	if(p != nullptr && node == p->getLeft()) p->setLeft(makeBalanceNode);	 
	else if(p != nullptr && node != p->getLeft()) p->setRight(makeBalanceNode);
	if(p != nullptr){ 
		if(valDiff != 0){
			make_Remove_Balance(p, valDiff);
		}
	}
}
//Helper function for remove definition
template<class Key, class Value>
void AVLTree<Key, Value>::remove_helper(AVLNode<Key, Value>* node, const Key& key){
	if(node == nullptr) return;
	if(node->getKey() == key){
		int valDiff = 0;
		AVLNode<Key, Value>* p = node->getParent();
		AVLNode<Key, Value>* c = nullptr;

		if((node->getLeft() != nullptr) && (node->getRight() != nullptr)){
			AVLNode<Key, Value>* pred = predecessor(node);
			if(pred == nullptr) return;
			nodeSwap(node, pred);
		}

		p = node->getParent();
		if((node->getLeft() == nullptr) && (node->getRight() == nullptr)){
			if(node == this->root_) this->root_ = nullptr;
			else if(node == node->getParent()->getLeft()){
				valDiff = 1;
				node->getParent()->setLeft(nullptr);
			}
			else{
				valDiff = -1;
				node->getParent()->setRight(nullptr);
			}
			delete node;
		}
		else if(node->getLeft() == nullptr || node->getRight() == nullptr){
			if(node->getLeft() == nullptr) c = node->getRight();
			else if(node->getRight() == nullptr) c = node->getLeft();

			if(node == this->root_){
				this->root_ = c;
				if(this->root_ != nullptr) this->root_->setParent(nullptr);
			} 
			else if(node == p->getLeft()){
				valDiff = 1;
				p->setLeft(c);
			}
			else{
				valDiff = -1;
				p->setRight(c);
			}
			if(c != nullptr) c->setParent(node->getParent());
			delete node;
		}
		make_Remove_Balance(p, valDiff);
	}
	else if(node->getKey() > key){
		remove_helper(node->getLeft(), key);
	}
	else if(node->getKey() < key){
		remove_helper(node->getRight(), key);
	}  
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif

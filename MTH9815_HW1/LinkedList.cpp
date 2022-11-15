//
//  LinkedList.cpp
//  MTH9815_HW1
//
//  Created by 王明森 on 11/9/22.
//

#ifndef LinkedList_cpp
#define LinkedList_cpp

#include "LinkedList.hpp"
#include <stdexcept>

// NODE
template <typename T>
Node<T>::Node(const T& val, Node<T>* nxt) : value(val), next(nxt) {}

// LIST ITERATOR
// Constructors and assignment
template <typename T>
ListIterator<T>::ListIterator(Node<T>* node) : node_(node) {}

template <typename T>
ListIterator<T>::ListIterator(const ListIterator<T>& iter) : node_(iter.node_){}

template <typename T>
ListIterator<T>& ListIterator<T>::operator = (const Node<T>* node) {
    node_ = node;
    return *this;
}

template <typename T>
ListIterator<T>& ListIterator<T>::operator = (const ListIterator<T>& iter) {
    
    if (this != &iter) {
        node_ = iter.node_;
    }
    
    return *this;
}

// Advance (prefix and postfix)
template <typename T>
ListIterator<T>& ListIterator<T>::operator ++ () {
    if (node_) {
        node_ = node_->next;
    }
    
    return *this;
}

template <typename T>
ListIterator<T>& ListIterator<T>::operator ++ (int) {
    ListIterator iter(*this);
    ++(*this);
    return *this;
}

// Compare
template <typename T>
bool ListIterator<T>::operator == (const ListIterator<T>& iter) const {
    return node_ == iter.node_;
}

template <typename T>
bool ListIterator<T>::operator != (const ListIterator<T>& iter) const {
    return node_ != iter.node_;
}

// Compare
template <typename T>
bool ListIterator<T>::operator == (Node<T>* node) const {
    return node_ == node;
}

template <typename T>
bool ListIterator<T>::operator != (Node<T>* node) const {
    return node_ != node;
}

// Dereference
template <typename T>
T& ListIterator<T>::operator * () const {
    return node_->value;
}

// Return whether there is another element to return in this iterator
template <typename T>
bool ListIterator<T>::HasNext() const {
    return node_->next != nullptr;
}

// Advance self and return the next element in this iterator
template <typename T>
T& ListIterator<T>::Next() {
    node_ = node_->next;
    return node_->value;
}

// Construct an empty linked list
template <typename T>
LinkedList<T>::LinkedList() : size_(0) {
    root_ = new Node<T>(T());
    leaf_ = root_;
}

// Add the specified element at the end of the list
template <typename T>
void LinkedList<T>::Add(const T& value) {
    // Create one more node at the end
    leaf_->next = new Node<T>(value);
    
    // The end node is shifted forward
    leaf_ = leaf_->next;
    
    // Increment size
    size_++;
}

// Add the specified element at the specified index
template <typename T>
void LinkedList<T>::Insert(const T& value, int index) {
    
    // Index is allowed to vary in [0, size].
    // The inserted element will be at position "index" after insertion
    
    if (index < 0 || index > size_) {
        throw std::out_of_range("Index out of range.");
    }
    
    // Place pointer just before the indexed node
    Node<T>* just_before(root_);
    for (int i = 0; i < index; i++) {
        just_before = just_before->next;
    }
    
    // And find the iterator just after the insert position
    Node<T>* just_after(just_before->next);
    
    // Build new node and reconnect
    just_before->next = new Node<T>(value, just_after);
    
    // Update leaf if insert at the end
    if (index == size_) {
        leaf_ = leaf_->next;
    }
    
    size_++;
}

// Get the element at the specified index
template <typename T>
T& LinkedList<T>::Get(int index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range.");
    }
    
    Node<T>* node(root_->next);
    
    while (index--) {
        node = node->next;
    }
    
    return node->value;
}

// Retrieve the index of the specified element (-1 if it does not exist in the list
template <typename T>
int LinkedList<T>::IndexOf(const T& value) const {
    
    int res = -1;
    Node<T>* node(root_);
    
    while (node->next) {
        node = node->next;
        res += 1;
        if (node->value == value) {
            return res;
        }
    }
    
    return -1;
}

// Remove the element at the specified index and return it template <typename T>
template <typename T>
T LinkedList<T>::Remove(int index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range.");
    }

    // Place pointer just before the indexed node
    Node<T>* just_before(root_);
    for (int i = 0; i < index; i++) {
        just_before = just_before->next;
    }
    
    // And find the iterator just after the indexed node
    Node<T>* just_after(just_before->next->next);
    
    // Store value
    T val(just_before->next->value);
    
    // Deallocate node
    delete just_before->next;
    
    // Reassign
    just_before->next = just_after;
    
    if (index == size_ - 1) {
        // If we need to reassign leaf
        leaf_ = just_before;
    }
    
    // Decrement size
    size_--;
    
    return val;
}

// Return an iterator on this list
template <typename T>
ListIterator<T> LinkedList<T>::Iterator() const {
    return ListIterator<T>(root_->next);
}

// Return the size of the list
template <typename T>
int LinkedList<T>::Size() const {
    return size_;
}

#endif /* LinkedList_cpp */

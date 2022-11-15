//
//  DoublyLinkedList.cpp
//  MTH9815_HW1
//
//  Created by 王明森 on 11/9/22.
//

#ifndef DoublyLinkedList_cpp
#define DoublyLinkedList_cpp

#include "DoublyLinkedList.hpp"

template <typename T>
DNode<T>::DNode(const T& val, DNode<T>* nxt, DNode<T>* prv) : value(val), next(nxt), prev(prv) {}

template <typename T>
DNode<T>::DNode(const DNode<T>& node) : value(node.value), next(node.next), prev(node.prev) {}

template <typename T>
DListIterator<T>::DListIterator(DNode<T>* node, DNode<T>* root) : node_(node), root_(root) {};

template <typename T>
DListIterator<T>::DListIterator(const DListIterator<T>& iter) : node_(iter.node_), root_(iter.root_) {}

//template <typename T>
//DListIterator<T>& DListIterator<T>::operator = (const DNode<T>* node) {
//    this->node_ = node;
//    return *this;
//}

template <typename T>
DListIterator<T>& DListIterator<T>::operator = (const DListIterator<T>& iter) {
    if (this != &iter) {
        root_ = iter.root_;
        node_ = iter.node_;
    }
    
    return *this;
}

// Advance (prefix and postfix)
template <typename T>
DListIterator<T>& DListIterator<T>::operator ++ () {
    if (node_) {
        node_ = node_->next;
    }
    
    return *this;
}

template <typename T>
DListIterator<T>& DListIterator<T>::operator ++ (int) {
    DListIterator iter(*this);
    ++(*this);
    return *this;
}

// Regress (prefix and postfix)
template <typename T>
DListIterator<T>& DListIterator<T>::operator -- () {
    if (node_) {
        node_ = node_->prev;
    }
    
    return *this;
}

template <typename T>
DListIterator<T>& DListIterator<T>::operator -- (int) {
    DListIterator iter(*this);
    --(*this);
    return *this;
}

// Compare
template <typename T>
bool DListIterator<T>::operator == (const DListIterator<T>& iter) const {
    return node_ == iter.node_;
}

template <typename T>
bool DListIterator<T>::operator != (const DListIterator<T>& iter) const {
    return node_ != iter.node_;
}

// Compare
template <typename T>
bool DListIterator<T>::operator == (DNode<T>* node) const {
    return node_ == node;
}

template <typename T>
bool DListIterator<T>::operator != (DNode<T>* node) const {
    return node_ != node;
}

// Dereference
template <typename T>
T& DListIterator<T>::operator * () const {
    return node_->value;
}

// Return whether there is another element before this iterator
template <typename T>
bool DListIterator<T>::HasPrev() const {
    return (node_->prev != nullptr) && (node_->prev != this->root_) ;
}

// Retrace self and return the prev element
template <typename T>
T& DListIterator<T>::Prev() {
    node_ = node_->prev;
    return node_->value;
}

// Return whether there is another element to after this iterator
template <typename T>
bool DListIterator<T>::HasNext() const {
    return node_->next != nullptr;
}

// Advance self and return the next element in this iterator
template <typename T>
T& DListIterator<T>::Next() {
    node_ = node_->next;
    return node_->value;
}

// Construct an empty doubly linked list
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    this->size_ = 0;
    root_ = new DNode<T>(T());
    leaf_ = root_;
}

// Add the specified element at the end of the list
template <typename T>
void DoublyLinkedList<T>::Add(const T& value) {
    // Create one more dnode at the end
    leaf_->next = new DNode<T>(value, nullptr, leaf_);
    
    // The end node is shifted forward
    leaf_ = leaf_->next;
    
    // Increment size
    this->size_++;
}

// Add the specified element at the specified index template <typename T>
template <typename T>
void DoublyLinkedList<T>::Insert(const T& value, int index) {
    
    // Index is allowed to vary in [0, size].
    // The inserted element will be at position "index" after insertion
    
    if (index < 0 || index > this->size_) {
        throw std::out_of_range("Index out of range.");
    }
    
    // Place pointer just before the indexed node
    DNode<T>* just_before(root_);
    for (int i = 0; i < index; i++) {
        just_before = just_before->next;
    }
    
    // And find the iterator just after the insert position
    DNode<T>* just_after(just_before->next);
    
    // Build new node and reconnect
    just_before->next = new DNode<T>(value, just_after, just_before);
    just_after->prev = just_before->next;
    
    // Update leaf if insert at the end
    if (index == this->size_) {
        leaf_ = leaf_->next;
    }
    
    this->size_++;
}

// Get the element at the specified index
template <typename T>
T& DoublyLinkedList<T>::Get(int index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range.");
    }
    
    DNode<T>* node(root_->next);
    
    while (index--) {
        node = node->next;
    }
    
    return node->value;
}

// Retrieve the index of the specified element (-1 if it does not exist in the list
template <typename T>
int DoublyLinkedList<T>::IndexOf(const T& value) const {
    
    int res = -1;
    DNode<T>* node(root_);
    
    while (node->next) {
        node = node->next;
        res += 1;
        if (node->value == value) {
            return res;
        }
    }
    
    return -1;
}

// Remove the element at the specified index and return it
template <typename T>
T DoublyLinkedList<T>::Remove(int index) {
    if (index < 0 || index >= this->size_) {
        throw std::out_of_range("Index out of range.");
    }

    // Place pointer just before the indexed node
    DNode<T>* just_before(root_);
    for (int i = 0; i < index; i++) {
        just_before = just_before->next;
    }
    
    // And find the iterator just after the indexed node
    DNode<T>* just_after(just_before->next->next);
    
    // Store value
    T val(just_before->next->value);
    
    // Deallocate node
    delete just_before->next;
    
    // Reassign
    just_before->next = just_after;
    just_after->prev = just_before;
    
    if (index == this->size_ - 1) {
        // If we need to reassign leaf
        leaf_ = just_before;
    }
    
    // Decrement size
    this->size_--;
    
    return val;
}

// Return a bidirectional iterator on this list template <typename T>
template <typename T>
DListIterator<T> DoublyLinkedList<T>::Iterator() const {
    return DListIterator<T>(root_->next, root_);
}

// Return the size of the list
template <typename T>
int DoublyLinkedList<T>::Size() const {
    return size_;
}

#endif /* DoublyLinkedList_cpp */

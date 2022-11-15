//
//  DoublyLinkedList.hpp
//  MTH9815_HW1
//
//  Created by 王明森 on 11/9/22.
//

#ifndef DoublyLinkedList_hpp
#define DoublyLinkedList_hpp

#include "LinkedList.hpp"

template <typename T>
class DNode {
public:
    T value;
    DNode<T>* prev;
    DNode<T>* next;
    
    DNode(const T& val, DNode<T>* nxt = nullptr, DNode<T>* prv = nullptr);
    DNode(const DNode<T>& node);
};

template <typename T>
class DoublyLinkedList;

template <typename T>
class DListIterator {
private:
    DNode<T>* node_;
    DNode<T>* root_;
    
    friend class DoublyLinkedList<T>;
    
public:
    DListIterator(DNode<T>* node, DNode<T>* root);
    DListIterator(const DListIterator<T>& iter);
//    DListIterator<T>& operator = (const DNode<T>* node);
    DListIterator<T>& operator = (const DListIterator<T>& iter);
    
    // Advance (prefix and postfix)
    DListIterator<T>& operator ++ ();
    DListIterator<T>& operator ++ (int);
    
    // Regress (prefix and postfix)
    DListIterator<T>& operator -- ();
    DListIterator<T>& operator -- (int);
    
    // Compare
    bool operator == (const DListIterator<T>& iter) const;
    bool operator != (const DListIterator<T>& iter) const;
    bool operator == (DNode<T>* node) const;
    bool operator != (DNode<T>* node) const;
    
    // Dereference
    T& operator * () const;
    
    // Return whether there is another element before this iterator
    bool HasPrev() const;
    
    // Retrace self and return the prev element
    T& Prev();
    
    // Return whether there is another element after this iterator
    bool HasNext() const;
    
    // Advance self and return the prev element
    T& Next();
};

template <typename T>
class DoublyLinkedList : public LinkedList<T> {
public:
    DNode<T>* root_;
    DNode<T>* leaf_;
    
    int size_;
    
public:
    // Construct an empty doubly linked list
    DoublyLinkedList();
    
    // Add the specified element at the end of the list
    void Add(const T& value);
    
    // Add the specified element at the specified index template <typename T>
    void Insert(const T& value, int index);
    
    // Get the element at the specified index
    T& Get(int index) const;
    
    // Retrieve the index of the specified element (-1 if it does not exist in the list
    int IndexOf(const T& value) const;
    
    // Remove the element at the specified index and return it template <typename T>
    T Remove(int index);
    
    // Return a bidirectional iterator on this list template <typename T>
    DListIterator<T> Iterator() const;
    
    // Return the size of the list
    int Size() const;
};

#ifndef DoublyLinkedList_cpp
#include "DoublyLinkedList.cpp"
#endif /* DoublyLinkedList_cpp */


#endif /* DoublyLinkedList_hpp */

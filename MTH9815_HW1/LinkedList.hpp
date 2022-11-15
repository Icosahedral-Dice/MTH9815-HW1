//
//  LinkedList.hpp
//  MTH9815_HW1
//
//  Created by 王明森 on 11/9/22.
//

#ifndef LinkedList_hpp
#define LinkedList_hpp

template <typename T>
class Node {
public:
    T value;
    Node<T>* next;
    
    Node(const T& val, Node<T>* nxt = nullptr);
};

template <typename T>
class LinkedList;

template <typename T>
class ListIterator {
protected:
    Node<T>* node_;
    
    friend class LinkedList<T>;
    
public:
    ListIterator(Node<T>* node);
    ListIterator(const ListIterator<T>& iter);
    ListIterator<T>& operator = (const Node<T>* node);
    ListIterator<T>& operator = (const ListIterator<T>& iter);
    
    // Advance (prefix and postfix)
    ListIterator<T>& operator ++ ();
    ListIterator<T>& operator ++ (int);
    
    // Compare
    bool operator == (const ListIterator<T>& iter) const;
    bool operator != (const ListIterator<T>& iter) const;
    bool operator == (Node<T>* node) const;
    bool operator != (Node<T>* node) const;
    
    // Dereference
    T& operator * () const;
    
    // Return whether there is another element to return in this iterator
    bool HasNext() const;
    
    // Advance self and return the next element in this iterator
    T& Next();
};

template <typename T>
class LinkedList {
    // NO LOOPS ALLOWED
    
protected:
    Node<T>* root_;
    Node<T>* leaf_;
    
    int size_;
    
public:
    // Construct an empty linked list
    LinkedList();
    
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
    
    // Return an iterator on this list template <typename T>
    ListIterator<T> Iterator() const;
    
    // Return the size of the list
    int Size() const;
};

#ifndef LinkedList_cpp
#include "LinkedList.cpp"
#endif /* LinkedList_cpp */

#endif /* LinkedList_hpp */

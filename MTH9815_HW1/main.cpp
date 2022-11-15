//
//  main.cpp
//  MTH9815_HW1
//
//  Created by 王明森 on 11/9/22.
//

#include <iostream>
#include "LinkedList.hpp"
#include "DoublyLinkedList.hpp"

template <typename T>
void Print(const LinkedList<T>& list) {
    for (auto it = list.Iterator(); it != nullptr; it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void Print(const DoublyLinkedList<T>& list) {
    for (auto it = list.Iterator(); it != nullptr; it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void PrintBackAndForth(const DoublyLinkedList<T>& list) {
    auto it = list.Iterator();
    std::cout << *it << " ";
    while (it.HasNext()) {
        std::cout << it.Next() << " ";
    }
    
    while (it.HasPrev()) {
        std::cout << it.Prev() << " ";
    }
    std::cout << std::endl;
}


int main(int argc, const char * argv[]) {
    
    LinkedList<int> list;

    list.Add(1);
    list.Add(2);
    list.Add(3);
    list.Add(4);

    list.Insert(6, 0);
    Print(list);
    list.Remove(2);

    Print(list);

    std::cout << list.IndexOf(3) << ' ' << list.IndexOf(7) << ' ' << list.Get(2) << std::endl;
    
    DoublyLinkedList<int> dlist;

    dlist.Add(1);
    dlist.Add(2);
    dlist.Add(3);
    dlist.Add(4);

    dlist.Insert(6, 0);
    Print(dlist);
    dlist.Remove(2);

    Print(dlist);

    std::cout << dlist.IndexOf(3) << ' ' << dlist.IndexOf(7) << ' ' << dlist.Get(2) << std::endl;
    
    PrintBackAndForth(dlist);
    return 0;
}

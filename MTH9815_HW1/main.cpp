//
//  main.cpp
//  MTH9815_HW1
//
//  Created by 王明森 on 11/9/22.
//

#include <iostream>
#include "LinkedList.hpp"
#include "DoublyLinkedList.hpp"
#include "HashTable.hpp"

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


void TestLinkedList() {
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
}

void TestDoublyLinkedList() {
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
}

void TestHashTable() {
    HashTable<int, int> ht(100);
    
    ht.add(201, 12);
    ht.add(202, 212);
    ht.add(18, 4);
    ht.add(101, 33);
    ht.add(102, 418);
    ht.print();
    
    std::cout << "\nFind key = 102 : " << *ht.find(102) << "\n";
    std::cout << "\nAfter Erase key = 202: \n";
    ht.erase(202);
    ht.print();
    std::cout << "\nAfter Erase key = 101: \n";
    ht.erase(101);
    ht.print();
}

int main(int argc, const char * argv[]) {
    
    TestLinkedList();
    TestDoublyLinkedList();
    TestHashTable();
    
    return 0;
}

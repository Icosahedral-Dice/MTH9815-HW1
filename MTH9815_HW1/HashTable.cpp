//
//  HashTable.cpp
//  MTH9815_HW1_hash
//
//  Created by Aubree Li on 11/15/22.
//


#ifndef HASHTABLE_CPP
#define HASHTABLE_CPP

#include "HashTable.hpp"
#include <iostream>

template<typename K, typename V>
hash_item<K, V>::hash_item(const K &k, const V &v) : key(k), val(v) {}

template<typename K, typename V>
K hash_item<K, V>::Key() const {return this->key;}

template<typename K, typename V>
V hash_item<K, V>::Val() const {return this->val;}


template<typename K, typename V>
HashTable<K, V>::HashTable(int size) : table_size(size) {table.resize(size);}

template<typename K, typename V>
int HashTable<K, V>::hash_function(const K &key) {
    return int(key) % table_size;
}

template<typename K, typename V>
bool HashTable<K, V>::is_equal(const K& k1, const K& k2) {
    return k1 == k2;
}

template<typename K, typename V>
void HashTable<K, V>::add(K k, V v) {
    if (item_nums >= table_size) {
        std::cout << "Hash Table is full.\n";
    } else {
        hash_item h_it(k, v);
        int index = hash_function(k);
        if (table[index].size() != 0) {
            collision_counter++;
        }
        item_nums++;
        table[index].push_back(h_it);
    }
}

template<typename K, typename V>
hash_item<K, V>* HashTable<K,V>::find(K key) {
    int index = hash_function(key);
    for (auto& elem : table[index]) {
        if (elem.Key() == key) {
            return &elem;
        }
    }
    // no match
    return nullptr;
}

template<typename K, typename V>
void HashTable<K,V>::erase(K key) {
    int index = hash_function(key);
    
    for (int i = 0; i < table[index].size(); ++i) {
        if (this->is_equal(table[index][i].Key(), key)) {
            table[index].erase(table[index].begin() + i);
            item_nums --;
            if (table[index].size() != 0) collision_counter--;
        }
    }
}

template<typename K, typename V>
void HashTable<K,V>::print() const {
    for (int i = 0; i < table_size; ++i) {
        if (this->table[i].size() != 0) {
            std::cout << i <<": ";
            for (auto& elem : table[i]) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
    }
    
    std::cout << "Total item number: " << this->get_item_num() << ", Collission counts: " << this->count_collision() <<"\n";
}

template<typename K, typename V>
int HashTable<K,V>:: count_collision() const {return collision_counter;}

template<typename K, typename V>
int HashTable<K,V>:: get_item_num() const {return item_nums;}

#endif

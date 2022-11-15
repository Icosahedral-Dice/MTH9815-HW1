//
//  HashTable.hpp
//  MTH9815_HW1_hash
//
//  Created by Aubree Li on 11/15/22.
//

#ifndef HashTable_hpp
#define HashTable_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <ostream>

template <typename K>
class Hasher {
public:
    virtual int hash_function(const K& key) = 0;
};


template <typename K>
class EqualityPredicate {
public:
    virtual bool is_equal(const K& k1, const K& k2) = 0;
};



template <typename K, typename V>
class hash_item {
private:
    K key;
    V val;
public:
    hash_item(const K &k, const V &v);
    K Key() const;
    V Val() const;
    friend std::ostream& operator<<(std::ostream& os, const hash_item& hi) {
        return os << "{Key: " << hi.key << ", Val: "<< hi.val << "}";
    }
};


template <typename K, typename V>
class HashTable : public Hasher<K>, public EqualityPredicate<K> {
protected:
    //The hash table, in vectors
    int table_size;
    int item_nums = 0;
    int collision_counter = 0;
    std::vector<std::vector<hash_item<K, V>>> table;
    bool is_equal(const K& k1, const K& k2);
    
public:
    HashTable(int size);
    int hash_function(const K& key);
    void add(K k, V v);
    hash_item<K, V>* find(K key);
    void erase(K key);
    void print() const;
    int count_collision() const;
    int get_item_num() const;
};


#ifndef HASHTABLE_CPP
#include "HashTable.cpp"
#endif

#endif /* HashTable_hpp */

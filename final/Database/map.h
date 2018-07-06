//
// Created by Gregory Montilla on 4/24/18.
//

#ifndef MAP_MAP_H
#define MAP_MAP_H

#include "pair.h"
#include "b_tree.h"

template <typename K, typename V>
class Map {
public:
    Map();

    Map& operator=(const Map& rhs) {
        map.copy_tree(rhs.map);
        return *this;
    };

//  Capacity
    int size() const {
        return key_count;
    };
    bool empty() const {
        return size() == 0;
    };

//  Element Access
    V& operator[](const K& key) {
        return map.get(key).value;
    };

    V& at(const K& key) {
        return map.get(key).value;
    };

//  Modifiers
    void insert(const K& k, const V& v) {
        key_count++;
        map.insert(Pair<K,V>(k,v));
    };

    void erase(const K& key) {
        key_count--;
        map.remove(key);
    };

    void clear() {
        map.clear_tree();
    };

    V get(const K& key) {
        Pair<K, V> pair(K);
        if (!map.contains(pair)) {
            map.insert(pair);
        }
        return map.get(key).value;
    };

//  Operations:
//    Iterator find(const K& key);
    bool contains(const Pair<K, V>& target) const {
        return map.contains(target);
    };

    // I have not written these yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

//    bool is_valid(){return map.is_valid();}

    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me){
        outs<<print_me.map<<endl;
        return outs;
    }
private:
    int key_count;
    BTree<Pair<K, V> > map;
};

template <typename K, typename V>
Map<K, V>::Map() {
    key_count=0;
}


#endif //MAP_MAP_H

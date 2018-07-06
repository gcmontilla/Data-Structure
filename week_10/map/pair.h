//
// Created by Gregory Montilla on 4/24/18.
//

#ifndef MAP_PAIR_H
#define MAP_PAIR_H

#include <iostream>
#include <string>
using namespace std;

template <typename K, typename V>
struct Pair{
    K key;
    V value;

    Pair(const K& k=K(), const V& v=V()) {
        key = k;
        value = v;
    };

    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me) {
        cout<<print_me.key<<": "<<print_me.value<<endl;
        return outs;
    };

    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs) {
        return (lhs.key == rhs.key);
    };

    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs) {
        return (lhs.key < rhs.key);
    };

    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs) {
        return (lhs.key > rhs.key);
    };

    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs) {
        return (lhs.key <= rhs.key);
    };

    friend bool operator >= (const Pair<K, V>& lhs, const Pair<K, V>& rhs) {
        return (lhs.key >= rhs.key);
    };
};

#endif //MAP_PAIR_H

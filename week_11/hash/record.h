//
// Created by Gregory Montilla on 5/2/18.
//

#ifndef HASH_RECORD_H
#define HASH_RECORD_H

#include <iostream>
using namespace std;

template<typename T>
struct record {
    int key;
    T value;

    record(int k=0, T v=T()) {
        key=k;
        value=v;
    };

    void set_record(int k, T v) {
        key=k;
        value=v;
    }

    friend bool operator == (const record& left, const record& right) {
        return left.value == right.value;
    }

    friend ostream& operator << (ostream& outs, const record& print_me) {
        cout << print_me.value << endl;
        return outs;
    }

    friend istream& operator >>(istream& is, const record& me) {
        int key;
        T value;
        is >> key >> value;
        return is;
    }
};

#endif //HASH_RECORD_H

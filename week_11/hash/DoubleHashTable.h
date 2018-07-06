//
// Created by Gregory Montilla on 5/7/18.
//

#ifndef HASH_DOUBLEHASHTABLE_H
#define HASH_DOUBLEHASHTABLE_H

#include "record.h"

template<typename T, typename K>
class DoubleHashTable{
public:
    static const int CAPACITY = 11;
    DoubleHashTable();
    void insert(const T& entry);
    void remove(int key);
    bool is_present(int key) const;
    void find( int key, bool& found, T& result) const;
    int size();
    int get_collisions();
    void display_hash();
    void test();
private:
    static const int NEVER_USED = -1;
    static const int PREV_USED = -2;
    int _size;
    int collisions;
    T data[CAPACITY];
    int hash(int key) const;
    int hash_again(int key) const;
    int next_index(int index, int key) const;
    void find_index(int key, bool& found, int& index) const;
    bool never_used(int size) const;
    bool is_vacant(int size) const;
};

template<typename T, typename K>
DoubleHashTable<T, K>::DoubleHashTable() {
    _size = 0;
    collisions = 0;
    for (int i = 0; i < CAPACITY; ++i) {
        data[i].key = NEVER_USED;
    }
}

template<typename T, typename K>
void DoubleHashTable<T, K>::insert(const T &entry) {
    bool is_present;
    int index;
    find_index(entry.key, is_present,index);
    if(!is_present) {
        index = hash(entry.key);
        while (!is_vacant(index)) {
            assert(size() < CAPACITY);
            index = next_index(index, entry.key);
            ++collisions;
        }
        ++_size;
        data[index] = entry;
    }
}

template<typename T, typename K>
void DoubleHashTable<T, K>::remove(int key) {
    assert(key >= 0);
    bool found;
    int index;
    find_index(key, found, index);
    if (found) {
        data[index].key = PREV_USED;
        --_size;
    }
}


template<typename T, typename K>
bool DoubleHashTable<T, K>::is_present(int key) const {
    bool found;
    int index;
    assert(key >= 0);
    find_index(key, found, index);
    return found;
}

template<typename T, typename K>
void DoubleHashTable<T, K>::find(int key, bool &found, T &result) const {
    int index;
    assert(key >= 0);
    find_index(key, found, index);
    if (found) {
        result = data[index];
    }
}

template<typename T, typename K>
int DoubleHashTable<T, K>::size() {
    return _size;
}

template<typename T, typename K>
int DoubleHashTable<T, K>::next_index(int index, int key) const {
    return (index + hash_again(key)) % CAPACITY;
}

template<typename T, typename K>
void DoubleHashTable<T, K>::find_index(int key, bool &found, int& index) const {
    int count = 0;
    index = hash(key);
    while((count<CAPACITY) && (!never_used(index)) && (data[index].key != key)) {
        ++count;
        index = next_index(index, key);
    }
    found = (data[index].key == key);
}

template<typename T, typename K>
bool DoubleHashTable<T, K>::never_used(int size) const {
    return data[size].key == NEVER_USED;
}

template<typename T, typename K>
bool DoubleHashTable<T, K>::is_vacant(int size) const {
    return data[size].key < 0;
}

template<typename T, typename K>
int DoubleHashTable<T, K>::hash(int key) const {
    return key % CAPACITY;
}

template<typename T, typename K>
int DoubleHashTable<T, K>::hash_again(int key) const {
    return 1 + (key % (CAPACITY -2));
}

template<typename T, typename K>
int DoubleHashTable<T, K>::get_collisions() {
    return collisions;
}

template<typename T, typename K>
void DoubleHashTable<T, K>::display_hash() {
    for (int i = 0; i < CAPACITY; i++) {
        cout << "[" << setfill('0') << setw(3) << i << "]";
        if (data[i].key > 0)
            cout << "->[" << setw(4) << data[i].key << ":" << setw(4) << data[i].value << "]";
        cout << "->|||" << endl;
    }
}

template<typename T, typename K>
void DoubleHashTable<T, K>::test(){
    char choice;
    int key;
    bool found;
    K value;
    T entry;
    cout << "[S]ize() [I]nsert [R]andom [D]elete [F]ind value [?]exists?   e[X]it ";
    cin >> choice;
    do {
        switch (choice) {
            case 'S':
                cout << "Size: " << size() << endl;
                break;
            case 'I':
                cout << "Key: ";
                cin>>key;
                cout << "Value: ";
                cin>>value;
                insert(record(key, value));
                break;
            case 'R':
                insert(record(rand() % 20 + 1, rand() % 20 + 1));
                break;
            case 'D':
                cout << "Key: ";
                cin >> key;
                remove(key);
                break;
            case 'F':
                cout << "Key: ";
                cin >> key;
                find(key, found, entry);
                if (found) {
                    cout << "Value is " << entry << endl;
                } else {
                    cout << "Not in here";
                }
                break;
            case '?':
                cout << "Key: ";
                cin >>key;
                if (is_present(key)) {
                    cout << key << " is in here" << endl;
                } else {
                    cout << key << " isn't in here"<<endl;
                }
                break;
            default:
                break;
        }
        cout<<endl;
        display_hash();
        cout<<endl;
        cout << "[S]ize() [I]nsert [R]andom [D]elete [F]ind value [?]exists?   e[X]it ";
        cin >> choice;
    } while (choice != 'X');
};

#endif //HASH_DOUBLEHASHTABLE_H

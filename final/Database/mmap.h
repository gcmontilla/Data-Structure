#ifndef MMAP_H
#define MMAP_H
#include <vector>
#include <iostream>
#include "BPlusTree.h"
#include <assert.h>
#include "utility.h"

using namespace std;

template <typename K, typename V>
struct MPair{
    K key;
    vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
    //--------------------------------------------------------------------------------
    MPair(const K& k=K()): key(k) {}

    MPair(const K& k, const V& v): key(k) { value_list.push_back(v); }

    MPair(const K& k, const vector<V>& vlist): key(k), value_list(vlist) {}

    //--------------------------------------------------------------------------------

    //You'll need to overload << for your vector:
    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me)
    {
        outs<<print_me.key<<"-[";
        for (int i = 0; i < print_me.value_list.size(); ++i) {
            if (i == print_me.value_list.size()-1) {
                cout << print_me.value_list[i];
            } else {
                cout << print_me.value_list[i] << ",";
            }
        }
        outs<<"]";
        return outs;
    }

    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs) { return (lhs.key == rhs.key); }

    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs) { return lhs.key < rhs.key; }

    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs) { return (lhs.key <= rhs.key); }

    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs) { return lhs.key > rhs.key; }

    friend bool operator >= (const MPair<K, V>& lhs, const MPair<K, V>& rhs) { return lhs.key >= rhs.key; }

    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        //????what should this do?

    }

    MPair<K, V>& operator += (const MPair<K, V>& other) {
        assert(key == other.key);
        value_list += other.value_list;
        return *this;
    }
};

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator {
    public:
        friend class MMap;
        Iterator(typename map_base::Iterator it) {
            _it = it;
        };
        Iterator operator ++(int unused) {
            ++_it;
        };
        Iterator operator ++() {
            _it++;
        };
        MPair<K, V> operator *() {
            return *_it;
        };
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){

        };
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
        };

    private:
        typename map_base::Iterator _it;
    };

    MMap();
    MMap&operator = (const MMap& rhs) {
        mmap = rhs.mmap;
    }

//  Iterators

//  Capacity
    int size() const;
    bool empty() const {
        return size()==0;
    };

//  Element Access
    vector<V>& operator[](const K& key)
    {
        return mmap.get(MPair<K, V>(key)).value_list;
    }

//  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();

//  Operations:
    bool contains(const K& key) const ;
    vector<V> &get(const K& key);

    Iterator find(const K& key);
    int count(const K& key);

    // I have not written these yet, but we will need them:
    // int count(const K& key);
    Iterator begin();
    Iterator end();
    Iterator lower_bound(const K& key);
    Iterator upper_bound(const K& key);
//    bool is_valid();

    friend ostream& operator << (ostream& outs, const MMap<K, V>& print_me)
    {
        cout<<print_me.mmap;
        return outs;
    }


private:
    BPlusTree<MPair<K, V> > mmap;
    int how_many;
};

template <typename K, typename V>
MMap<K, V>::MMap(){
    how_many = 0;
}

template <typename K, typename V>
void MMap<K, V>::insert(const K& k, const V& v) {
    if (!mmap.contains(MPair<K, V> (k))) {
        mmap.insert(MPair<K,V>(k,v));
    } else {
        mmap.get(k).value_list.push_back(v);
    }
    how_many++;
}

template<class K,class V>
typename MMap<K,V>::Iterator MMap<K,V>::begin(){
    return mmap.begin();
}
template<class K,class V>
typename MMap<K,V>::Iterator MMap<K,V>::end(){
    return mmap.end();
}

template <typename K, typename V>
void MMap<K, V>::erase(const K &key) { }

template <typename K, typename V>
void MMap<K, V>::clear() { }

template <typename K, typename V>
bool MMap<K, V>::contains(const K &key) const { return mmap.contains(MPair<K, V>(key)); }

template <typename K, typename V>
vector<V>& MMap<K, V>::get(const K &key) { return mmap.get(MPair<K, V> (key)).value_list; }


template<class K,class V>
typename MMap<K,V>::Iterator MMap<K,V>::lower_bound(const K &key){
    return mmap.lower_bound(MPair<K,V> (key,V()));
}
template<class K,class V>
typename MMap<K,V>::Iterator MMap<K,V>::upper_bound(const K &key){
    return mmap.upper_bound(MPair<K,V> (key,V()));
}

#endif // MMAP_H

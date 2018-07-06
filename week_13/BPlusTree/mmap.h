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
        for (auto i : print_me.value_list) {
            outs << i << "->";
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

    MPair<K, V>& operator += (const MPair<K, V>& other)
    {
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
    class Iterator{
    public:
        friend class MMap;
        Iterator(typename map_base::Iterator it);
        Iterator operator ++(int unused);
        Iterator operator ++();
        MPair<K, V> operator *();
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs);
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs);

    private:
        typename map_base::Iterator _it;
    };

    MMap();

//  Iterators
    Iterator begin();
    Iterator end();

//  Capacity
    int size() const;
    bool empty() const;

//  Element Access
//    const vector<V>& operator[](const K& key) const
//    {
//        return mmap.get(MPair<K,V>(key)).value_list;
//    }

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
    //    lower_bound
    //    upper_bound
    //    equal_range:

    bool is_valid();

    friend ostream& operator << (ostream& outs, const MMap<K, V>& print_me)
    {
        cout<<print_me.mmap<< endl;
        return outs;
    }


private:
    BPlusTree<MPair<K, V> > mmap;
};

template <typename K, typename V>
MMap<K, V>::MMap() { }

template <typename K, typename V>
void MMap<K, V>::insert(const K& k, const V& v) {
    if (!mmap.contains(MPair<K, V> (k))) {
        mmap.insert(MPair<K,V>(k,v));
    } else {
        cout << "contains" << endl;
        mmap.get(k).value_list.push_back(v);
    }
}

template <typename K, typename V>
void MMap<K, V>::erase(const K &key) { }

template <typename K, typename V>
void MMap<K, V>::clear() {
    mmap.clear_tree();
    }

template <typename K, typename V>
bool MMap<K, V>::contains(const K &key) const { return mmap.contains(MPair<K, V>(key)); }

template <typename K, typename V>
vector<V>& MMap<K, V>::get(const K &key) { return mmap.get(MPair<K, V> (key)).value_list; }

#endif // MMAP_H

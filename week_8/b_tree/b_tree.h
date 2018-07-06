//
// Created by Gregory Montilla on 4/10/18.
//

#ifndef B_TREE_BTREE_H
#define B_TREE_BTREE_H

#include <vector>
#include <iostream>
#include <iomanip>

#include "utility.h"

using namespace std;

template <class T>
class b_tree{
public:
    b_tree(bool dups = false);

    //big three:
    b_tree(const b_tree<T>& other);
    ~b_tree() {
        clear_tree();
    }
    b_tree<T>& operator =(const b_tree<T>& RHS);

    void insert(const T& entry);                //insert entry into the tree
    void remove(const T& entry);                //remove entry from the tree

    void clear_tree();
    void copy_tree(const b_tree<T>& other);

    bool contains(const T& entry);
    T& get(const T& entry);
    T* find(const T& entry);

    int size() const;
    bool empty() const {
        return size() == 0;
    }

    void print_tree(int level = 0, ostream &outs=cout) const;

    friend ostream& operator<<(ostream& outs, const b_tree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }

public:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                                   //true if duplicate keys may be inserted
    int data_count=0;                                 //number of data elements
    T data[MAXIMUM + 1];                            //holds the keys
    int child_count=0;                                //number of children
    b_tree* subset[MAXIMUM + 2];                     //subtrees

    bool is_leaf() const {return child_count==0;}   //true if this is a leaf node

    void loose_insert(const T& entry);              //allows MAXIMUM+1 data elements in the root
    void fix_excess(int i);                         //fix excess of data elements in child i

    void loose_remove(const T& entry);              //allows MINIMUM-1 data elements in the root
    void fix_shortage(int i);                       //fix shortage of data elements in child i

    void remove_biggest(T& entry);                  //remove the biggest child of this tree->entry
    void rotate_left(int i);                        //transfer one element LEFT from child i
    void rotate_right(int i);                       //transfer one element RIGHT from child i
    void merge_with_next_subset(int i);             //merge subset i with subset i+1

};

/**
 * Constructor for balanced tree
 * @tparam T Data type
 * @param dups Duplicates allowed
 */
template<class T>
b_tree<T>::b_tree(bool dups){
    for(int i=0;i<MAXIMUM+2;i++){
        subset[i] = NULL;
    }
}

/**
 * Prints entire balanced tree
 * @tparam T Data type
 * @param level Level
 * @param outs Out stream
 */
template<class T>
void b_tree<T>::print_tree(int level, ostream &outs) const{
    if(child_count==0){
        for(int i = data_count-1;i>=0;i--){
            cout<<setw(4*level)<<" "<<data[i]<<endl;
        }
        return;
    }
    subset[child_count-1]->print_tree(level+1,outs);
    for(int i = data_count-1;i>=0;i--){
        cout<<setw(4*level)<<" "<<data[i]<<endl;
        subset[i]->print_tree(level+1,outs);
    }
}

/**
 * Determines whether entry is in the balanced tree
 * @tparam T Data type
 * @param entry Entry
 * @return True if entry is in the balanced tree
 */
template<typename T>
bool b_tree<T>::contains(const T& entry) {
    int i = first_ge(data, data_count, entry);
    if (data[i] == entry) {
        return true;
    }
    if (!is_leaf()) {
        return subset[i]->contains(entry);
    }
    return false;
}

/**
 * Finds the entry in the balanced tree
 * @tparam T Data type
 * @param entry Entry
 * @return Pointer to found item in balanced tree
 */
template<typename T>
T* b_tree<T>::find(const T &entry) {
    T* ptr = nullptr;
    if (contains(entry)) {
        int i = first_ge(data, data_count, entry);
        if (data[i] == entry) {
            ptr = &data[i];
        }
        if (!is_leaf()) {
            return subset[i]->find(entry);
        }
    }
    return ptr;
}

/**
 * Gets reference to entry in balanced tree
 * @tparam T Data type
 * @param entry Entry
 * @return Reference to item in balanced tree
 */
template<typename T>
T& b_tree<T>::get(const T &entry) {
    T& reference = 0;
    if (contains(entry)) {
        reference = find(entry);
    }
    return reference;
}

/**
 * Inserts entry into balanced tree
 * @tparam T Data type
 * @param entry Entry
 */
template<class T>
void b_tree<T>::insert(const T &entry){
    loose_insert(entry);
    if(data_count>MAXIMUM){
        b_tree<T>* temp = new b_tree<T>;
        copy_array(temp->data,data,temp->data_count,data_count);
        copy_array(temp->subset,subset,temp->child_count,child_count);
        data_count=0;
        child_count=0;
        subset[0] = temp;
        child_count++;
        fix_excess(0);
    }
}

/**
 * Determines how to insert entry into balanced tree
 * @tparam T Data type
 * @param entry Entry
 */
template<class T>
void b_tree<T>::loose_insert(const T &entry){
    int i = first_ge(data,data_count,entry);
    bool found = (i<data_count && data[i] == entry);
    if(found){
        return;
    }else{
        if(is_leaf()){
            insert_item(data,i,data_count,entry);
        }else{
            subset[i]->loose_insert(entry);
            fix_excess(i);
        }
    }
}

/**
 * Fixes excess in leaf
 * @tparam T Data type
 * @param i Child index to be fixed
 */
template<class T>
void b_tree<T>::fix_excess(int i){
    if(subset[i]->data_count > MAXIMUM){
        insert_item(subset,i+1,child_count,new b_tree<T>);
        split(subset[i]->data,subset[i]->data_count,subset[i+1]->data,subset[i+1]->data_count);
        split(subset[i]->subset,subset[i]->child_count,subset[i+1]->subset,subset[i+1]->child_count);
        T item;
        detach_item(subset[i]->data,subset[i]->data_count,item);
        ordered_insert(data,data_count,item);
    } else {
        return;
    }
}

/**
 * Rotates balanced tree to the right
 * @tparam T Data type
 * @param i Child index to be rotated right
 */
template<class T>
void b_tree<T>::rotate_right(int i){
    if((i<child_count-1)&&(subset[i]->data_count>MINIMUM)){

        T parent;
        delete_item(data,i,data_count,parent);
        ordered_insert(subset[i+1]->data,subset[i+1]->data_count,parent);

        T kid;
        detach_item(subset[i]->data,subset[i]->data_count,kid);
        ordered_insert(data,data_count,kid);

        if(subset[i]->child_count>0){
            b_tree<T>* kid_ptr=NULL;
            detach_item(subset[i]->subset,subset[i]->child_count,kid_ptr);
            insert_item(subset[i+1]->subset,0,subset[i+1]->child_count,kid_ptr);
        }
    }
}

/**
 * Rotates balanced tree to the left
 * @tparam T Data type
 * @param i Child index to be rotated left
 */
template<class T>
void b_tree<T>::rotate_left(int i){
    if((i<child_count)&&(subset[i]->data_count>MINIMUM)){
        T parent;
        detach_item(data,data_count,parent);
        attach_item(subset[i-1]->data,subset[i-1]->data_count,parent);
        T kid;
        delete_item(subset[i]->data,0,subset[i]->data_count,kid);
        attach_item(data,data_count,kid);
        if(subset[i]->child_count>0){
            b_tree<T>* kid_ptr = NULL;
            delete_item(subset[i]->subset,0,subset[i]->child_count, kid_ptr);
            attach_item(subset[i-1]->subset,subset[i-1]->child_count,kid_ptr);
        }
    }
}

/**
 * Searches the children for the biggest item
 * @tparam T Data type
 * @param entry Biggest item
 */
template<class T>
void b_tree<T>::remove_biggest(T &entry){
    if(is_leaf()){
        detach_item(data,data_count,entry);
        return;
    }
    subset[child_count-1]->remove_biggest(entry);
    if (subset[child_count-1]->data_count < MINIMUM) {
        fix_shortage(child_count - 1);
    }
}

/**
 * Determines what to do after deleting entry
 * @tparam T Data type
 * @param entry Entry
 */
template<class T>
void b_tree<T>::loose_remove(const T &entry){
    int i = first_ge(data,data_count,entry);
    bool found = (i<data_count && data[i] == entry);
    if (found) {
        if (is_leaf()) {
            T item;
            delete_item(data, i, data_count, item);
        } else {
            T item;
            subset[i]->remove_biggest(item);
            Swap(data[i], item);
            if (subset[i]->data_count < MINIMUM) {
                fix_shortage(i);
            }
        }
    } else {
        if (!is_leaf()) {
            subset[i]->loose_remove(entry);
            if (subset[i]->data_count < MINIMUM) {
                fix_shortage(i);
            }
        }
    }
}

/**
 * Merges child at index with child at index + 1
 * @tparam T Data type
 * @param i Index
 */
template<class T>
void b_tree<T>::merge_with_next_subset(int i){
    T entry;
    delete_item(data,i,data_count,entry);
    ordered_insert(subset[i]->data,subset[i]->data_count,entry);
    b_tree<T>* temp = subset[i+1];
    merge(subset[i]->data,subset[i]->data_count,subset[i+1]->data,subset[i+1]->data_count);
    if(subset[i+1]->child_count>0){
        merge(subset[i]->subset,subset[i]->child_count,subset[i+1]->subset,subset[i+1]->child_count);
    }
    delete temp;
    temp = NULL;
    b_tree<T>* ptr;
    delete_item(subset, i+1, child_count, ptr);
}

/**
 * Fixes shortage in the children at index
 * @tparam T Data type
 * @param i Index
 */
template<class T>
void b_tree<T>::fix_shortage(int i){
    if (i > 0 && subset[i - 1]->data_count > MINIMUM) {
        rotate_right(i - 1);
    } else if ((i < (child_count-1)) && (subset[i + 1]->data_count > MINIMUM)) {
        rotate_left(i + 1);
    } else if (i == 0) {
        merge_with_next_subset(i);
    } else {
        merge_with_next_subset(i - 1);
    }
}

/**
 * Removes entry from the balanced tree
 * @tparam T Data type
 * @param entry Entry
 */
template<class T>
void b_tree<T>::remove(const T &entry) {
    loose_remove(entry);
    if (data_count < MINIMUM and child_count > 0) {
        b_tree<T>* temp = subset[0];
        copy_array(data,subset[0]->data,data_count,subset[0]->data_count);
        copy_array(subset,subset[0]->subset,child_count,subset[0]->child_count);
        temp->child_count=0;
        delete temp;
        temp = NULL;
    }
}

/**
 * Clears entire balanced tree
 * @tparam T Data type
 */
template <typename T>
void b_tree<T>::clear_tree() {
    if (!is_leaf()) {
        for (int i = 0; i < child_count; ++i) {
            subset[i]->clear_tree();
        }
    }
    child_count = 0;
    data_count = 0;
}


#endif //B_TREE_BTREE_H

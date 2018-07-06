//
// Created by Gregory Montilla on 5/23/18.
//

#ifndef BPLUSTREE_BPLUSTREE_H
#define BPLUSTREE_BPLUSTREE_H

#include <vector>
#include <iostream>
#include <iomanip>

#include "utility.h"

template <typename T>
class BPlusTree {
   public:
    BPlusTree();

    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree() {
        clear_tree();
    }
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS) {
        copy_tree(RHS, ptr);
        return *this;
    };

    void insert(const T& entry);                //insert entry into the tree
    void remove(const T& entry);                //remove entry from the tree

    void clear_tree();
    void copy_tree(const BPlusTree<T>& other, vector<BPlusTree<T>*>& ptr);

    bool contains(const T& entry) const;
    T& get(const T& entry);
    T& get_existing(const T& entry);
    T* find(const T& entry);

    int size() const;
    bool empty() const {
        return size() == 0;
    }

    void print_tree(int level = 0, ostream &outs=cout) const;

    friend ostream& operator<<(ostream& outs, const BPlusTree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                                   //true if duplicate keys may be inserted
    int data_count=0;                               //number of data elements
    T data[MAXIMUM + 1];                            //holds the keys
    int child_count=0;                              //number of children
    BPlusTree* subset[MAXIMUM + 2];                 //subtrees

    BPlusTree* next;
    vector<BPlusTree<T>*> ptr;

    bool is_leaf() const {return child_count==0;}   //true if this is a leaf node

    void loose_insert(const T& entry);              //allows MAXIMUM+1 data elements in the root
    void fix_excess(int i);                         //fix excess of data elements in child i

    void loose_remove(const T& entry);              //allows MINIMUM-1 data elements in the root
    BPlusTree<T>* fix_shortage(int i);                       //fix shortage of data elements in child i

    BPlusTree<T>* get_smallest_node();
    void remove_biggest(T& entry);                  //remove the biggest child of this tree->entry
    void rotate_left(int i);                        //transfer one element LEFT from child i
    void rotate_right(int i);                       //transfer one element RIGHT from child i
    BPlusTree<T>* merge_with_next_subset(int i);             //merge subset i with subset i+1

    void get_smallest(T& entry);
    void get_biggest(T& entry);
    void transfer_left(int i);
    void transfer_right(int i);

};

/**
 * Constructor for balanced tree
 * @tparam T Data type
 * @param dups Duplicates allowed
 */
template<class T>
BPlusTree<T>::BPlusTree(){
    for(int i=0;i<MAXIMUM+2;i++){
        subset[i] = NULL;
    }
    ptr.push_back(NULL);
}

template<typename T>
BPlusTree<T>::BPlusTree(const BPlusTree<T> &other) {
    vector<BPlusTree*> ptr = nullptr;
    copy_tree(other, ptr);
}

/**
 * Prints entire balanced tree
 * @tparam T Data type
 * @param level Level
 * @param outs Out stream
 */
template<class T>
void BPlusTree<T>::print_tree(int level, ostream &outs) const{
    if(is_leaf()){
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
bool BPlusTree<T>::contains(const T& entry) const {
    int i = first_ge(data, data_count, entry);
    if (data[i] == entry && i < data_count) {
        return true;
    }
    if (!is_leaf()) {
        return subset[i]->contains(entry);
    } else {
        return false;
    }
}

/**
 * Finds the entry in the balanced tree
 * @tparam T Data type
 * @param entry Entry
 * @return Pointer to found item in balanced tree
 */
template<typename T>
T* BPlusTree<T>::find(const T &entry) {
    T* ptr = nullptr;
    if (contains(entry)) {
        int i = first_ge(data, data_count, entry);
        if (data[i] == entry) {
            ptr = data[i];
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
T& BPlusTree<T>::get(const T &entry) {
//    if (contains(entry)) {
//        int i =  first_ge(data, data_count, entry);
//        if (i < data_count && data[i] == entry) {
//            return data[i];
//        }
//        if (!is_leaf()) {
//            return subset[i]->get(entry);
//        }
//    } else {
//        insert(entry);
//        return get(entry);
//    }
    if(!contains(entry)) {
        insert(entry);
    }
    return get_existing(entry);
}

template <typename T>
T& BPlusTree<T>::get_existing(const T &entry) {
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count and data[i] == entry);
    if (is_leaf()) {
        if (found) {
            return data[i];
        } else {
            assert(found);
        }
    }
    if (found) {
        return subset[i+1]->get(entry);
    } else {
        return subset[i]->get(entry);
    }
}

/**
 * Inserts entry into balanced tree
 * @tparam T Data type
 * @param entry Entry
 */
template<class T>
void BPlusTree<T>::insert(const T &entry){
    loose_insert(entry);
    if(data_count>MAXIMUM){
        BPlusTree<T>* temp = new BPlusTree<T>;
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
void BPlusTree<T>::loose_insert(const T &entry){
    int i = first_ge(data,data_count,entry);
    bool found = (i<data_count && data[i] == entry);
    if(!found){
        if(is_leaf()){
            insert_item(data,i,data_count,entry);
        }else{
            subset[i]->loose_insert(entry);
            fix_excess(i);
        }
    } else {
        if(!is_leaf()) {
            subset[i+1]->loose_insert(entry);
            fix_excess(i+1);
        }
    }
}

/**
 * Fixes excess in leaf
 * @tparam T Data type
 * @param i Child index to be fixed
 */
template<class T>
void BPlusTree<T>::fix_excess(int i){
    if(subset[i]->data_count > MAXIMUM){
        insert_item(subset,i+1,child_count,new BPlusTree<T>);
        split(subset[i]->data,subset[i]->data_count,subset[i+1]->data,subset[i+1]->data_count);
        split(subset[i]->subset,subset[i]->child_count,subset[i+1]->subset,subset[i+1]->child_count);
        subset[i+1]->next=subset[i]->next;
        T item;
        detach_item(subset[i]->data,subset[i]->data_count,item);
        ordered_insert(data,data_count,item);
        if (subset[i]->is_leaf()) {
            ordered_insert(subset[i+1]->data, subset[i+1]->data_count, item);
            subset[i]->next=subset[i+1];
        }
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
void BPlusTree<T>::rotate_right(int i){
    if((i<child_count-1)&&(subset[i]->data_count>MINIMUM)){
        cout<<"rotate right"<<endl;
        T parent;
        delete_item(data,i,data_count,parent);
        ordered_insert(subset[i+1]->data,subset[i+1]->data_count,parent);

        T kid;
        detach_item(subset[i]->data,subset[i]->data_count,kid);
        ordered_insert(data,data_count,kid);

        if(subset[i]->child_count>0){
            cout<<"transferring kids"<<endl;
            BPlusTree<T>* kid_ptr=NULL;
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
void BPlusTree<T>::rotate_left(int i){
    if((i<child_count)&&(subset[i]->data_count>MINIMUM)){
        cout<<"rotate left"<<endl;
        T parent;
        detach_item(data,data_count,parent);
        attach_item(subset[i-1]->data,subset[i-1]->data_count,parent);
        T kid;
        delete_item(subset[i]->data,0,subset[i]->data_count,kid);
        attach_item(data,data_count,kid);
        if(subset[i]->child_count>0){
            BPlusTree<T>* kid_ptr = NULL;
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
void BPlusTree<T>::remove_biggest(T &entry){
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
 * Searches the children for the smallest item
 * @tparam T Data type
 * @param entry Smallest item
 */
template<typename T>
void BPlusTree<T>::get_smallest(T &entry) {
    if(is_leaf()) {
        entry = data[0];
        return;
    }
    subset[0]->get_smallest(entry);
}


/**s
 * Searches the children for the biggest item
 * @tparam T Data type
 * @param entry Biggest item
 */
template<typename T>
void BPlusTree<T>::get_biggest(T &entry) {
    if (is_leaf()) {
        entry = data[data_count];
        return;
    }
    subset[child_count-1]->get_biggest(entry);
}

/**
 * Determines what to do after deleting entry
 * @tparam T Data type
 * @param entry Entry
 */
template<class T>
void BPlusTree<T>::loose_remove(const T &entry){
    int i = first_ge(data,data_count,entry);
    bool found = (i<data_count && data[i] == entry);
//    if (found) {
//        if (is_leaf()) {
//            T item;
//            delete_item(data, i, data_count, item);
//        } else {
//            T item;
//            subset[i]->remove_biggest(item);
//            Swap(data[i], item);
//            if (subset[i]->data_count < MINIMUM) {
//                fix_shortage(i);
//            }
//        }
//    } else {
//        if (!is_leaf()) {
//            subset[i]->loose_remove(entry);
//            if (subset[i]->data_count < MINIMUM) {
//                fix_shortage(i);
//            }
//        }
//    }
    if (is_leaf()) {
        if (!found) {
            return;
        } else {
            T item;
            cout<<"deleting item"<<endl;
            delete_item(data, i , data_count, item);
            cout<<"item->"<<item<<endl;
        }
    } else {
        if (!found) {
            subset[i]->loose_remove(entry);
            fix_shortage(i);
        } else {
            subset[i+1]->loose_remove(entry);
            fix_shortage(i+1);
//            assert(i < child_count-1);
        }
    }
}

/**
 * Merges child at index with child at index + 1
 * @tparam T Data type
 * @param i Index
 */
template<class T>
BPlusTree<T>* BPlusTree<T>::merge_with_next_subset(int i){
    T entry;
    delete_item(data,i,data_count,entry);
    if (!is_leaf()) {
        ordered_insert(subset[i]->data, subset[i]->data_count, entry);
    }
    BPlusTree<T>* temp = subset[i+1];
    merge(subset[i]->data,subset[i]->data_count,subset[i+1]->data,subset[i+1]->data_count);
    if(subset[i+1]->child_count>0){
        merge(subset[i]->subset,subset[i]->child_count,subset[i+1]->subset,subset[i+1]->child_count);
    }
    delete temp;
    temp = NULL;
    BPlusTree<T>* ptr;
    delete_item(subset, i+1, child_count, ptr);
    return subset[i];
}

/**
 * Fixes shortage in the children at index
 * @tparam T Data type
 * @param i Index
 */
template<class T>
BPlusTree<T>* BPlusTree<T>::fix_shortage(int i){
    if (i > 0 && subset[i - 1]->data_count > MINIMUM) {
        rotate_right(i - 1);
//        transfer_right(i-1);
    } else if ((i < (child_count-1)) && (subset[i + 1]->data_count > MINIMUM)) {
        rotate_left(i + 1);
//        transfer_left(i+1);
    } else if (i == 0) {
        merge_with_next_subset(i);
    } else {
        merge_with_next_subset(i - 1);
    }
    if (i < child_count - 1 and subset[i+1]->data_count > MINIMUM) {
        transfer_left(i+1);
        return subset[i];
    }
}

/**
 * Removes entry from the balanced tree
 * @tparam T Data type
 * @param entry Entry
 */
template<class T>
void BPlusTree<T>::remove(const T &entry) {
    cout<<"removing"<<endl;
    loose_remove(entry);
    if (data_count < MINIMUM and child_count > 0) {
        cout<<"shrinking"<<endl;
        BPlusTree<T>* temp = subset[0];
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
void BPlusTree<T>::clear_tree() {
    if (!is_leaf()) {
        for (int i = 0; i < child_count; ++i) {
            subset[i]->clear_tree();
        }
    }
    child_count = 0;
    data_count = 0;
    next = NULL;
}

/**
 * Copies from another balanced tree
 * @tparam T Data type
 * @param other Balanced tree to be copied from
 */
template<typename T>
void BPlusTree<T>::copy_tree(const BPlusTree<T> &other, vector<BPlusTree<T> *>& ptr) {
    copy_array(data, other.data, data_count, other.data_count);
    copy_array(subset, other.subset, child_count, other.child_count);
    if (!other.is_leaf()) {
        for (int i = other.child_count-1; i >= 0; --i) {
            subset[i] = new BPlusTree<T>();
            subset[i]->copy_tree(*other.subset[i], ptr);
        }
    } else {
        next = ptr.at(0);
//        cout << *next << endl;
        ptr.pop_back();
        ptr.push_back(other.next);
    }
}

/**
 *
 * @tparam T
 * @param i
 */
template<typename T>
void BPlusTree<T>::transfer_left(int i) {
    if (is_leaf()) {
        rotate_left(i);
    } else {
        cout<<"transfer left"<<endl;
       T item;
       delete_item(subset[i]->data, 0, subset[i]->data_count, item);
       attach_item(subset[i-1]->data, child_count, item);
       data[0] = subset[1]->data[0];
    }
}

/**
 *
 * @tparam T
 * @param i
 */
template<typename T>
void BPlusTree<T>::transfer_right(int i) {
    if (!is_leaf()) {
        rotate_right(i);
    } else {
        cout<<"transfer right"<<endl;
        T item;
        delete_item(subset[i]->data, 0,subset[i]->data_count, item);
        insert_item(subset[i+1]->data, 0, subset[i]->data_count, item);
        subset[i]->data_count++;
        data[i] = subset[i+1]->data[0];
    }
}




#endif //BPLUSTREE_BPLUSTREE_H

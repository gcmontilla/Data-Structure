//
// Created by Gregory Montilla on 5/23/18.
//

#ifndef BPLUSTREE_UTILITY_H
#define BPLUSTREE_UTILITY_H

#include <iostream>
using namespace std;

/**
 * Prints array
 * @tparam T Data type
 * @param data Array to be printed
 * @param n Size
 * @param pos Initial position
 */
template <class T>
void print_array(const T data[], int n, int pos = -1){
    for(int i=0;i<n;i++){
        cout<<"["<<data[i]<<"]";
    }
}

/**
 * Returns the max of two items
 * @tparam T Data type
 * @param a First item
 * @param b Second item
 * @return Max item
 */
template <class T>
T maximal(const T& a, const T& b){
    if(a<b){
        return b;
    }else{
        return a;
    }
}

/**
 * Swaps two items
 * @tparam T Data type
 * @param a First item
 * @param b Second item
 */
template <class T>
void Swap(T& a, T& b){
    T temp = a;
    a=b;
    b=temp;
}

/**
 * Returns the index of the largest item
 * @tparam T Data type
 * @param data Array
 * @param n Array size
 * @return Index
 */
template <class T>
int index_of_maximal(T data[ ], int n){
    int previous = 0;
    int index = 0;
    for(int i=0;i<n;i++){
        if(data[i]>data[previous]){
            previous = index;
        }
    }
    return previous;
}

/**
 * Returns the index of the first item that is greater than the entry
 * @tparam T Data type
 * @param data Array
 * @param n Array Size
 * @param entry Entry
 * @return Index
 */
template <class T>
int first_ge(const T data[ ], int n, const T& entry){
    int index = n;
    for(int i=0;i<n;i++){
        if(data[i] >= entry){
            index=i;
            return index;
        }
    }
    return index;
}

/**
 * Attaches entry to array
 * @tparam T Data type
 * @param data
 * @param n
 * @param entry
 */
template <class T>
void attach_item(T data[ ], int& n, const T& entry){
    data[n] = entry;
    n++;
}

/**
 * Inserts item at index in array
 * @tparam T Data type
 * @param data Array
 * @param i Index
 * @param n Array size
 * @param entry Entry
 */
template <class T>
void insert_item(T data[ ], int i, int& n, T entry){
    for(int j=n;j>i;j--){
        data[j] = data[j-1];
    }
    data[i] = entry;
    n++;
}

/**
 * Inserts item at the proper index in array
 * @tparam T Data type
 * @param data Array
 * @param n Array size
 * @param entry Entry
 */
template <class T>
void ordered_insert(T data[ ], int& n, T entry){
    int temp = first_ge(data,n,entry);
    insert_item(data,temp,n,entry);
}

/**
 * Detaches last item from array and stores in entry
 * @tparam T Data type
 * @param data Array
 * @param n Array size
 * @param entry Entry
 */
template <class T>
void detach_item(T data[ ], int& n, T& entry){
    entry = data[n-1];
    n--;
}

/**
 * Deletes entry from the index
 * @tparam T Data type
 * @param data Array
 * @param i Index
 * @param n Array size
 * @param entry Entry
 */
template <class T>
void delete_item(T data[ ], int i, int& n, T& entry){
    entry = data[i];
    for(int begin = i; begin < n ;begin++){
        data[i] = data[i+1];
    }
    n--;
}

/**
 * Merges two arrays together
 * @tparam T Data type
 * @param data1 Destination array
 * @param n1 Destination array size
 * @param data2 Source array
 * @param n2 Source array size
 */
template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2){
    int end = n2;
    for(int i = 0;i<end;i++){
        data1[n1] = data2[i];
        n1++;
        n2--;
    }
}

/**
 * Splits an array and copies the secod half into another array
 * @tparam T Data type
 * @param data1 Source array
 * @param n1 Source array size
 * @param data2 Destination array
 * @param n2 Destination array size
 */
template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2){
    int size = n1/2;
    int start = n1-size;
    for(int i=0;i<size;i++){
        data2[n2] = data1[start];
        n2++;
        start++;
        n1--;
    }
}

/**
 * Copies one array to another array
 * @tparam T Data type
 * @param dest Destination array
 * @param src Source array
 * @param dest_size Destination array size
 * @param src_size Source array size
 */
template <class T>
void copy_array(T dest[], const T src[],int& dest_size, int src_size){
    for(int i=0;i<src_size;i++){
        dest[i] = src[i];
    }
    dest_size = src_size;
}

/**
 * Checks if item is greater than all elements in the array
 * @tparam T Data type
 * @param data Array
 * @param n Array size
 * @param item Item
 * @return True or False
 */
template <class T>
bool is_gt(const T data[], int n, const T& item){

    for(int i=0;i<n;i++){
        if(data[i]>item){
            return false;
        }
    }
    return true;
}

/**
 * Checks if item is smaller than all element in the array
 * @tparam T Data type
 * @param data Array
 * @param n Array size
 * @param item Item
 * @return True or False
 */
template <class T>
bool is_le(const T data[], int n, const T& item){
    for(int i=0;i<n;i++){
        if(data[i]>=item){
            return true;
        }
    }
    return false;
}

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list);

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme);

#endif //BPLUSTREE_UTILITY_H

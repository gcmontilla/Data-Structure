//
// Created by Gregory Montilla on 3/14/18.
//

#ifndef BINARY_SEARCH_TREE_BST_H
#define BINARY_SEARCH_TREE_BST_H

#include "tree_node.h"

template <class T>
class BST {

public:
    // Constructors
    BST();
    BST(const T* sorted_list, int first, int last);
    BST(const BST<T>& copy_me);

    // Destructors
    ~BST();

    // Operator
    BST<T>&operator = (const BST<T>& rhs);

    // Functions
    void insert(const T& insert_me);
    void erase(const T& target);
    bool search(const T& target, tree_node<T>*& found_ptr);
    void run();

    friend ostream& operator <<(ostream& outs, const BST<T>& tree);
    BST<T>& operator +=(const BST<T>& rhs);

private:
    tree_node<T>* root;
};


/**
 * Constructor for Binary Search Tree
 * @tparam T
 */
template <class T>
BST<T>::BST() {
    root = NULL;
}


/**
 * Constructor for Binary Search Tree that converts a sorted list into a binary tree
 * @tparam T Type of sorted list
 * @param sorted_list Sorted list to be converted into a binary tree
 * @param size Size of sorted list
 */
template <class T>
BST<T>::BST(const T *sorted_list, int first, int last) {
    tree_from_sorted_list(sorted_list, first, last);
}


/**
 * Constructor for Binary Search Tree that copies a binary tree
 * @tparam T Type of binary tree
 * @param copy_me Binary tree to be copied
 */
template <class T>
BST<T>::BST(const BST<T> &copy_me) {
    root = tree_copy(copy_me.root);
}
//
///**
// *
// * @tparam T
// * @param rhs
// * @return
// */
//template <class T>
//BST<T>&operator=(const BST<T> &rhs) {
//}

/**
 * De-constructor for Binary Search Tree
 * @tparam T
 */
template <class T>
BST<T>::~BST() {
    tree_clear(root);
}


/**
 * Inserts an item at the proper place in a binary tree
 * @tparam T Type of item to be inserted
 * @param insert_me Item to be inserted
 */
template <class T>
void BST<T>::insert(const T &insert_me) {
    tree_insert(root, insert_me);
}


/**
 * Searches a binary tree and erases target if it exists within the binary tree
 * @tparam T Type of item to be erased
 * @param target Item to be erased
 */
template <class T>
void BST<T>::erase(const T &target) {
    tree_erase(root, target);
}


/**
 * Searches binary tree for target
 * @tparam T Type of item to be searched for
 * @param target Item to be searched for
 * @param found_ptr Pointer for binary tree
 * @return True if item is in binary tree, false otherwise
 */
template <class T>
bool BST<T>::search(const T &target, tree_node<T> *&found_ptr) {
    tree_search(root, target, found_ptr);
}

/**
 * Testing function
 * @tparam T Type of item for binary tree
 */
template <class T>
void BST<T>::run() {
    tree_node<T>* ptr = NULL;
    char choice;
    cout << "[R]andom  [I]nsert  [E]rase  [C]clear  [S]earch   e[X]it: ";
    cin >> choice;

    while (choice!='x') {
        switch (toupper(choice)) {
            case 'R':
                int i;
                i = rand() % 100 + 1;
                tree_insert(root, i);
                cout << "-- Inserting " << i << endl;
                break;
            case 'E':
                int k;
                cout << "What do you want to erase? ";
                cin >> k;
                tree_remove_max(root, k);
                break;
            case 'I':
                cout << "What do you want to insert: ";
                T j;
                cin >> j;
                tree_insert(root, j);
                break;
            case 'C':
                cout << "clearing tree" << endl;
                tree_clear(root);
                break;
            case 'S':
                cout << "?: ";
                T search;
                cin >> search;
                if (tree_search(root, search, ptr)) {
                    cout << "item is found -> " << ptr->_item<< endl;
                } else {
                    cout << "item is not found" << endl;
                }
                break;
            default:
                cout << "not a valid choice" << endl;
                break;
        }

        tree_print(root);
        cout << "=================================================" << endl;
        cout << "[R]andom  [I]nsert  [E]rase   [C]clear  [S]earch   e[X]it: ";
        cin >> choice;
    }
    cout << "exiting program" << endl;
}

template <class T>
ostream& operator << (ostream &outs, const BST<T> &tree) {
    tree_print(tree.root);
    return outs;
}

template <class T>
BST<T>& BST<T>::operator+=(const BST<T> &rhs) {
    tree_add(root, rhs.root);
}

template <class T>
BST<T>& BST<T>::operator=(const BST<T> &rhs) {
    tree_clear(root);
    tree_copy(rhs.root);
}


#endif //BINARY_SEARCH_TREE_BST_H

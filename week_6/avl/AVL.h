//
// Created by Gregory Montilla on 3/28/18.
//

#ifndef AVL_AVL_H
#define AVL_AVL_H

#include "tree_node.h"

template <typename T>
class AVL {
public:
    AVL();
    AVL(const T* sorted_list, int first, int last);

    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    AVL(const AVL<T>& copy_me);
    AVL<T>& operator =(const AVL<T>& rhs);
    ~AVL();

    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    void insert(const T& insert_me);
    void erase(const T& target);
    bool search(const T& target, tree_node<T>* & found_ptr);

    friend ostream& operator <<(ostream& outs, const AVL<T>& tree);
    AVL<T>& operator +=(const AVL<T>& rhs);

    void run();

    private:
    tree_node<T>* root;
};

template <typename T>
AVL<T>::AVL() {
    root= nullptr;
}

template <typename T>
AVL<T>::AVL(const T *sorted_list, int first, int last) {
    tree_from_sorted_list(sorted_list, first, last);
}

template <typename T>
AVL<T>::AVL(const AVL<T> &copy_me) {
    root = tree_copy(copy_me.root);
}

template <typename T>
AVL<T>::~AVL() {
    tree_clear(root);
}

template <typename T>
void AVL<T>::insert(const T &insert_me) {
    tree_insert(root, insert_me);
}

template <typename T>
void AVL<T>::erase(const T &target) {
    tree_erase(root, target);
}

template <typename T>
bool AVL<T>::search(const T &target, tree_node<T> *&found_ptr) {
    tree_search(root, target, found_ptr);
}

template <typename T>
ostream& operator << (ostream &outs, const AVL<T> &tree) {
    tree_print(tree.root);
    return outs;
}

template <typename T>
AVL<T>& AVL<T>::operator+=(const AVL<T> &rhs) {
    tree_add(root, rhs.root);
}

template <typename T>
AVL<T>& AVL<T>::operator=(const AVL<T> &rhs) {
    tree_clear(root);
    root = tree_copy(rhs.root);
}

/**
 * Testing function
 * @tparam T Type of item for binary tree
 */
template <class T>
void AVL<T>::run() {
    tree_node<T>* ptr = NULL;
    char choice;
    cout << "[R]andom  [I]nsert  [C]clear  [S]earch   [E]rase   e[X]it: ";
    cin >> choice;

    while (choice!='x') {
        switch (toupper(choice)) {
            case 'R':
                int i;
                i = rand() % 100 + 1;
                tree_insert(root, i);
                cout << "-- Inserting " << i << endl;
                break;
            case 'I':
                cout << "What do you want to insert: ";
                T j;
                cin >> j;
                tree_insert(root, j);
                break;
            case 'E':
                cout << "What do you want to erase: ";
                T l;
                cin >> l;
                tree_erase(root, l);
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
            case 'N':
                int a;
                tree_remove_max(root, a);
                break;
            default:
                cout << "not a valid choice" << endl;
                break;
        }

        tree_print_debug(root);
        cout << "=================================================" << endl;
        cout << "[R]andom  [I]nsert  [C]clear  [E]rase  [S]earch   e[X]it: ";
        cin >> choice;
    }
    cout << "exiting program" << endl;
}
#endif //AVL_AVL_H

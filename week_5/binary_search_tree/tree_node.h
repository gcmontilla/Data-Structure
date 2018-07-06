//
// Created by Gregory Montilla on 3/14/18.
//

#ifndef BINARY_SEARCH_TREE_TREE_NODE_H
#define BINARY_SEARCH_TREE_TREE_NODE_H

#include <clocale>
#include <iostream>
#include <iomanip>

using namespace std;

template <typename T>
struct tree_node {
    // Member variables
    T _item;                // Value of node
    tree_node<T> *_left;    // Pointer to the left child
    tree_node<T> *_right;   // Pointer to the right child
    int _height;            // Height of node


    // Functions
    /**
     *
     * @return
     */
    int balance_factor() {
        return (_left->_height - _right->_height);
    }


    /**
     * Returns height
     * @return Height
     */
    int height() {
        int left, right;
        if (!_left)
            left = -1;
        else
            left = _left->_height;

        if (!_right)
            right = -1;
        else
            right = _right->_height;

        return (1 + max(left, right));
    }


    /**
     *
     * @return
     */
    int update_height() {
        _height = height();
        return _height;
    }


    /**
     * Constructor for a tree node with defaults for left and right set to null
     * @param item Value of item
     * @param left NULL
     * @param right NULL
     */
    tree_node(T item = T(), tree_node *left = NULL, tree_node *right = NULL) : _item(item), _left(left), _right(right) {
        _height = 0;
    }


    /**
     *
     * @param outs
     * @param t_node
     * @return
     */
    friend ostream& operator << (ostream& outs, const tree_node<T>& t_node) {
        // tree_print(t_node);
        return outs;
    }
};

template <typename T>
void tree_remove_max(tree_node<T>* &root, T& max_value);

/**
 * Inserts item into tree
 * @tparam T Type of item to be inserted
 * @param root Pointer to binary tree
 * @param insert_me Item to be inserted
 */
template <typename T>
void tree_insert(tree_node<T>* &root, const T& insert_me) {
    if(!root) {
        root = new tree_node<T>(insert_me);
    }
    if(root->_item == insert_me) {
        return;
    }
    if(insert_me < root->_item) {
        tree_insert(root->_left, insert_me);
    } else {
        tree_insert(root->_right, insert_me);
    }
    root->update_height();
}


/**
 * Searches through binary tree for item
 * @tparam T Type of item to be searched for
 * @param root Pointer to binary tree
 * @param target Item to be searched for
 * @return True if item is found, false otherwise
 */
template <typename T>
tree_node<T>* tree_search(tree_node<T>* root, const T& target) {
    if (!root)
        return NULL;
    if (root->_item ==  target) {
        return root;
    }

    if (target < root->_item) {
        return tree_search(root->_left, target);
    } else {
        return tree_search(root->_right, target);
    }
}


/**
 * Searches through binary tree for item
 * @tparam T Data type of binary tree
 * @param root Pointer to root of binary tree
 * @param target Item to be searched for
 * @param found_ptr
 * @return True if item is found, false otherwise
 */
template <typename T>
bool tree_search(tree_node<T>* root, const T& target, tree_node<T>* &found_ptr){
    if (!root) {
        return false;
    }
    if (root->_item == target) {
        found_ptr = root;
        return true;
    }

    if (target < root->_item) {
        return tree_search(root->_left, target, found_ptr);
    } else {
        return tree_search(root->_right, target, found_ptr);
    };
}


/**
 * Prints all nodes in binary tree
 * @tparam T Data type of binary tree
 * @param root Pointer to root of binary tree
 * @param level Levels of binary tree
 * @param outs
 */
template<typename T>
void tree_print(tree_node<T>* root, int level=0, p){
    if (!root) {
        return;
    }
    tree_print(root->_right, level + 1);
    cout << setw(4 * level) << root->_item << endl;
    tree_print(root->_left, level + 1);
}


/**
 * Prints information of specific node
 * @tparam T Data type of binary tree
 * @param root Pointer to root of binary tree
 * @param level Levels of binary tree
 * @param outs
 */
template<typename T>
void tree_print_debug(tree_node<T>* root, int level=0, ostream& outs=cout) {
    if(!root) {
        return;
    }
    tree_print_debug(root->_right, level + 1);
    cout << setw(10 * level) << "item: " << root->_item;
    cout << " height: " << root->_height << endl;
    tree_print_debug(root->_left, level + 1);
}


/**
 * Clears all the nodes of the binary tree
 * @tparam T Data type of binary tree
 * @param root Pointer to root of binary tree
 */
template <typename T>
void tree_clear(tree_node<T>* &root) {
    if (!root) {
        return;
    } else  {
        tree_clear(root->_left);
        tree_clear(root->_right);
        delete root;
        root = NULL;
    }
}


/**
 * Erases specific target from binary tree
 * @tparam T Data type of binary tree
 * @param root Pointer to root of binary tree
 * @param target Item to be deleted from binary tree
 * @return True if item was deleted, false otherwise
 */
template <typename T>
bool tree_erase(tree_node<T>*& root, const T& target) {
    if (!root) {
        return false;
    }
    if (root->_item == target) {
        if (root->_left) {
            T max;
            tree_remove_max(root->_left, max);
            root->_item = max;
            return tree_erase(root, max);
        } else {
            delete root;
            root = NULL;
        }
        return true;
    }

    if (target < root->_item) {
        return tree_erase(root->_left, target);
    }
    if (target > root->_item) {
        return tree_erase(root->_right, target);
    }

    root->update_height();
}


/**
 * Erases the rightmost node from the tree and stores it in variable
 * @tparam T Data type of binary tree
 * @param root Pointer to root of binary tree
 * @param max_value Variable to store deleted node
 */
template <typename T>
void tree_remove_max(tree_node<T>* &root, T& max_value) {
    if (!root)
        return;
    if (root->_right) {
        tree_remove_max(root->_right, max_value);
    } else {
        max_value = root->_item;
        delete root;
        root = nullptr;
//        tree_node<T> *ptr = root;
//        root = root->_left;
//        ptr->_left = NULL;
//        ptr->_right = NULL;
//        delete ptr;

        root->update_height();
    }
}


/**
 * Returns copy of binary tree pointed to by root
 * @tparam T Data type of binary tree
 * @param root Pointer to root of binary tree
 * @return Copy of binary tree
 */
template <typename T>
tree_node<T>* tree_copy(tree_node<T>* root) {
    if (!root)
        return NULL;

    tree_node<T>* treeNode = NULL;

    tree_insert(treeNode, root->_item);
    treeNode->_left = tree_copy(root->_left);
    treeNode->_right = tree_copy(root->_right);

    return treeNode;
}


/**
 * Adds tree source to destination
 * @tparam T Data type of binary tree
 * @param dest Where the binary tree will be added
 * @param src Source of what will be added to the binary tree
 */
template <typename T>
void tree_add(tree_node<T>* & dest, const tree_node<T>* src) {
    if (!src)
        return;

    tree_insert(dest, src->_item);

    if (src->_left)
        tree_add(dest, src->_left);

    if (src->_right)
        tree_add(dest, src->_right);
}


/**
 * Converts a sorted array into a binary tree
 * @tparam T Data type of binary tree
 * @param a Pointer to an array
 * @param size Size of the array
 * @return Returns binary tree of sorted array
 */
template <typename T>
tree_node<T>* tree_from_sorted_list(T array[], int first, int last) {
    if (first > last)
        return nullptr;

    tree_node<T> *tree_node = NULL;

    int mid = (first+last)/2;

    tree_insert(tree_node, array[mid]);

    tree_node->_left = tree_from_sorted_list(array, first, mid-1);
    tree_node->_right = tree_from_sorted_list(array, mid+1, last);

    tree_node->update_height();

    return tree_node;
}


#endif //BINARY_SEARCH_TREE_TREE_NODE_H

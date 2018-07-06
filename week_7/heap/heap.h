//
// Created by Gregory Montilla on 4/3/18.
//

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

template <typename T>
class Heap {
public:
    Heap();
    void insert(const T& insert_me);
    T pop();
    void test();

    int size() const {
        return int(tree.size()-1);
    }
    friend ostream& operator << (ostream& outs, const Heap<T>& print_me) {
        print_me.print_tree();
        return outs;
    }
    void run();
private:
    vector<T> tree;
    void print_tree(ostream& outs = cout) const;
    void print_tree(int root, int level = 0, ostream& outs = cout) const;

    bool is_leaf(int i) const;
    unsigned int parent_index(int i) const;
    int left_child_index(int i) const;
    int right_child_index(int i) const;
    int big_child_index(int i) const;
    void swap_with_parent(int i);
    void swap_with_child(int i);
};

/**
 * Constructor for Heap class
 * @tparam T Datatype
 */
template <typename T>
Heap<T>::Heap() {
    srand(time(0));
}

/**
 * Inserts a value into the heap structure
 * @tparam T Datatype
 * @param insert_me Value
 */
template <typename T>
void Heap<T>::insert(const T &insert_me) {
    tree.push_back(insert_me);

    int parent = parent_index(size());
    if (tree[size()] > tree[parent]) {
        swap_with_parent(size());
    }
}

/**
 * Swaps parent with biggest of two children
 * @tparam T Datatype
 * @param i Index
 */
template <typename T>
void Heap<T>::swap_with_parent(int i) {
    if (i == -1) {
        return;
    }

    int parent = parent_index(i);

    if (tree[i] > tree[parent]) {
       T temp = tree[i];
        tree[i] = tree[parent];
        tree[parent] = temp;
        swap_with_parent(parent);
    }
}

template <typename T>
void Heap<T>::swap_with_child(int i) {
    if (i == -1) {
        return;
    }

    int left = left_child_index(i);
    int right = right_child_index(i);

    if (left != -1) {
        if (tree[left] > tree[i]) {
            T temp = tree[left];
            tree[left] = tree[i];
            tree[i] = temp;
            swap_with_child(left);
        }
    }

    if (right != -1) {
        if (tree[right] > tree[i]) {
            T temp = tree[right];
            tree[right] = tree[i];
            tree[i] = temp;
            swap_with_child(right);
        }
    }
}

/**
 * Checks if item at index is a leaf
 * @tparam T Datatype
 * @param i Index
 * @return True if leaf, false if else
 */
template <typename T>
bool Heap<T>::is_leaf(int i) const {
     return (right_child_index(i) == -1 && left_child_index(i) == -1);
}

/**
 * Pops the first item and reconfigures the heaps structure accordingly
 * @tparam T Datatype
 * @return Reconfigured heap structure
 */
template <typename T>
T Heap<T>::pop() {
    if (size() != -1) {
        tree[0] = tree[tree.size() - 1];
        tree.pop_back();

        int left = left_child_index(0);
        int right = right_child_index(0);

        if (tree[left] > tree[0]) {
            swap_with_child(0);
        }

        if (tree[right] > tree[0]) {
            swap_with_child(0);
        }
    }
}

/**
 * Returns the parent index
 * @tparam T Datatype
 * @param i Index
 * @return Parent index of given index
 */
template <typename T>
unsigned int Heap<T>::parent_index(int i) const {
    return (i - 1) / 2;
}

/**
 * Returns the index of the left child
 * @tparam T Datatype
 * @param i Index
 * @return Index of left child, -1 if it has no left child
 */
template <typename T>
int Heap<T>::left_child_index(int i) const {
    int index = (2 * i + 1 >= tree.size() ? -1 : 2 * i + 1);
    return index;
}

/**
 * Returns the index of the right child
 * @tparam T Datatype
 * @param i Index
 * @return Index of the right child, -1 if it has no right child
 */
template <typename T>
int Heap<T>::right_child_index(int i) const {
    int index = (2 * i + 2 >= tree.size() ? -1 : 2 * i + 2);
    return index;
}

/**
 * Returns the index of the largest of the two children
 * @tparam T Dataype
 * @param i Index
 * @return Index of the largest of the two children
 */
template <typename T>
int Heap<T>::big_child_index(int i) const {
    int left = left_child_index(i);
    int right = right_child_index(i);

    (tree[left] > tree[right] ? left: right);
}

template <typename T>
void Heap<T>::print_tree(ostream &outs) const {
    print_tree(0);
}

/**
 * Prints heap in binary tree form
 * @tparam T Data type
 * @param root Initial index
 * @param level Level
 * @param outs Binary tree
 */
template <typename T>
void Heap<T>::print_tree(int root, int level, ostream &outs) const {
    if (size() == -1) {
        cout << "empty" << endl;
    } else {
        if (root == -1) {
            return;
        }

        print_tree(right_child_index(root), level + 1);
        cout << setw(10 * level) << tree[root] << endl;
        print_tree(left_child_index(root), level + 1);
    }
}

template <typename T>
ostream& operator << (ostream& outs, const Heap<T>& print_me) {
    print_me.print_tree();
    return outs;
}

template <typename T>
void Heap<T>::run() {
    char input;
    cout << "insert random pop exit" << endl;
    cin >> input;
    while (input != 'x') {
        switch (input) {
            case 'i':
                T i;
                cin >> i;
                insert(i);
                break;
            case 'r':
                int random;
                random = rand() % 100 + 1;
                insert(random);
                break;
            case 'p':
                pop();
                break;
            default:
                break;
        }
        print_tree(0);
        cin >> input;
    }
    cout << "exiting program" << endl;
}

template <typename T>
void Heap<T>::test() {
    for (int i = 0; i < 10; ++i) {
        int random =  rand() % 25 + 1;
        insert(random);
    }

    while (size() != -1) {
        print_tree(0);
        pop();
        cout << "=======" << endl;
    }
}

#endif //HEAP_HEAP_H

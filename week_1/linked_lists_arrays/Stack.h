//
// Created by Gregory Montilla on 2/22/18.
//

#ifndef LINKED_LISTS_ARRAYS_STACK_H
#define LINKED_LISTS_ARRAYS_STACK_H

template <class T>
class Stack {
public:
    Stack();
    void push (T item);
    T pop();
    T top();
    bool empty();
    void copy(Stack& stack);
    T value(int i);
    T print();

private:
    T stack[10];
    int position;
};

template <class T>
Stack<T>::Stack() {
    position = 0;
}

template <class T>
bool Stack<T>::empty() {
    return (position == 0);
}

template <class T>
T Stack<T>::pop() {
    int temp = position-1;
    position--;
    return stack[temp];
}

template <class T>
T Stack<T>::top() {
    return stack[position];
}

template <class T>
void Stack<T>::push(T item) {
    stack[position] = item;
    position++;
}

template <class T>
void Stack<T>::copy(Stack& s) {
    for (int i = 0; i < position; i++) {
        s.push(stack[i]);
    }
}

template <class T>
T Stack<T>::value(int i) {
    return stack[i];
}

template <class T>
T Stack<T>::print() {
    for (int i = 0; i < position; ++i) {
        std::cout << "[" << value(i) << "] -> ";
    }
    std::cout << "|||" << std::endl;
}

#endif //LINKED_LISTS_ARRAYS_STACK_H

#include <iostream>
#include "heap.h"
#include "pqueue.h"

int Random(int low, int hi);

int main() {
    Heap<int> h;
    h.insert(18);
    h.insert(23);
    h.insert(6);
    h.insert(10);
    h.insert(2);
    h.insert(3);
    h.insert(8);
    h.insert(19);
    h.insert(27);
    h.insert(56);
    h.insert(99);
    h.insert(102);
    cout << h;
    while (h.size() != -1) {
        h.pop();
        cout << h;
    }

//    PQueue<int> pq;
//    for (int i = 0; i<100; i++){
//        pq.insert(Random(1, 50), Random(1, 10));
//    }
//    cout << pq;
//    for (int j = 0; j < 100; ++j) {
//        pq.Pop();
//        cout << pq;
//    }
}

int Random(int low, int hi) {
    return rand() % hi + low;
}
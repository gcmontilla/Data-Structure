#include <iostream>
#include "Stack.h"
#include "Queue.h"

using namespace std;

int main() {
    Stack<int> s;
    Stack<int> s2;
    Queue<int> q;
    Queue<int> q2;

    for (int i = 0; i < 10; i++) {
        s.push(i);
        q.push(i);
    }

    s.copy(s2);
    q.copy(q2);

    cout << "STACK" << endl;
    cout << "S :";
    s.print();
    cout << "S2:";
    s2.print();
    while (!s2.empty()) {
        cout << "S2:";
        s2.print();
        s2.pop();
    }
    cout << "COPY S INTO S2" << endl;
    cout << "S :";
    s.print();
    s.copy(s2);
    cout << "S2:";
    s2.print();


    cout << endl << endl;
    cout << "QUEUE" << endl;
    cout << "Q :";
    q.print();
    cout << "Q2:";
    q2.print();
    while (!q2.empty()) {
        cout << "Q :";
        q2.print();
        q2.pop();
    }
    cout << "COPY Q INTO Q2" << endl;
    cout << "Q :";
    q.print();
    q.copy(q2);
    cout << "Q2:";
    q2.print();

}
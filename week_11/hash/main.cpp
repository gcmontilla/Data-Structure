#include <iostream>
#include "HashTable.h"
#include "DoubleHashTable.h"
#include "ChainedHashTable.h"

int main() {
    srand(time(0));
    DoubleHashTable<record<int>, int> doubleHashTable;
    doubleHashTable.test();

    cout << "Chained Hash Table" << endl;
    ChainedHashTable<record<int>> h;
    for (int i = 0; i < 10; i++)
        h.insert_item(record(rand() % 1000 + 1, 5));

    h.display_hash();
    h.insert_item(record(1,20));
    cout<<endl<<"INSERTING 1:20"<<endl;
    h.display_hash();
    h.delete_item(1);
    cout<<endl<<"DELETING 1"<<endl;
    h.display_hash();

    return 0;
}
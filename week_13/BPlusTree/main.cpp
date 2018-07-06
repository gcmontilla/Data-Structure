#include <iostream>
#include "BPlusTree.h"
#include "mmap.h"
#include "map.h"
int main() {
    srand(time(NULL));
//    vector<Map <string, int>> v;
    MMap <string, long> mmap;
//    MMap <long, long> m;
    for (int i = 0; i < 20; ++i) {
        mmap.insert("test", rand()%100+1);
    }
    cout << mmap;
//    m = mmap;r
//    mmap.clear();
//    cout << endl << "cleared" <<endl;
//    cout << mmap;
//    cout << m;

//    BPlusTree<int> b;
//    BPlusTree<int> c;
//    for (int j = 0; j < 10; ++j) {
//        b.insert(1);
//    }
//    cout << b;
//    c = b;
//    cout <<c;


//    MMap<string, int> mMap;
//    mMap.insert("hello", 5);
//    v.push_back(mMap);

}
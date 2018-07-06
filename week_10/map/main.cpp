#include <iostream>
#include "map.h"
#include "b_tree.h"


int main() {
//    Map<string, string> m;
//    string name[] = {"iron man", "black panther", "starlord", "dr. strange", "hulk", "thor", "thanos", "black widow",
//                     "vision", "scarlett witch", "gamorah", "groot", "drax", "spider man", "daredevil" , "wolverine",
//                     "aquaman", "green lantern", "captain america"};
//    for (int i = 0; i < 19; ++i) {
//        int c = rand() % 19;
//        m.insert(name[i], name[c]);
//    }
//    cout<<m<<"=============="<<endl;
//    m["iron man"] = "tony stark";
//    cout<<m<<"=============="<<endl;
//    m.clear();
//    cout<<m<<"=============="<<endl;
//    m["TEST"];
//    cout<<m<<"=============="<<endl;
//    m["TEST"] = "I was inserted";
//    cout<<m<<"=============="<<endl;
    BTree<int> b;
    BTree<int> c;
    for (int i = 0; i < 10; ++i) {
        b.insert(i);
    }
    c = b;
    cout << "=====B=====" << endl << b <<endl;
    cout << "=====C=====" << endl << c <<endl;
}
#include <iostream>
#include "b_tree.h"
#include <cmath>

int Random(int lo, int hi);
void test_bplustree_auto(int tree_size=500, int how_many=500, bool report=false);
bool test_bplustree_auto(int how_many, bool report=true);

int main(int argc, char *argv[])
{
    srand(time(0));
//
//    test_bplustree_auto(1000,100,false);

    b_tree<int> bTree;

    for (int i = 0; i < 20; ++i) {
        bTree.insert(i);
    }
    cout<<bTree<<endl;
    bTree.clear_tree();
    cout<<"====="<<endl;
    cout<<bTree<<endl;
    bTree.insert(5);
    cout<<bTree<<endl;
    b_tree<int> b;
    b = bTree;
    cout<<b;

    return 0;
}

void test_bplustree_auto(int tree_size, int how_many, bool report){
    bool verified = true;
    for (int i = 0; i< how_many; i++){
        if (report){
            cout<<"*********************************************************"<<endl;
            cout<<" T E S T:    "<<i<<endl;
            cout<<"*********************************************************"<<endl;
        }
        if (!test_bplustree_auto(tree_size,report)){
            cout<<"T E S T :   ["<<i<<"]    F A I L E D ! ! !"<<endl;
            verified = false;
            return;
        }

    }
    cout<<"**************************************************************************"<<endl;
    cout<<"**************************************************************************"<<endl;
    cout<<"             E N D     T E S T: "<<how_many<<" tests of "<<tree_size<<" items: ";
    cout<<(verified?"VERIFIED": "VERIFICATION FAILED")<<endl;
    cout<<"**************************************************************************"<<endl;
    cout<<"**************************************************************************"<<endl;

}

bool test_bplustree_auto(int how_many, bool report){
    const int MAX = 10000;
    assert(how_many < MAX);
    b_tree<int> bpt;
    int a[MAX];
    int original[MAX];
    int deleted_list[MAX];

    int original_size = rand() % 100 + 1;
    int size;
    int deleted_size = 0;

    //fill a[ ]
    for (int i= 0; i< how_many; i++){
        a[i] = i;
    }
    //shuffle a[ ]: Put this in a function!
    for (int i = 0; i< how_many; i++){
        int from = Random(0, how_many-1);
        int to = Random(0, how_many -1);
        int temp = a[to];
        a[to] = a[from];
        a [from] = temp;
    }
    //copy  a[ ] -> original[ ]:

    copy_array(original, a, how_many, original_size);

    size = how_many;
    original_size = how_many;
    for (int i=0; i<size; i++){
        bpt.insert(a[i]);

    }
    if (report){
        cout<<"========================================================"<<endl;
        cout<<"  "<<endl;
        cout<<"========================================================"<<endl;
        cout<< bpt << endl << endl;
    }

    for (int i= 0; i<how_many; i++){
        int r = Random(0, how_many - i - 1);
        if (report){
            cout<<"========================================================"<<endl;
            cout<<bpt<<endl;
            cout<<". . . . . . . . . . . . . . . . . . . . . . . . . . . . "<<endl;
            cout<<"deleted: "; print_array(deleted_list, deleted_size);
            cout<<"   from: "; print_array(original, original_size);
            cout<<endl;
            cout<<"  REMOVING ["<<a[r]<<"]"<<endl;
            cout<<"========================================================"<<endl;
        }
        bpt.remove(a[r]);


        delete_item(a, r, size, deleted_list[deleted_size++]);
//        if (!bpt.is_valid()){
//            cout<<setw(6)<<i<<" I N V A L I D   T R E E"<<endl;
//            cout<<"Original Array: "; print_array(original, original_size);
//            cout<<"Deleted Items : "; print_array(deleted_list, deleted_size);
//            cout<<endl<<endl<<bpt<<endl<<endl;
//            return false;
//        }

    }
    if (report) cout<<" V A L I D    T R E E"<<endl;

    return true;
}


int Random(int lo, int hi)
{
    int r = rand()%(hi-lo+1)+lo;

    return r;
}
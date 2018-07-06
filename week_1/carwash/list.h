////
//// Created by Gregory Montilla on 2/21/18.
////
//
//#ifndef CARWASH_LIST_H
//#define CARWASH_LIST_H
//
//#include <iostream>
//using namespace std;
//
//template <class T>
//struct node{
//    T _item;
//    node<T>* _next;
//    node(const T& item = T(), node<T>* next = NULL):_item(item), _next(next){}
//    friend ostream& operator << (ostream& outs, const node<T>& print_me){
//        outs<<"["<<print_me._item<<"]->";
//        return outs;
//    }
//};
//
////initializes head to NULL
//template <class T>
//node<T>* init_head(node<T>* &head) {
//    head = NULL;
//}
//
////deletes all the nodes in the list
//template<class T>
//void delete_all(node<T>*&head);
//
////true if head is NULL, false otherwise.
//template <class T>
//bool empty(const node<T>* head) {
//    return (head == NULL);
//}
//
////makes a copy of the list, returns a pointer to the last node:
//template <class T>
//node<T>* copy_list(const node<T>* head, node<T>* & cpy);
//
////insert at the beginning of the list:
//template <class T>
//node<T>* insert_head(node<T>* &head, T item);
//
////insert_after: if after is NULL, inserts at head
//template <class T>
//node<T>* insert_after(node<T>* &head, node<T>* after, const T& item);
//
////delete the node at the head of the list, reuturn the item:
//template <class T>
//T delete_head(node<T>* &head);
//
////print the list and return outs
//template<class T>
//ostream& print_list(const node<T>* head, ostream& outs=cout);
//
//#endif //CARWASH_LIST_H

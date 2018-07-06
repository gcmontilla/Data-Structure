#ifndef UTILITIES_H
#define UTILITIES_H
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;
void open_fileRW(fstream& f, const char filename[]) throw(char*);
void open_fileW(fstream& f, const char filename[]);
bool file_exists(const char filename[]);
bool read_info(const char filename[], vector<string>& v);
bool write_info(const char filename[], const vector<string> &v);



template<class T>
void show_vector( vector<T>& v){
    for (typename vector<T>::iterator it = v.begin(); it!=v.end(); it++){
        cout<<*it<<"|";
    }
    cout<<endl;

}

// duplicates i bplustree:arrayfunc.h
//template <class T>
//ostream& operator <<(ostream& outs,  const vector<T>& v){
//    for (typename vector<T>::const_iterator it = v.begin(); it!=v.end(); it++){
//        outs<<*it<<"|";
//    }
//    return outs;
//}


//void show_vector(vector<string>& v);



#endif // UTILITIES_H

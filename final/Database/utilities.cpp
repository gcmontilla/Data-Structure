#include "utilities.h"
#include <iostream>
using namespace std;

void open_fileRW(fstream& f, const char filename[]) throw (char*){
    const bool debug = true;
    //opening a nonexistent file for in|out|app causes a fail()
    //  so, if the file does not exist, create it by opening it for
    //  output:
    if (!file_exists(filename)){
        f.open(filename, std::fstream::out|std::fstream::binary);
        if (f.fail()){
            cout<<"file open (RW) failed: with out|"<<filename<<"]"<<endl;
            throw("file RW failed");
        }
        else{
            if (false){
                cout<<"open_fileRW: file created successfully: "<<filename<<endl;
            }
        }
    }
    else{
        f.open (filename,
            std::fstream::in | std::fstream::out| std::fstream::binary );
        if (f.fail()){
            cout<<"file open (RW) failed. ["<<filename<<"]"<<endl;
            throw("file failed to open.");
        }
    }

}
void open_fileW(fstream& f, const char filename[]){
    f.open (filename,
            std::fstream::out| std::fstream::binary );
    if (f.fail()){
        cout<<"file open (W) failed: ["<<filename<<"]"<<endl;
        throw("file failed to open.");
    }

}
bool file_exists(const char filename[]){
    const bool debug = true;
    fstream ff;
    ff.open (filename,
        std::fstream::in | std::fstream::binary );
    if (ff.fail()){
//        if (debug) cout<<filename<<" does not exist!"<<endl;
        return false;
    }
//    if (debug) cout<<"Loaded "<<filename<<endl;
    return true;
}

bool read_info(const char filename[], vector<string>& v){
    ifstream f;
    f.open(filename);
    if (f.fail()){
        return false;
    }
    string s;
    getline(f, s);
    while (!f.eof()){
        v.push_back(s);
        getline(f, s);
        cout << s << endl;
    }
    f.close();
    return true;
}
bool write_info(const char filename[], const vector<string>& v){
    ofstream f;
    f.open(filename);
    if (f.fail()) return false;
    for (int i= 0; i<v.size(); i++){
        f<<v[i]<<endl;
    }
    f.close();
    return true;
}



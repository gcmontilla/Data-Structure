#include <iostream>
#include <iomanip>
#include "Token.h"
#include "FTokenizer.cpp">

using namespace std;

void test_f_tokenize_simple();

int main() {
    test_f_tokenize_simple();
    return 0;
}


void test_f_tokenize_simple(){
    char file[] = "solitude.txt";
    Token t;
    FTokenizer ftk(file);
    ftk>>t;
    int token_count = 0;
    while (ftk.more()) {
        if (t.type_string()=="WORD" ){
            token_count++;
//            cout<<left<<setw(10)<<token_count
//                <<setw(3)<<left<<":"<<setw(25)<<left<<t.token_str()
//                <<t.type_string()<<endl;
        }
//        cout << t.token_str() << " " << t.type_string() << endl;
        ftk>>t;

    }

    cout<<"Tokens Found: "<<token_count<<endl;
    cout<<"=========="<<endl;

}

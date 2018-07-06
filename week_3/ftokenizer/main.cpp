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
    int i = 0;
    Token t;
    const char* path = "solitude.txt";
    FTokenizer ftk(path);
    ftk >> t;
    int token_count = 0;
    while (ftk.more()){
        if (t.type_string()=="ALPHA" ){
            token_count++;
            if (i < 100) {
                cout << setw(10) << right << token_count
                     << setw(3) << left << ":" << setw(25) << left << t.token_str()
                     << t.type_string() << setw(20) << right << t.token_str().length() << endl;
                ++i;
            }
        }
        ftk >> t;
    }
    cout << "Tokens Found: " << token_count << endl;
}
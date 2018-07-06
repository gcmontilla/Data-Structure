#include <iostream>
#include <iomanip>
#include <fstream>
#include "STokenizer.cpp"

using namespace std;

int main() {
    char temp[10];
    char t[] = "ello my namé";

    STokenizer sTokenizer(t);
    while (!sTokenizer.done()) {
        Token t;
        sTokenizer >> t;
        cout << t.token_str() << endl;
        t = Token();
    }

}
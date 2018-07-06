#include <iostream>
#include <iomanip>
#include "STokenizer.cpp"
#include "Token.cpp"

using namespace std;

int main() {
    char alpha[] = "it was the night of october 17th. pi was still 3.14.";
    char test[] = "123. 12 3 dsfkah pmfi-/N 10-\nAEF 24 \t qo2 39 u 213 t!>< v 12.23 ! f, .";
    char x[] = "123. u7t..";
    STokenizer s(x);
//    s.print();
    Token t;
    while (!s.done()) {
//        string token;
//        if (s.get_token(START_DOUBLE, token)) {
//            t.set(DIGIT, token);
//        } else if (s.get_token(START_ALPHA, token)) {
//            t.set(WORD, token);
//        } else if (s.get_token(START_SPACES, token)) {
//            t.set(SPACE, token);
//        } else if (s.get_token(START_OPERATORS, token)) {
//            t.set(PUNCTUATION, token);
//        }
        s>>t;
        cout<<left<<setw(8)<<t.type_string()<<t<<endl;
        t = Token();
    }

}
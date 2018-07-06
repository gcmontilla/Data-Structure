//
// Created by Gregory Montilla on 2/28/18.
//

#ifndef TOKENIZER_TOKEN_H
#define TOKENIZER_TOKEN_H

#include <iostream>
#include <iomanip>

using namespace std;

class Token {

public:
    Token() {

    }
    Token(string str, int type) {
        _token = str;
        _type = type;
    }

    friend ostream& operator << (ostream &outs, const Token &t) {
        outs << "|" << t._token << "|";
        return outs;

    }

    void set(int type, string str) {
        _token = str;
        _type = type;
    }

    string type_string() {
        switch (_type) {
            case 0:
                return "DIGIT";
            case 1:
                return "ALPHA";
            case 2:
                return "SPACE";
            case 3:
                return "PUNC.";
            default:
                return "UNKNOWN";
        }
    }

    int type() {
        return _type;
    }
    string token_str() {
        string str = "|" + _token + "|";
        return str;
    }

private:
    string _token;
    int _type;
};


#endif //TOKENIZER_TOKEN_H

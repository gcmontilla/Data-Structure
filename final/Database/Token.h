//
// Created by Gregory Montilla on 5/29/18.
//

#ifndef DATABASE_TOKEN_H
#define DATABASE_TOKEN_H

#include <iostream>
#include <iomanip>

using namespace std;

class Token {

public:
    Token() {}

    Token(string str, int type) {
        _token = str;
        _type = type;
    }

    friend ostream& operator << (ostream &outs, const Token &t) {
        outs << t._token;
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
                return "WORD";
            case 2:
                return "SPACE";
            case 3:
                return "PUNC.";
            case 4:
                return "SPECIAL";
            default:
                return "UNKNOWN";
        }
    }

    int type() {
        return _type;
    }

    string token_str() {
        return _token;
    }

private:
    string _token;
    int _type;
};


#endif //DATABASE_TOKEN_H

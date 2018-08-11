//
// Created by Gregory Montilla on 3/5/18.
//

#include "FTokenizer.h"

FTokenizer::FTokenizer(char *file) {
    _blockPos = 0;
    _f.open(file);
    _more = true;

    if (_f.fail()) {
        cout << "FAILURE" << endl;
    }

    get_new_block();

//    if (debug) {
//        cout << "CONSTRUCTOR -> NEW BLOCK" << endl;
//    }
}

FTokenizer& operator>>(FTokenizer& f, Token& t) {

    if (f._more) {
        if (!f._stk.done()) {
            t = f.next_token();

//            if (debug) {
//                cout << t.token_str() << endl;
//            }

        } else {
            f.get_new_block();
            t = f.next_token();

//            if (debug) {
//                cout << t.token_str() << endl;
//            }
        }
    }

    return f;
}

Token FTokenizer::next_token() {
    Token t;

    _stk >> t;

    return t;
}

bool FTokenizer::get_new_block() {
    if (_more) {
        _f.read(_block, MAX_BLOCK-1);
        _block[_f.gcount()] = NULL;

        if (debug) {
            cout << "GET NEW BLOCK" << endl;
//            cout << _block << endl;
        }

        if (_f.gcount() < MAX_BLOCK-1) {
            _more = false;
        }

        _stk.set_string(_block);
        return true;
    }
    return false;
}

bool FTokenizer::more() {
    return _more;
}

int FTokenizer::block_pos() {
    return _blockPos;
}

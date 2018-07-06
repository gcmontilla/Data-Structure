//
// Created by Gregory Montilla on 3/5/18.
//

#ifndef FTOKENIZER_FTOKENIZER_H
#define FTOKENIZER_FTOKENIZER_H

#include "constants.h"
#include "STokenizer.cpp"
#include <fstream>

using namespace std;

class FTokenizer {
public:
    static const int MAX_BLOCK = MAX_BUFFER;
    FTokenizer( const char* file);
    Token next_token();
    bool more();        // Returns the current value of _more
    friend FTokenizer& operator >> (FTokenizer& f, Token& t);

private:
    bool get_new_block(); // Gets the new block from the file
    ifstream _f;          // File being tokenized
    STokenizer _stk;      // Tokenizer
    bool _more;
    char _block[MAX_BLOCK];

};


#endif //FTOKENIZER_FTOKENIZER_H

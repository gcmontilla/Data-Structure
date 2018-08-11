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
    FTokenizer( char* file);
    Token next_token();
    bool more();        //returns the current value of _more
    int pos();          //returns the value of _pos
    int block_pos();     //returns the value of _blockPos
    friend FTokenizer& operator >> (FTokenizer& f, Token& t);

private:
    bool get_new_block(); //gets the new block from the file
    ifstream _f;          //file being tokenized
    STokenizer _stk;
    int _blockPos;        //Current position in the current block
    bool _more;           //false if last token of the last block
    //  has been processed and now we are at
    //  the end of the last block.
    char _block[MAX_BLOCK];

};


#endif //FTOKENIZER_FTOKENIZER_H

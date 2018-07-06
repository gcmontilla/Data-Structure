//
// Created by Gregory Montilla on 2/27/18.
//

#ifndef TOKENIZER_STOKENIZER_H
#define TOKENIZER_STOKENIZER_H

#include <iostream>
#include "Token.cpp"
#include "constants.h"

using namespace std;

class STokenizer {

public:
    // Constructors
    STokenizer();
    STokenizer(char str[]);

    bool done();    // true: no more tokens

    friend STokenizer& operator >> (STokenizer& s, Token& t);

    void set_string(char str[]);
    void reset();

    void print();
    void print_string(int len);

private:
    // create table for all the tokens we will recognize
    void make_table(int _table[MAX_ROWS][MAX_COLUMNS]);

    // extract the longest string that match
    bool get_token(int start_state, string& token);

    char _buffer[MAX_BUFFER];
    int _pos;
    static int _table[MAX_ROWS][MAX_COLUMNS];

    void mark_cells(int row, int table[][MAX_COLUMNS], int from, int to, int state);
    void mark_cells(int row, int table[][MAX_COLUMNS], const char columns[], int state);
    void mark_cell(int row, int table[][MAX_COLUMNS], int column, int state);
    void mark_table();

};


#endif //TOKENIZER_STOKENIZER_H

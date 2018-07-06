//
// Created by Gregory Montilla on 5/29/18.
//

#ifndef DATABASE_STOKENIZER_H
#define DATABASE_STOKENIZER_H

#include <iostream>
#include "Token.h"
#include "constants.h"


class STokenizer {
public:
    // Constructors
    STokenizer();
    STokenizer(char *str);

    bool done();    // true: no more tokens

    friend STokenizer& operator >> (STokenizer& s, Token& t);

    void set_string(char str[]);

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


#endif //DATABASE_STOKENIZER_H

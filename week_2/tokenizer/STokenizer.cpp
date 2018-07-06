//
// Created by Gregory Montilla on 2/27/18.
//

#include <iomanip>
#include "STokenizer.h"

// Constructor
STokenizer::STokenizer() {
    make_table(_table);
    _pos = 0;
}

// Constructor that initializes buffer to string
STokenizer::STokenizer(char *str) {
    make_table(_table);
    _pos = 0;
    strcpy(_buffer, str);
}

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer& operator>>(STokenizer &s, Token &t) {
    string token;

    if (s.get_token(START_DOUBLE, token)) {
        t = Token(token, DIGIT);
    } else if (s.get_token(START_ALPHA, token)) {
        t = Token(token, WORD);
    } else if (s.get_token(START_SPACES, token)) {
        t = Token(token, SPACE);
    } else if (s.get_token(START_OPERATORS, token)) {
        t = Token(token, PUNCTUATION);
    } else if (s.get_token(START_UNKNOWN, token)) {
        t = Token(token, UNKNOWN);
    }
    return s;
}

// Generates table
void STokenizer::make_table(int _table[][MAX_COLUMNS]) {

    // Creates table and sets all values to -1
    mark_table();

    // Create success states
//    mark_cell(0, _table, 0, 0);
//    mark_cell(1, _table, 0, 1);
//    mark_cell(2, _table, 0, 0);
//    mark_cell(3, _table, 0, 1);

    // Creates states for digits
    mark_cells(0, _table, DIGITS, 1);
    mark_cells(1, _table, DIGITS, 1);
    mark_cells(2, _table, DIGITS, 3);
    mark_cells(3, _table, DIGITS, 3);

    // Creates states for decimals
    mark_cells(0, _table, '.', '.', 2);
    mark_cells(1, _table, '.', '.', 2);

    // Creates states for strings
    mark_cells(4, _table, ALPHA, 5);
    mark_cell(4, _table, 39, 5);
    mark_cells(5, _table, ALPHA, 5);
    mark_cells(5, _table, DIGITS, 5);

    // Creates states for spaces
    mark_cells(6, _table, SPACES, 7);

    // Creates states for operators
    mark_cells(8, _table, OPERATORS, 9);

    // Create states for unknown
    mark_cells(10, _table, 0, MAX_COLUMNS, 11);

}

// Prints table
void STokenizer::print() {
    char array[MAX_COLUMNS];

    for (int m = 0; m < MAX_COLUMNS; ++m) {
        array[m] = 0;
    }
    for (int j = 0; j < MAX_COLUMNS; ++j) {
        array[int(ASCII[j])] = ASCII[j];
    }

    for (int k = 0; k < MAX_COLUMNS; ++k) {
        cout << setw(2) << array[k] << " ";
    }
    cout << endl;

    for (int l = 0; l < MAX_ROWS; ++l) {
        for (int i = 0; i < MAX_COLUMNS; ++i) {
            cout << setw(2) <<_table[l][i] << " ";
        }
        cout << endl;
    }
}

// Sets buffer to string argument
void STokenizer::set_string(char str[]) {
    strcpy(_buffer, str);
}

// Prints string
void STokenizer::print_string(int len) {
    for (int i = 0; i < len; ++i) {
        cout << _buffer[i] << " ";
    }
}

// Marks a range of cells using int variables
void STokenizer::mark_cells(int row, int table[][MAX_COLUMNS], int from, int to, int state) {
    for (int i = from; i <= to; ++i) {
        table[row][i] = state;
    }
}

bool STokenizer::done() {
    return (_pos >= strlen(_buffer));
}
// Marks a range of cells using an array
void STokenizer::mark_cells(int row, int table[][MAX_COLUMNS], const char columns[], int state) {
    for (int i = 0; i < strlen(columns); ++i) {
        table[row][int(columns[i])] = state;
    }
}

// Marks a single cell
void STokenizer::mark_cell(int row, int table[][MAX_COLUMNS], int column, int state) {
    table[row][column] = state;
}

// Marks entire table to -1
void STokenizer::mark_table() {
    for (int i = 0; i < MAX_ROWS; ++i) {
        for (int j = 0; j < MAX_COLUMNS; ++j) {
            _table[i][j] = -1;
        }
    }
}

// Checks if it was a token
bool STokenizer::get_token(int start_state, string &token) {
    bool success = false;
    int state = start_state;
    int l_pos = _pos;
    if (debug) {
        cout << "START " << start_state << endl;
    }
    do {
        char current = _buffer[_pos];
        int next = _pos + 1;
        switch (state) {
            case -1:
                _pos = l_pos;
            case 0:
                state = _table[state][int(current)];
                if (state == 1) {
                    token += current;
                    l_pos = _pos;
                    success = true;
                } else {
                    _pos = l_pos;
                }
                break;
//            case 1:
//                char next = _buffer[next];
//                state = _table[state][int(current)];
//                cout << state << endl;
//                if (state == 2) {
//                    if (isdigit(next)) {
//                        token += current;
//                        l_pos = _pos;
//                        success = true;
//                    }
//                } else if (state == 1) {
//                    token += current;
//                    l_pos = _pos;
//                    success = true;
//                } else {
//                    _pos = l_pos;
//                }
//                break;
//            case 2:
//                state = _table[state][int(current)];
//                if (state != -1) {
//                    token += current;
//                    l_pos = _pos;
//                    success = true;
//                } else {
//                    _pos = l_pos;
//                }
//                break;
//            case 3:
//                state = _table[state][int(current)];
//                if (state != -1) {
//                    token += current;
//                    l_pos = _pos;
//                    success = true;
//                } else {
//                    _pos = l_pos;
//                }
//                break;
//            case 4:
//                state = _table[state][int(current)];
//                if (state != -1) {
//                    token += current;
//                    l_pos = _pos;
//                    success = true;
//                } else {
//                    _pos = l_pos;
//                }
//                break;
//            case 5:
//                state = _table[state][int(current)];
//                if (state != -1) {
//                    token += current;
//                    l_pos = _pos;
//                    success = true;
//                } else {
//                    _pos = l_pos;
//                }
//                break;
//            case 6:
//                state = _table[state][int(current)];
//                if (state != -1) {
//                    token += current;
//                    l_pos = _pos;
//                    success = true;
//                } else {
//                    _pos = l_pos;
//                }
//                break;
//            case 7:
//                state = _table[state][int(current)];
//                if (state != -1) {
//                    token += current;
//                    l_pos = _pos;
//                    success = true;
//                } else {
//                    _pos = l_pos;
//                }
//                break;
//            case 8:
//                state = _table[state][int(current)];
//                if (state != -1) {
//                    token += current;
//                    l_pos = _pos;
//                    success = true;
//                } else {
//                    _pos = l_pos;
//                }
//                break;
//            case 9:
//                state = _table[state][int(current)];
//                if (state != -1) {
//                    token += current;
//                    l_pos = _pos;
//                    success = true;
//                } else {
//                    _pos = l_pos;
//                }
//                break;
//            case 10:
//                state = _table[state][int(current)];
//                if (state != -1) {
//                    token += current;
//                    l_pos = _pos;
//                    success = true;
//                } else {
//                    _pos = l_pos;
//                }
//                break;
//            case 11:
//                state = _table[state][int(current)];
//                if (state != -1) {
//                    token += current;
//                    l_pos = _pos;
//                    success = true;
//                } else {
//                    _pos = l_pos;
//                }
//                break;
            default:
                state = _table[state][int(current)];
                if (state != -1) {
                    token += current;
                    l_pos = _pos;
                    success = true;
                } else {
                    _pos = l_pos;
                }
                break;
        }

        if (debug) {
            cout << "STATE " << state << endl;
            cout << "POS   " << _pos << endl;
            cout << "SUCC  " << success << endl;
            cout << "LAST  " << l_pos << endl;
            cout << "CURR  " << current << endl;
            cout << "TOKEN " << token << endl;
            cout << "======" << endl;
        }
        ++_pos;

        } while (state != -1);

//    if (debug) {
//        cout << "FINAL TOKEN " << token << endl;
//        cout << "============" << endl;
//    }

    if (!success) {
        _pos = l_pos;
    }

    return success;
}

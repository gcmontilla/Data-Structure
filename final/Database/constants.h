//
// Created by Gregory Montilla on 5/29/18.
//

#ifndef DATABASE_CONSTANTS_H
#define DATABASE_CONSTANTS_H

// Constants
bool const debug = true;

static const int MAX_ROWS = 50;
static const int MAX_COLUMNS = 256;
static const int MAX_BUFFER = 1000;

const char ASCII[] = " !#$%'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~";
const char LETTERS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" ;
const char DIGITS[] = "0123456789";
const char OPERATORS[] = "><=!?-%&|,.*";
const char SPACES[] = {' ', '\t', '\n', '\0'};

const int START_DOUBLE = 0;
const int START_ALPHA = 4;
const int START_SPACES = 6;
const int START_OPERATORS = 8;
const int START_UNKNOWN = 10;
const int START_SPECIALS = 15;

const int UNKNOWN = -1;
const int DIGIT = 0;
const int WORD = 1;
const int SPACE = 2;
const int PUNCTUATION = 3;
const int SPECIAL = 4;

#endif //DATABASE_CONSTANTS_H

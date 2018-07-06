//
// Created by Gregory Montilla on 2/28/18.
//

#ifndef TOKENIZER_CONSTANTS_H
#define TOKENIZER_CONSTANTS_H

// Constants
bool const debug = false44

static const int MAX_ROWS = 12;
static const int MAX_COLUMNS = 256;
static const int MAX_BUFFER = 1000;

const char ASCII[] = " !#$%'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
const char ALPHA[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const char DIGITS[] = "0123456789";
const char OPERATORS[] = "><=!?-%&|,.";
const char SPACES[] = {' ', '\t', '\n', '\0'};

const int START_DOUBLE = 0;
const int START_ALPHA = 4;
const int START_SPACES = 6;
const int START_OPERATORS = 8;
const int START_UNKNOWN = 10;

const int UNKNOWN = -1;
const int DIGIT = 0;
const int WORD = 1;
const int SPACE = 2;
const int PUNCTUATION = 3;
#endif //TOKENIZER_CONSTANTS_H

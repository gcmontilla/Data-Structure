//
// Created by Gregory Montilla on 5/29/18.
//

#ifndef DATABASE_PARSE_H
#define DATABASE_PARSE_H

#include <string>
#include <iomanip>
#include <iostream>
#include "constants.h"
#include "map.h"
#include "mmap.h"
#include "file_record.h"
#include <vector>

using namespace std;

class Parse {
public:
    Parse();
    MMap<string, string> getParseTree(vector<string> command);
    vector<string> parse(char *line);

private:
    Map<string, int> keywords;
    void createMap();
    static const int tableLength = 18;
    static int table[tableLength][tableLength];
    void mark_cells(int row, int table[][tableLength], int from, int to, int state);
    void mark_cells(int row, int table[][tableLength], const char columns[], int state);
    void mark_cell(int row, int table[][tableLength], int column, int state);
    void mark_table();
    void make_table(int table[tableLength][tableLength]);
};


#endif //DATABASE_PARSE_H

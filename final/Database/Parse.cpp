//
// Created by Gregory Montilla on 5/29/18.
//

#include "Parse.h"
#include "STokenizer.h"

Parse::Parse() {
    make_table(table);
    createMap();
}

int Parse::table[tableLength][tableLength];

void Parse::make_table(int table[tableLength][tableLength]){
    mark_table();

    // success states
    table[4][0] = 1;
    table[6][0] = 1;
    table[12][0] = 1;
    table[18][0] = 1;

    // select from symbol, symbol
    table[0][1] = 1;
    table[1][4] = 2;
    table[1][11] = 2;
    table[2][2] = 3;
    table[2][3] = 1;
    table[3][4] = 4;
    table[4][8] = 5;
    table[5][4] = 6;
    table[6][3] = 5;
    table[6][4] = 6;

    // insert into table values
    table[0][5] = 8;
    table[8][6] = 9;
    table[9][4] = 10;
    table[10][7] = 11;
    table[11][4] = 12;
    table[12][3] = 11;
    table[12][4] = 12;

    // create table fields fields
    table[0][9] = 14;
    table[14][12] = 15;
    table[15][4] = 16;
    table[16][10] = 17;
    table[17][4] = 18;
    table[18][3] = 17;
    table[18][4] = 18;

}

void Parse::mark_table() {
    for (int i = 0; i < tableLength; ++i) {
        for (int j = 0; j < tableLength; ++j) {
            table[i][j] = -1;
        }
    }
}

MMap<string, string> Parse::getParseTree(vector<string> command) {
    int state = 0;
    int i = 0;
    int value = 0;
    MMap<string, string> pTree;

    while (i < command.size()) {
        string key = command[i];
        if (keywords.contains(key)) {
            value = keywords[key];
        } else {
            value = 4;
        }

//        if (debug)
//            cout << setw(10) << key << setw(3) << state << setw(3) << value;

        state = table[state][value];

        i++;
//        if (debug)
//            cout << setw(3) << state << endl;


        switch (state) {
            case 1:
                if (!pTree.contains("command")) {
                    pTree["command"].push_back(key);
                }
                break;
            case 2:
                pTree["fields"].push_back(key);
                break;
            case 4:
                pTree["table"].push_back(key);
                break;
            case 6:
                pTree["conditionals"].push_back(key);
                break;
            case 8:
                pTree["command"].push_back(key);
                break;
            case 10:
                pTree["table"].push_back(key);
                break;
            case 12:
                pTree["values"].push_back(key);
                break;
            case 14:
                pTree["command"].push_back(key);
                break;
            case 16:
                pTree["table"].push_back(key);
                break;
            case 18:
                pTree["fields"].push_back(key);
            default:
                break;
        }
    }

//    if (debug) {
//        if (table[state][0] == 1) {
//            cout << "valid command" << endl;
//        } else {
//            cout << "invalid command" << endl;
//        }
//    }

    return pTree;
}

void Parse::createMap() {
    keywords.insert("state", 0);
    keywords.insert("select", 1);
    keywords.insert("from", 2);
    keywords.insert(",", 3);
    keywords.insert("symbol", 4);
    keywords.insert("insert", 5);
    keywords.insert("into", 6);
    keywords.insert("values", 7);
    keywords.insert("where", 8);
    keywords.insert("make", 9);
    keywords.insert("fields", 10);
    keywords.insert("*", 11);
    keywords.insert("table", 12);
}

vector<string> Parse::parse(char *line) {
    vector<string> commands;
    STokenizer sTokenizer(line);
    while (!sTokenizer.done()) {
        Token t;
        sTokenizer >> t;
        if (t.type() == WORD or t.type() == PUNCTUATION or t.type() == DIGIT or t.type() == SPECIAL) {
            string token = t.token_str();
            if (t.type() == SPECIAL) {
                token = token.substr(1, token.size()-2);
            }
            commands.push_back(token);
        }
    }
    return commands;
}
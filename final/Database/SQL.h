//
// Created by Gregory Montilla on 6/7/18.
//

#ifndef DATABASE_SQL_H
#define DATABASE_SQL_H

#include "map.h"
#include "Table.h"
#include "Parse.h"

class SQL {
public:
    SQL();
    void run(string filename);
private:
    vector<string> tables;
    const string sqlInfo = "sql_info.txt";
    Map<string, Table> sql;
    Table table;
    void command(MMap<string, string>& parse);
    void add(string filename, string table);
    bool exists(string name);
};


#endif //DATABASE_SQL_H

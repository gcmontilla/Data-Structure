//
// Created by Gregory Montilla on 5/29/18.
//

#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H

#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include "mmap.h"
#include "map.h"

using namespace std;

class Table {
public:
    Table();
    Table& operator=(const Table& rhs);
    ~Table();
    Table(string name);

    const string &getName() const;

    long getRecordNumber() const;

    Table(string name, vector<string> fields);
    void insert(vector<string>& fields);
    Table select(vector<string> fields);
    Table select(vector<string> fields, vector<string> conditionals);
    void print();
    void printLoad();

private:
    string name;
    string filename;
    string info;
    long recordNumber;

    vector<MMap<string, long>> indices;
    Map<string, int> fieldMap;
    vector<string> fieldList;

    void createFile();
    void createIndices(vector<string> fields);
    void createFieldList(vector<string> fields);

    void storeFieldList(vector<string> fields);

    void loadFile(string filename);
    void loadFieldList();
    void loadIndices();

    bool isOperator(string word);
    bool fileExists(string filename);

    string createFileName(vector<string> fields);
    string createFileNameConditionals(vector<string> fields, vector<string> conditionals);
    string txt(string name);

    vector<string> orderedFields(vector<string> fields);
    vector<int> holdings(vector<string> fields);
    vector<int> selection(queue<string> rpn);

    queue<string> reversePolishNotation(vector<string> conditionals);

    void copyTable(const Table& rhs);

public:
    void setRecordNumber(long recordNumber);

private:

    const bool debug = false;
};


#endif //DATABASE_TABLE_H

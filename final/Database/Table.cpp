//
// Created by Gregory Montilla on 5/29/18.
//

#include <iostream>
#include <iomanip>
#include <queue>
#include "Table.h"
#include "utilities.h"
#include "consts.h"
#include "file_record.h"
#include "STokenizer.h"

using namespace std;
/**
 * default CTOR
 */
Table::Table() {}

/**
 * CTOR with name
 * @param name database name
 */
Table::Table(string name) {
    fieldList.clear();
    fieldMap.clear();
    indices.clear();

    this->name = name;
    info = name;
    info.append("_info.txt");
    filename = name;
    filename.append(".txt");
    loadFile(filename);
    loadFieldList();
    loadIndices();

    if (indices.empty()) {
        for (int i = 0; i < fieldList.size(); ++i) {
            MMap<string, long> mMap;
            indices.push_back(mMap);
        }
    }
}

/**
 * CTOR with name and fields
 * @param name database name
 * @param fields database fields
 */
Table::Table(string name, vector<string> fields) {
    this->name = name;
    info = name;
    info.append("_info.txt");
    filename = name;
    filename.append(".txt");
    createFile();
    createFieldList(fields);
    createIndices(fields);
    storeFieldList(fields);

    if (indices.size() == 0) {
        for (int i = 0; i < fieldList.size(); ++i) {
            MMap<string, long> mMap;
            indices.push_back(mMap);
        }
    }

    if (false) {
        cout <<"FIELDLIST";
        for(auto &fl :fieldList) {
            cout << setw(10) << fl;
        }
        cout << endl;
    }
}

/**
 * inserst values into database
 * @param fields values
 */
void Table::insert(vector<string>& fields) {
    // loading file
    if (false) cout << "INDICES SIZE " << indices.size() << endl;

    if (indices.empty()) {
        for (int i = 0; i < fieldList.size(); ++i) {
            MMap<string, long> mMap;
            indices.push_back(mMap);
        }
    }

   if (false) cout << "INDICES NEW SIZE " << indices.size() << endl;

    fstream f;
    file_record fRecord(recordNumber);

    for (int i = 0; i < fields.size(); i++) {
        strcpy(fRecord.record[i+1], fields[i].c_str()); // inserts into file record
        indices[i].insert(fields[i], recordNumber);     // inserts into indices
    }

    // updates record number
    open_fileRW(f, filename.c_str());
    f.seekg(0, f.end);
    recordNumber = fRecord.write(f);
    f.close();
}

/**
 * selects fields from a database
 * @param fields selected fields
 * @return table with information
 */
Table Table::select(vector<string> fields) {
    // open file
    fstream file;
    file_record record(recordNumber);
    open_fileRW(file, filename.c_str());
    vector<vector<string>> inserts;
    vector<string> inOrderFields = orderedFields(fields);
    string tempFileName = createFileName(inOrderFields);
    string checkFile = txt(tempFileName);

    if (false) {
//        cout << "FINALIST";
//        for (auto &fin : finalists) {
//            cout << setw(3) << fin;
//        }
//        cout << endl;
//        cout << "FIELD LIST";
//        for (auto &fl : fieldList) {
//            cout << setw(10) << fl;
//        }
//        cout << endl;
        cout << "IN ORDER FIELDS";
        for (auto &iof : inOrderFields) {
            cout << setw(5) << iof;
        }
        cout << endl;
    }

    if (fileExists(checkFile)) {
        Table temp(tempFileName);
        return temp;
    } else {
        Table temp(tempFileName, inOrderFields);
        if (fields[0] != "*") {
            vector<int> selection = holdings(fields);

            for (int i = 1; i < recordNumber; ++i) {
                vector<string> insert;
                for (auto &s: selection) {
                    record.read(file, i);
                    insert.emplace_back(record.record[s + 1]);
                }
                inserts.push_back(insert);
            }

        } else {
            vector<int> selection = holdings(fieldList);
            for (int i = 1; i < recordNumber; ++i) {
                vector<string> insert;
                for (auto &s :  selection) {
                    record.read(file, i);
                    insert.emplace_back(record.record[s + 1]);
                }
                inserts.push_back(insert);
            }
        }

        file.close();

        for (auto &i : inserts) {
            temp.insert(i);
        }

        return temp;
    }
}

/**
 * selects fields from a database that fits the conditions
 * @param fields selected fields
 * @param conditionals conditionals
 * @return table with information
 */
Table Table::select(vector<string> fields, vector<string> conditionals) {
    fstream file;
    file_record record(recordNumber);
    open_fileRW(file, filename.c_str());
    queue<string> rpn = reversePolishNotation(conditionals);
    vector<int> finalists = selection(rpn);
    vector<vector<string>> inserts;
    vector<string> inOrderFields = orderedFields(fields);

    if (false) {
        cout << "FIELDS";
            for (auto &f :fields) {
                cout <<setw(10) << f;
            }
        cout << endl;
        cout << "FINALIST";
        for (auto &fin : finalists) {
            cout << setw(3) << fin;
        }
        cout << endl;
        cout << "FIELD LIST";
        for (auto &fl : fieldList) {
            cout << setw(10) << fl;
        }
        cout << endl;
        cout << "IN ORDER FIELDS";
        for (auto &iof : inOrderFields) {
            cout << setw(5) << iof;
        }
        cout << endl;
    }

    string tempFileName = createFileNameConditionals(inOrderFields, conditionals);
    string checkFile = txt(tempFileName);

    if (fileExists(checkFile)) {
        Table temp(tempFileName);
        return temp;
    } else {

        if (fields[0] != "*") {
            Table temp(tempFileName, inOrderFields);
            vector<int> holding = holdings(fields);

            for (auto &i : finalists) {
                vector<string> insert;
                for (auto &h: holding) {
                    record.read(file, i);
                    insert.emplace_back(record.record[h + 1]);
                }
                inserts.push_back(insert);
            }

            file.close();

            if (false) {
                cout << "TEMP\n";
                for (int i = 0; i < inserts.size(); ++i) {
                    cout << setw(4)<< i;
                    for (int j = 0; j < inserts[i].size(); ++j) {
                        cout << setw(15) << inserts[i][j];
                    }
                    cout << endl;
                }
                cout << endl;
            }

            for (auto &i : inserts) {
                if (false) cout << "INSERTING ALL OF THEM\n";
                temp.insert(i);
            }
            if (false) cout << "COMPLETED INSERTED ALL OF THEM\n";
            return temp;
        } else {
            Table temp(tempFileName, fieldList);
            if (false) cout << "SELECTING ALL\n";
            vector<int> holding = holdings(fieldList);
            if (false) {
                cout << "INNER FINALISTS";
                for (auto &fin: finalists) {
                    cout << setw(5) << fin;
                }
                cout << endl;
                cout << "HOLDING";
                for (auto &h : holding) {
                    cout << setw(10) << h;
                }
                cout << endl;
                cout << "INNER FIELD LIST";
                for (auto &fl : fieldList) {
                    cout << setw (10) << fl;
                }
                cout << endl;
            }
            for (auto &i : finalists) {
                vector<string> insert;
                    for (auto &h : holding) {
//                for (auto &f: fieldList) {
                    record.read(file, i);
//                    cout << setw(15) << record.record[h + 1];
                    insert.push_back(record.record[h + 1]);
                }
//                cout << endl;

                    if (false) {
                        cout << "INSERT";
                        for (auto &i : insert) {
                            cout << setw(15) <<i <<".";
                        }
                        cout << endl;
                    }
                inserts.push_back(insert);
            }

            file.close();

            if (false) {
                cout << "TEMP\n";
                for (int i = 0; i < inserts.size(); ++i) {
                    cout << setw(4)<< i;
                    for (int j = 0; j < inserts[i].size(); ++j) {
                        cout << setw(15) << inserts[i][j];
                    }
                    cout << endl;
                }
                cout << endl;
            }

            for (auto &i : inserts) {
                if (false) cout << "INSERTING ALL OF THEM\n";
                temp.insert(i);
            }
            if (false) cout << "COMPLETED INSERTED ALL OF THEM\n";
            return temp;
        }
    }
}

/**
 * loads file from storage
 * @param name filename
 */
void Table::loadFile(string name) {
    fstream file;
    open_fileRW(file, filename.c_str());
    file.seekg(0, file.end);
    streampos pos = file.tellp();
    recordNumber = pos/(MAX_RECORD_WIDTH*MAX_RECORD_WIDTH)-1;

    file.close();
    if (debug)
        cout << "loaded " << name << " contains " << recordNumber << " records" << endl;
}

/**
 * prints table
 */
void Table::print() {
    // opens file
    fstream file(filename.c_str());
    file_record record(0);

    cout << setw(5) << "No.";
    for (auto &f: fieldList) {
        cout << setw(20) << f;
    }
    cout << endl;

    for (int i = 1; i <= recordNumber; ++i) {
        record.read(file, i);
        cout << setw(4) << i << " " << record << endl;
    }

    file.close(); // closes file
}

void Table::printLoad() {
    // opens file
    fstream file(filename.c_str());
    file_record record(0);

    cout << setw(5) << "No.";
    for (auto &f: fieldList) {
        cout << setw(20) << f;
    }
    cout << endl;

    for (int i = 1; i <= recordNumber; ++i) {
        record.read(file, i);
        cout << setw(4) << i << " " << record << endl;
    }

    file.close(); // closes file
}

/**
 * creates database file
 */
void Table::createFile() {
    if (debug)
        cout << "creating file" << endl;

    // creates files
    fstream f;
    file_record file(recordNumber);
    open_fileRW(f, filename.c_str());
    recordNumber = file.write(f); // sets record number
    f.close();  // closes file
}

/**
 * creates field list for databse
 * @param fields fields
 */
void Table::createFieldList(vector<string> fields) {
    if (debug)
        cout << "creating field list" << endl;

    // creates field lists
    for (const auto &f : fields) {
        fieldList.push_back(f);

    };

    for (int i = 0; i < fields.size(); ++i) {
        fieldMap.insert(fields[i], i);
    }
}

/**
 * creates indices for database
 */
void Table::createIndices(vector<string> fields) {
    if (debug)
        cout << "creating indices" << endl;

    // creates an index for each file
    for (const auto &f: fields) {
        MMap <string, long> mMap;
        indices.push_back(mMap);
    }
}

/**
 * stores fields to a file
 * @param fields fields to be stored
 */
void Table::storeFieldList(vector<string> fields) {
    // opens file
    ofstream file;
    file.open(info);

    // writes field lists to file
    for (auto &f : fields) {
        file << f << "\n";
    }

    file.close(); // closes file
}

/**
 * loads fields from a file
 */
void Table::loadFieldList() {
    if (debug)
        cout << "loading field lists" << endl;

    // opens file and pushes into field list
    ifstream file(info);
    string line;
    int i = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (false) cout << "LINE " <<line << endl;
            fieldList.push_back(line);
            fieldMap.insert(line, i);
            i++;
        }
    }

    file.close();   // closes file
}

/**
 * loads databse indices
 */
void Table::loadIndices() {
    // opens file
    fstream file;
    file_record record(recordNumber);
    open_fileRW(file, filename.c_str());

    if (false) {
        cout << "FIELD LIST";
        for (auto &f : fieldList) {
            cout << setw(10) << f;
        }
        cout << endl;
    }

    // creates an index for each field
    for (auto &field : fieldList) {
        MMap<string, long> mMap;
        indices.push_back(mMap);
    }

    // cycles through file record and pushes into proper index
    for (int i = 1; i < recordNumber; ++i) {
        for (int j = 0; j < fieldList.size(); ++j) {
            record.read(file, i);
            indices[j].insert(record.record[j+1], i);
        }
    }

    file.close();  // closes file
}

/**
 * COPY CTOR
 * @param rhs
 * @return table
 */
Table& Table::operator=(const Table &rhs) {
    copyTable(rhs);
    return *this;
}

Table::~Table() {}

/**
 * converts conditionals to reverse polish conditionals
 * @param conditionals parsed conditions
 * @return rpn conditions
 */
queue<string> Table::reversePolishNotation(vector<string> conditionals) {
    stack<string> operators;
    queue<string> output;

    Map<string,int> precedence;
    precedence.insert("=", 10);
    precedence.insert("<", 10);
    precedence.insert(">", 10);
    precedence.insert("<=", 10);
    precedence.insert(">=", 10);
    precedence.insert("or", 7);
    precedence.insert("and", 2);

    for (auto &c : conditionals) {
        if (precedence.contains(c)) {
            while (!operators.empty() and precedence[operators.top()] >= precedence[c]) {
                output.push(operators.top());
                operators.pop();
            }
            operators.push(c);
        } else {
            output.push(c);
        }
    }

    while (!operators.empty()) {
        output.push(operators.top());
        operators.pop();
    }

    return output;
}

/**
 * final indices that fits conditions
 * @param rpn
 * @return indices that fit conditions
 */
vector<int> Table::selection(queue<string> rpn) {
    fstream file;
    file_record record(recordNumber);
    open_fileRW(file, filename.c_str());
    vector<vector<int>> survivors;
    string fl;
    string op;
    string field;

    Map <string, int> operations;
    for (int j = 0; j < fieldList.size(); ++j) {
        operations.insert(fieldList[j], j);
    }

    while (!rpn.empty()) {
        if (operations.contains(rpn.front())) {
            fl = rpn.front();
            rpn.pop();

        } else if (isOperator(rpn.front())) {
            vector<int> temp;
            temp.clear();
            op = rpn.front();
            rpn.pop();

            for (int i = 1; i < recordNumber; ++i) {
                record.read(file, i);

                string value = record.record[operations[fl]+1];

                if (false) {
                    cout << fl << op << field << value << endl;
                }

                if (op == "=" and value == field) { temp.push_back(i); }

                if (op == ">" and value > field) { temp.push_back(i); }

                if (op == "<" and value < field) { temp.push_back(i); }

                if (op == ">=" and value <= field) { temp.push_back(i); }

                if (op == "<=" and value >= field) { temp.push_back(i); }
            }

            survivors.push_back(temp);

        } else if (rpn.front() == "and" or rpn.front() == "or") {
            vector<int> one = survivors.at(survivors.size()-1);
            survivors.pop_back();
            vector<int> two = survivors.at(survivors.size()-1);
            survivors.pop_back();
            sort(one.begin(), one.end());
            sort(two.begin(), two.end());
            if (rpn.front() == "and") {
                vector<int> i;
                set_intersection(one.begin(), one.end(), two.begin(), two.end(), back_inserter(i));
                survivors.push_back(i);
            } else if (rpn.front() == "or") {
                vector<int> u;
                set_union(one.begin(), one.end(), two.begin(), two.end(), back_inserter(u));
                survivors.push_back(u);
            }
            rpn.pop();
        } else {
            field = rpn.front();
            rpn.pop();
        }
    }

    return survivors[0];
}


/**
 * checks if word is an operator
 * @param word word to check
 * @return true/false
 */
bool Table::isOperator(string word) {
    const vector<string> operations = {"=", "<", ">", "<=", ">="};
    return (find(operations.begin(), operations.end(), word) != operations.end());
}

/**
 * checks if file exists
 * @param filename filename
 * @return true if exists
 */
bool Table::fileExists(string filename) {
    fstream file(filename.c_str());
    return file.good();
}

/**
 * returns fields in order
 * @param fields input
 * @return ordered fields
 */
vector<string> Table::orderedFields(vector<string> fields) {
    vector<string> inOrderFields;
        for (int j = 0; j < fieldList.size(); ++j) {
            for (auto &f : fields) {
                if (fieldList[j] == f) {
                    inOrderFields.push_back(f);
                }
            }
        }
    return inOrderFields;
}

/**
 *
 * @param fields
 * @return
 */
vector<int> Table::holdings(vector<string> fields) {
    vector<int> holding;
    if (false) cout << "FIRST FIELD " << fields[0]<< endl;
    if (fields[0] != "*") {
        for (int k = 0; k < fieldList.size(); ++k) {
            for (auto f : fields) {
                if (fieldList[k] == f) {
                    holding.push_back(k);
                }
            }
        }

        sort(holding.begin(), holding.end());
        return holding;
    }
}

string Table::createFileName(vector<string> fields) {
    string fname;
    for (auto &f : fields) {
        fname += f;
    }
    fname += name;
    return fname;
}

string Table::createFileNameConditionals(vector<string> fields, vector<string> conditionals) {
    string fname;
    for (auto &f: fields) { fname += f; }
    for (auto &c : conditionals) { fname += c; }
    fname += name;
    return fname;
}

string Table::txt(string name) {
    string temp = name;
    temp.append(".txt");
    return temp;
}

void Table::copyTable(const Table &rhs) {
    name = rhs.name;
    filename = rhs.filename;
    info = rhs.info;

    if (false) {
        cout << "RHS\n";
        cout << rhs.getName() << endl;
        cout << rhs.filename << endl;
        cout << rhs.info << endl;
        cout << "COPYING TABLE\n";
        cout << name << endl;
        cout << filename << endl;
        cout << info << endl;
    }

    recordNumber = rhs.recordNumber;
    fieldList = rhs.fieldList;
    fieldMap = rhs.fieldMap;
    indices = rhs.indices;

    if (false) {
        cout << "FL";
        for (auto &f : fieldList) {
            cout << setw(5) << f;
        }
        cout << endl;
    }
//    if (indices.empty()) {
//        for (int i = 0; i < fieldList.size(); ++i) {
//            MMap<string, long> mMap;
//            indices.push_back(mMap);
//        }
//    }
}

long Table::getRecordNumber() const {
    return recordNumber;
}

const string &Table::getName() const {
    return name;
}

void Table::setRecordNumber(long recordNumber) {
    Table::recordNumber = recordNumber;
}

//
// Created by Gregory Montilla on 6/7/18.
//

#include "SQL.h"

/**
 * CTOR
 */
SQL::SQL() {
    fstream file;
    file.open(sqlInfo);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            tables.push_back(line);
            Table t(line);
            sql.insert(line, t);
        }
    }

    file.close();
}

/**
 * runs file
 * @param filename name of file
 */
void SQL::run(string filename) {
    Parse parse;
    fstream file(filename);
    string line;
    int count = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.find("/") == 0 or line == "") {
                cout << line << endl;
            } else {
                cout << "[" << count << "] " << line << endl;
                int length = line.length();
                char array[length+1];
                strcpy(array, line.c_str());
                vector<string> parsedCommands = parse.parse(array);
                MMap<string, string> pTree = parse.getParseTree(parsedCommands);

                if(false) {
                    cout << "PTREE\n" <<pTree << endl;
                }
                command(pTree);
                count++;


                cout << endl << endl << "SQL: DONE.\n";
            }
        };
    }
}

/**
 * control database
 * @param parse parsetree
 */
void SQL::command(MMap<string, string>& parse) {
    string table = parse["table"][0];
    vector<string> fields = parse["fields"];
    string command = parse["command"][0];
    if (command == "make") {
        Table t(table, fields);
        sql.insert(table, t);
        add(sqlInfo, table);
        if (true) {
            cout << "SQL::create_table(" << table << ", ";
            for (auto &f : fields) {
                cout << f << " ";
            }
            cout << ")\n";
            cout << "Table " << table << " created. cols: ";
            for (auto &f : fields) {
                cout << f << " ";
            }
            cout << endl;
            t.print();
        }
    } else {
//        Table t(table);
        if (command == "select") {
            if (parse.contains("conditionals")) {
                vector<string> conditions = parse["conditionals"];
                Table a = sql[table].select(fields, conditions);

                if (true) {
                    cout << "Table name: " << a.getName() << ", records: " << a.getRecordNumber()  << endl;
                    a.print();
                }
            } else {
                Table a = sql[table].select(fields);

                if (true) {
                    cout << "Table name: " << a.getName() << ", records: " << a.getRecordNumber()  << endl;
                    a.print();
                }
            }
        }
        if (command == "insert") {
            vector<string> values = parse["values"];
            sql[table].insert(values);
            if (true) {
                cout << "SQL::run: inserted\n";
//                sql[table].print();
            }
        }
    }
}

/**
 * adds database to txt file
 * @param filename file holding all databases
 * @param table database name
 */
void SQL::add(string filename, string table) {
    // opens file
    ofstream file;
    file.open(filename, ios_base::app);

    // writes field lists to file
    if (!exists(table)) {
        file << table << '\n';
    }

    file.close(); // closes file
}

/**
 * checks if file exists
 * @param name filename
 * @return true if it exists
 */
bool SQL::exists(string name) {
    ifstream file(sqlInfo);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.find(name) != string::npos) {
                return true;
            }
        }
    }
    return false;
}
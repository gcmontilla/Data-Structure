#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "file_record.h"
#include "utilities.h"
#include "consts.h"
#include "STokenizer.h"
#include "Parse.h"
#include "Table.h"
#include "SQL.h"
#include "b_tree.h"

long get_last_record(fstream& f);
vector<string> input_record();
//void map_test();
//MMap<string, long> get_word_indices(char* file_name);

int main() {
    srand(time(0));
//    vector<string> fields = {"First Name","Age","Last Name"};
//    vector<string> first = {"Greg", "Bo", "Andres", "Evan", "Joe", "Simon","Wall-E"};
//    vector<string> last = {"Montilla", "Yang", "Caro", "Firoozi", "Zhang", "Eva"};
//    Table t("student", fields);
//    for (int j = 0; j < 10; ++j) {
//        vector<string> i = {first[rand()%3], last[rand()%3], to_string(rand() % 50 + 1)};
//        t.insert(i);
//    }
//    t.print();
//    Table a("student");
//    a.print();
//    vector<string> b = {"a","b","=","c","d",">","and","e","f","<","or"};
//    vector<string> c = {"First Name","=","Greg","or","Last Name","=", "Yang","and","Age","<","25"};
//    Table b = a.select(fields, c);
//    b.print();
//    vector<int> s = a.selection(output);
//    for(auto &i : s) {
//        cout << setw(5) << i;
//    }
//    cout << endl;
//    a.select(fields);
//    a.print();
//    vector<string> select = {"select", "lname", "from", "student", "where", "la la la"};
//    vector<string> create = {"create", "student", "fields", "name", "age", "course"};
//    vector<string> insert = {"insert", "into", "table", "values", "b", "c"};
//    Parse parse;
//    char * test = {"lname = Jackson"};
//    char *line = {"select *from student where \"fname\"=name and lname=name"};
//    char *b = {"create student fields name, age, course"};
//    char *c = {"insert into table values b, c"};
//    vector<string> commands = parse.parse(line);
//    cout << parse.getParseTree(commands);
//    Table b("student");
//    vector<string> i = {"*"};
//    b.insert(i);
//    b.print();
//    Table a = b.select(i, commands);
//    a.print();

//    Table c("test");
//    for (int j = 0; j < 5; ++j) {
//        b.insert(i);
//    }
//    b.print();
    SQL sql;
//    string n = "_!batch_file.batch";
    string s = "_!select.txt";
//    string o = "_!sample_original.txt";
//    string ss = "_!sample_student.txt";
//    string t = "test.txt";
//    string a ="_!original.txt";
    sql.run(s);
//
//    Table e("employee");
//    e.print();
//    Table s("fnamelnamefname>Bostudent");
//    cout << "==================================================================" << endl;
//    s.print();

//    fstream file(name);
//    string line;
//    if (file.is_open()) {
//        while (getline(file, line)) {
//            cout << line << endl;
//        }
//    }

//    map_test();
}

long get_last_record(fstream& f){
    //this is for testing only! Do not use this in your project!
    const bool debug = false;
    file_record frec;
    int recno = 0;
    while (!f.eof()){
        frec.read(f, recno);
        if (debug) cout<<"recno: "<<setw(4)<<recno<<frec<<endl;
        recno++;
    }
    if (debug) cout<<"found last record: "<<recno<<endl;
    return recno;

}
vector<string> input_record(){
    string s;
    vector<string> v;
    cout<<": ";
    getline(cin, s);
    while (!s.empty()){
        v.push_back(s);
        cout<<": ";
        getline(cin, s);
    }
    return v;
}

//void map_test() {
//    MMap<string, long> word_indices;
//    word_indices = get_word_indices("solitude.txt");
//    cout<<endl<<endl<<endl;
//
//    //list all nodes of the index mmap:
//    for (MMap<string, long>::Iterator it = word_indices.begin();
//         it != word_indices.end(); it++){
//        cout<<*it<<endl;
//    }
//
//
//    cout<<endl<<endl<<endl;
//    cout<<"---------------------------------------------------"<<endl;
//    string this_word = "ice";
//    cout<<"---------------------------------------------------"<<endl;
//    cout<<"Indices of \""<<this_word<<"\""<<endl;
//    //list indices of this_word:
//    if (word_indices.contains(this_word)){
//        cout<<this_word<<": "<<word_indices[this_word]<<endl;
//    }
//    cout<<endl<<endl<<endl;
//
//    cout<<"---------------------------------------------------"<<endl;
//    string from = "ask";
//    string to = "asker";
//    //list from .. to:
//    cout<<"listing indices from \""<<from<<"\" to \""<<to<<"\""<<endl;
//    cout<<"---------------------------------------------------"<<endl;
//    for (MMap<string, long>::Iterator it =
//            word_indices.lower_bound(from);
//         it != word_indices.upper_bound(to) &&
//         it != word_indices.end(); it++){
//        cout<<*it<<endl;
//    }
//
//    cout <<endl<<endl<<endl<< "========== E N D  ====================" << endl;
//}

//MMap<string, long> get_word_indices(char* file_name){
//    const bool debug = false;
//    MMap<string, long> word_indices;
//    FTokenizer ftk("solitude.txt");
//    Token t;
//    long count = 0;
//
//    ftk >> t;
//    while (ftk.more()){
//        //only the "words"
//        if (t.type_string() == "WORD"){
//            string s;
//            s = t.token_str();
//            word_indices[s].push_back(count);
//            count++;
//            if (debug)
//                cout<<"|"<<t.token_str()<<"|"<<endl;
//        }
//        ftk >> t;
//    }
//    return word_indices;
//}
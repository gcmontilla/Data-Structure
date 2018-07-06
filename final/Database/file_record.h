#ifndef FIELD_H
#define FIELD_H
#include <iostream>
using namespace std;
const int MAX_RECORD_WIDTH = 50;
struct file_record{
public:
    file_record(long r = 0);
    long rec_no();
    streampos write(fstream& outs);
    streampos read(fstream &ins, streampos recno);
    friend ostream& operator <<(ostream& out,
                          const file_record& r);


    char record[MAX_RECORD_WIDTH][MAX_RECORD_WIDTH];
};

#endif // FIELD_H

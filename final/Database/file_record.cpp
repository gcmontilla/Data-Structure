#include "file_record.h"
#include <iostream>
#include  <fstream>
#include <string>
#include <iomanip>


file_record::file_record(long r) {
    strcpy(record[0], to_string(r).c_str());
    for (int i = 1 ; i<MAX_RECORD_WIDTH; i++)
        record[i][0] = NULL;
}

long file_record::rec_no() {
    return stol(string(record[0]));
}

streampos file_record::write(fstream& outs){
    //write to the end of the file.
    streampos pos = outs.tellp();
    outs.write(&record[0][0], sizeof(record));
    return pos/sizeof(record);
}

streampos file_record::read(fstream& ins, streampos recno){
    streampos pos= recno * sizeof(record);
    ins.seekg(pos, ios_base::beg);
    ins.read(&record[0][0], sizeof(record));
    return ins.gcount();
}

ostream& operator <<(ostream& outs, const file_record& r){
    for (int i=1; r.record[i][0]!= NULL && i<MAX_RECORD_WIDTH; i++){
        outs<<setw(20)<<r.record[i];
    }
    return outs;
}

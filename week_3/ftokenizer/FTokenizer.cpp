//
// Created by Gregory Montilla on 3/5/18.
//

#include "FTokenizer.h"

/// Constructs FTokenizer object
/// \param file File needed to be opened
FTokenizer::FTokenizer(const char *file) {
    _f.open(file);  // Opens file
    _more = true;   // Sets more to true

    // Checks for failure to open file
    if (_f.fail()) {
        cout << "FAILURE" << endl;
    }
}

/// Grabs token from file
/// \param f File Tokenizer object
/// \param t Token object
/// \return Next token from file
FTokenizer& operator>>(FTokenizer& f, Token& t) {
    // Checks if tokenizer is done, gets new block from file
    if (f._stk.done()) {
        f.get_new_block();
    }

    t = f.next_token();     // Sets token to next token

    // Check for end of file and if tokenizer is done
    if ((f._f.eof()) && (f._stk.done())) {
        f._more = false;
        f._f.close();
    }

    return f;
}

/// Gets next token
/// \return Next token
Token FTokenizer::next_token() {
    // Grabs the next token
    Token t;
    _stk >> t;
    return t;
}

/// Gets new block from file and sets it for string tokenizer
/// \return True if gets new block, false if else
bool FTokenizer::get_new_block() {
    // Checks if there is more in the file
    if (_more) {
        // Reads new block from file and sets string for tokenizer
        _f.read(_block, MAX_BUFFER - 1);
        _block[_f.gcount()] = NULL;
        _stk.set_string(_block);
        return true;
    }
    return false;
}

/// Returns value of more
/// \return True if there is more to file, false if else
bool FTokenizer::more() {
    return _more;
}

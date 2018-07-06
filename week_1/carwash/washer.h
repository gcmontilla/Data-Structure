//
// Created by Gregory Montilla on 2/21/18.
//

#ifndef CARWASH_WASHER_H
#define CARWASH_WASHER_H

#include <cstddef>
#include <iostream>

using namespace std;


class washer {
public:
    // CONSTRUCTOR
    washer(unsigned int s);
    // MOD MEM FUNC
    void second();
    bool busy() const {
        return (washTimeLeft > 0);
    };
    // CONST MEM FUNC
    void wash();

private:
    unsigned int washTime;
    unsigned int washTimeLeft;
};

class averager {
public:
    // CONSTRUCTOR
    averager();
    // MOD MEM FUNC
    void next(double value);
    // CONST MEM FUNC
    size_t amount() const {
        return count;
    };
    double average() const;

private:
    double sum;
    size_t count;
};

class probability {

public:
    // CONSTRUCTOR
    probability(double p = 0.5);
    // CONST MEM FUNC
    bool query() const;

private:
    double prob;
};


#endif //CARWASH_WASHER_H

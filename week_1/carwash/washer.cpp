//
// Created by Gregory Montilla on 2/21/18.
//

#include "washer.h"
#include <cassert>

washer::washer(unsigned int s) {
    washTime = s;
    washTimeLeft = 0;
}

void washer::wash() {
    assert(!busy());
    washTimeLeft = washTime;
}

void washer::second() {
    if (busy()) {
        washTimeLeft--;
    }
}

averager::averager() {
    count = 0;
    sum = 0;
}

double averager::average() const {
    assert(amount() > 0);
    return sum/count;
}

void averager::next(double value) {
    ++count;
    sum += value;
}

probability::probability(double p) {
    assert(prob >= 0);
    assert(prob <= 1);
    prob = p;
}

bool probability::query() const {
    return (rand() < prob * RAND_MAX);
}

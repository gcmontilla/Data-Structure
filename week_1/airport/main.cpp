#include <iostream>
#include "airport.cpp"
#include "Queue.h"

using namespace std;

void simulate(unsigned int takeoff_t, double takeoff_p, unsigned int landing_t, double landing_p, unsigned int fuel,
              unsigned int total_t);

int main() {
    srand(time(NULL));
    airport runway;
    for (int i = 0; i < 5; ++i) {
        runway.simulate(15, .1, 5, .08, 20, 1440);
        std::cout << "=============================" << std::endl;
    }
}

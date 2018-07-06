//
// Created by Gregory Montilla on 2/22/18.
//

#include "airport.h"
#include <cassert>
#include "Queue.h"
#include <iostream>

using namespace std;


// AIRPORT CLASS
// Constructor
airport::airport() {
    time = 0;
    time_left = 0;
}

// Simulates entire airport
void airport::simulate(unsigned int takeoff_t, double takeoff_p, unsigned int landing_t, double landing_p,
                       unsigned int fuel, unsigned int total_t) {
        Queue<unsigned int> takeoff_times;
        Queue<unsigned int> landing_times;
        unsigned int next;
        probability takeoff(takeoff_p);
        probability landing(landing_p);
        airport runway;
        averager t_averager;
        averager l_averager;
        unsigned int current_second;
        unsigned int crash = 0;

        // Write the parameters to cout
        cout << "time to take off   :" << takeoff_t << endl;
        cout << "time to land       :" << landing_t << endl;
        cout << "prob. of take off  :" << takeoff_p << endl;
        cout << "prob. of landing   :" << landing_p << endl;
        cout << "fuel               :" << fuel << endl;
        cout << "simulation time    :" << total_t << endl << endl;

        // Simulate the passage of a second
        for (current_second = 1; current_second <= total_t; current_second++) {
            // Check if landing or taking off
            if (takeoff.query()) {
                takeoff_times.push(current_second);
            }

            if (landing.query())
                landing_times.push(current_second);

            // Check if runway is busy and plane in landing queue
            if ((!runway.busy()) && (!landing_times.empty())) {
                next = landing_times.front();
                landing_times.pop();
                // Checks if plane crashed or landed
                if (next > fuel) {
                    runway.set_time(landing_t);
                    l_averager.next(current_second - next);
                    runway.run();
                } else {
                    ++crash;
                }
                // Check if runway is busy and plane in take off queue
            } else if ((!runway.busy()) && (!takeoff_times.empty())) {
                next = takeoff_times.front();
                takeoff_times.pop();
                runway.set_time(takeoff_t);
                t_averager.next(current_second - next);
                runway.run();
            }

            // Airport simulates passage of a second
            runway.second();
        }

        // Prints out information
        cout << "planes taken off   : " << t_averager.amount() << endl;
        cout << "planes landed      : " << l_averager.amount() - crash << endl;
        if (t_averager.amount() > 0) {
            cout << "avg takeoff        : " << t_averager.average() << endl;
        }
        if (l_averager.amount() > 0) {
            cout << "avg landing        : " << l_averager.average() << endl;
        }
        cout << "waiting to takeoff : " << takeoff_times.amount() << endl;
        cout << "waiting to land    : " << landing_times.amount() << endl;
        cout << "crashes            : " << crash << endl;
}

// Sets the time left to time
void airport::run() {
    assert(!busy());
    time_left = time;
}

// Sets time to desired time
void airport::set_time(unsigned int t) {
    time = t;
}

// Simulates a second
void airport::second() {
    if (busy()) {
        --time_left;
    }
}

// AVERAGER CLASS
// Constructor
averager::averager() {
    count = 0;
    sum = 0;
}

// Returns average wait time
double averager::average() const {
    assert(amount() > 0);
    return sum/count;
}

// Appends values to count and sum
void averager::next(double value) {
    count++;
    sum += value;
}

// PROBABILITY CLASS
// Constructor
probability::probability(double p) {
    assert(p <= 1);
    assert(p >= 0);
    _probability = p;
}

// Checks if plane is in queue
bool probability::query() const {
    return (rand() < _probability * RAND_MAX);
}
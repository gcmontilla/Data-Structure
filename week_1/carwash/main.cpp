#include <iostream>
#include "washer.cpp"
#include <queue>
#include "Queue.h"

void simulate(unsigned int washTime, double arrivalP, unsigned int totalTime);

int main() {
    simulate(10, 0.3, 600);
}

void simulate(unsigned int washTime, double arrivalP, unsigned int totalTime) {
    queue<unsigned int> arrivalTimes;
    unsigned int next;
    probability arrival(arrivalP);
    washer machine(washTime);
    averager waitTimes;
    unsigned int currentSecond;

    // Write the parameters to cout.
    cout << "Seconds to wash one car: " << washTime << endl;
    cout << "Probability of customer arrival during a second: " << arrivalP << endl;
    cout << "Total simulation seconds: " << totalTime << endl;
    for (currentSecond = 1; currentSecond <= totalTime; ++currentSecond)
    {
        //Simulate the passage of one second of time.
        // Check whether a new customer has arrived.
        if (arrival.query())
            arrivalTimes.push(currentSecond);

        // Check whether we can start washing another car.
        if ((!machine.busy()) && (!arrivalTimes.empty( )))
        {
            next = arrivalTimes.front();
            arrivalTimes.pop( );
            waitTimes.next(currentSecond - next);
            machine.wash();
        }
        // Tell the washer to simulate the passage of one second.
        machine.second();
    }
    // Write the summary information about the simulation.
    cout << "Customers served: " << waitTimes.amount() << endl;
    if (waitTimes.amount() > 0)
        cout << "Average wait: " << waitTimes.average( ) << " sec" << endl;

}

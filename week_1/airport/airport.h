//
// Created by Gregory Montilla on 2/22/18.
//

#ifndef AIRPORT_AIRPORT_H
#define AIRPORT_AIRPORT_H

class airport {

public:
    airport();
    void second();
    void set_time(unsigned int t);
    bool busy() const {
        return (time_left > 0);
    }
    void run();
    void simulate(unsigned int takeoff_t, double takeoff_p, unsigned int landing_t, double landing_p, unsigned int fuel,
                  unsigned int total_t);

private:
    unsigned int time;
    unsigned int time_left;

};

class averager {
public:
    averager();
    void next(double value);
    size_t amount() const {
        return count;
    }
    double average() const;

private:
    double sum;
    size_t count;

};

class probability {
public:
    probability(double p = 0.5);
    bool query() const;

private:
    double _probability;
};



#endif //AIRPORT_AIRPORT_H

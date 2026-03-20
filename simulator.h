#ifndef SIMULATOR_H
#define SIMULATOR_H

#include<functional>
using namespace std;

struct Result {
    double mean;
    double variance;
};

class Simulator{
private:
    int num_simulations;
public:
    Simulator(int n);
    
    Result run(function<double()> experiment);
};

#endif
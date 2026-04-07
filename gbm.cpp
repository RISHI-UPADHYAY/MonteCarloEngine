#include "gbm.h"
#include <random>
#include <cmath>

using namespace std;

vector<double> simulate_gbm(double S0, double mu, double sigma, double T, int steps){
    vector<double> path(steps);
    path[0] = S0;

    double dt = T / steps;

    thread_local mt19937 gen(random_device{}());
    normal_distribution<> dist(0.0, 1.0);

    for(int i = 0; i < steps; i++){
        double Z = dist(gen);

        path[i] = path[i-1] * exp((mu - 0.5 * sigma * sigma) * dt + sigma * sqrt(dt) * Z);
    }

    return path;
}
#include "black_scholes.h"
#include <cmath>

using namespace std;

//CDF of standard normal
double norm_cdf(double x){
    return 0.5 * erfc(-x / sqrt(2));
}

double black_scholes_call(double S, double K, double r, double sigma, double T){
    double d1 = (log(S/K) + (r + 0.5*sigma*sigma)*T) / (sigma*sqrt(T));
    double d2 = d1 - sigma*sqrt(T);

    return S*norm_cdf(d1) - K*exp(-r*T) * norm_cdf(d2);
}
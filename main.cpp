#include<iostream>
#include<random>
#include<cmath>
#include<vector>

#include "simulator.h"
#include "gbm.h"
#include "black_scholes.h"

using namespace std;


double compute_dp(int k){
    vector<double> dp(k+1);

    dp[0] = 3.5;

    for(int r = 1; r <= k; r++){
        double sum = 0.0;

        for(int i = 1; i <= 6; i++){
            sum += max((double)i, dp[r-1]);
        }
        dp[r] = sum / 6.0;
    }
    return dp[k];
}

int main(){
    cout << "Dynamic Programming Results\n";
    for(int k = 0; k <= 5; k++){
        double exact = compute_dp(k);
        cout << "Rerolls: " << k << " | DP EV: " << exact << endl;
    }

    cout << "\nMonte Carlo Option Pricing (GBM)\n";

    
    double S0 = 100.0;   // initial price
    double K = 100.0;    // strike
    double r = 0.05;     // risk-free rate
    double sigma = 0.2;  // volatility
    double T = 1.0;      // 1 year
    int steps = 252;     // daily steps

    vector<int> simulations_list = {10000, 100000, 1000000};

    for(int N_sim : simulations_list){

        Simulator sim(N_sim);

        // Monte Carlo experiment
        auto experiment = [&]() {

            auto path = simulate_gbm(S0, r, sigma, T, steps);
            double ST = path.back();

            double payoff = max(ST - K, 0.0);

            // discount payoff
            return exp(-r * T) * payoff;
        };

        Result res = sim.run(experiment);

        double std_dev = sqrt(res.variance);
        double margin = 1.96 * std_dev / sqrt(N_sim);

        // Black-Scholes benchmark
        double bs_price = black_scholes_call(S0, K, r, sigma, T);

        cout << "\n----------------------------------\n";
        cout << "Simulations: " << N_sim << endl;

        cout << "Monte Carlo Price: " << res.mean << endl;
        cout << "Black-Scholes Price: " << bs_price << endl;

        cout << "Relative Error: "
             << abs(res.mean - bs_price) / bs_price << endl;

        cout << "Std Dev: " << std_dev << endl;

        cout << "95% Confidence Interval: ["
             << res.mean - margin << ", "
             << res.mean + margin << "]\n";
    }

    return 0;
}
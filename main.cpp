#include<iostream>
#include<random>
#include<cmath>
#include<vector>
#include "simulator.h"

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
    int N = 1000000;
    Simulator sim(N);

    cout<<"Dynamic Programming Results";
    for(int k = 0; k <= 5; k++){
        double exact = compute_dp(k);
        cout<<"Rerolls: "<<k<<" | DP EV: "<<exact<<endl;
    }

    cout<<"Monte Carlo Simulation"<<endl;
    for(int k = 1; k <= 6; k++){

        //Lambda function 
        auto experiment = [k]() {
            thread_local mt19937 gen(random_device{}());
            uniform_int_distribution<> dist(1, 6);

            int best = 0;
            for(int i = 0; i <= k; i++){
                int roll = dist(gen);
                if(roll > best) best = roll;
            }
            return (double)best;
        };

        Result res = sim.run(experiment);

        double std_dev = sqrt(res.variance);

        //95% confidence interval
        double margin = 1.96 * std_dev / sqrt(N);

        cout<<"Threshold "<<k<<endl;
        cout<<"EV: "<<res.mean<<endl;
        cout<<"Std Dev: "<<std_dev<<endl;
        cout<<"95% CI: ["
            <<res.mean - margin<<", "
            <<res.mean + margin<<"]"<<endl;
    }
    return 0;
}
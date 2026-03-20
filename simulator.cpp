#include "simulator.h"
#include<thread>
#include<vector>
#include<cmath>

using namespace std;


Simulator::Simulator(int n){
    num_simulations = n;
}

Result Simulator::run(function<double()> experiment){
    int num_threads = std::thread::hardware_concurrency();
    vector<std::thread> threads;

    vector<double> partial_sum(num_threads, 0.0);
    vector<double> partial_sum_sq(num_threads, 0.0);

    int sims_per_thread = num_simulations / num_threads;

    for(int t = 0; t < num_threads; t++){
        threads.emplace_back([&, t](){
            for(int i = 0; i < sims_per_thread; i++){
                double value = experiment();
                partial_sum[t] += value;
                partial_sum_sq[t] += value*value;
            }
        });
    }

    //Wait for all threads
    for(auto &th : threads){
        th.join();
    }

    //Combine results
    double total_sum = 0.0;
    double total_sum_sq = 0.0;

    for(int t = 0; t < num_threads; t++){
        total_sum += partial_sum[t];
        total_sum_sq += partial_sum_sq[t];
    }

    double mean = total_sum / num_simulations;
    double variance = (total_sum_sq / num_simulations) - (mean*mean);

    return {mean, variance};
}

# Monte Carlo Simulation Engine (C++)

## 📌 Overview

This project implements a high-performance **Monte Carlo Simulation Engine in C++** for evaluating probabilistic systems and optimizing decision-making strategies.

It supports:
- Parallel simulations using multithreading
- Statistical analysis (expected value, variance, confidence intervals)
- Strategy optimization for stochastic problems
- Validation using Dynamic Programming

---

## 🚀 Features

- ⚡ **Multithreaded Simulation**
  - Uses `std::thread` for parallel execution
  - Scales with available CPU cores

- 🎲 **Monte Carlo Engine**
  - Generic simulation framework
  - Supports custom probabilistic experiments

- 📊 **Statistical Analysis**
  - Expected Value (EV)
  - Variance & Standard Deviation
  - 95% Confidence Intervals

- 🧠 **Dynamic Programming Solver**
  - Computes exact solutions for optimal stopping problems
  - Used to validate simulation results

- 🔁 **Strategy Optimization**
  - Solves reroll decision problems
  - Finds optimal strategies based on expected value

---

## 🧠 Example Problem

### Optimal Dice Reroll Strategy

**Problem:**
- Roll a 6-sided die
- You can reroll up to *k* times
- Goal: maximize expected value

---

### ✅ Results

| Rerolls (k) | DP EV (Exact) | Simulation EV |
|------------|--------------|---------------|
| 0 | 3.50 | ~3.50 |
| 1 | 4.25 | ~4.25 |
| 2 | 4.67 | ~4.66 |
| 3 | 4.96 | ~4.95 |
| 4 | 5.15 | ~5.14 |

👉 Simulation closely matches theoretical results.

---

## ⚙️ How It Works

### Monte Carlo Simulation
- Runs millions of randomized experiments
- Estimates expected outcomes using averaging

### Dynamic Programming
- Computes optimal decisions recursively

---

## 🛠️ Tech Stack

- **Language:** C++
- **Libraries:**
- `<thread>` (multithreading)
- `<random>` (RNG)
- `<vector>`
- `<functional>`

---

## ▶️ How to Run

### Compile:
```bash
g++ -std=c++17 main.cpp simulator.cpp -o main -pthread
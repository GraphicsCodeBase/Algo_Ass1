#include <iostream>
#include <string>
#include "algo.hpp"
//=============================================================
// PROBLEM: Efficient Fault Detection in International MRT Networks
//
// Urban mass transit systems (Singapore: 150+ stations, Japan: 1000+ 
// stations) require efficient fault detection algorithms. Given the 
// monotonic ordering where non-faulty stations precede faulty ones,
// design an O(log n) solution to identify the first faulty station.
//
// OBJECTIVES:
// 1. Handle network sizes from 150 to 1000+ stations efficiently
// 2. Minimize station checks using binary search approach
// 3. Demonstrate logarithmic complexity through empirical analysis
// 4. Provide scalable solution for future network expansions
//
// APPROACH:
// 1. Load country-specific station datasets
// 2. Simulate fault propagation maintaining monotonic ordering
// 3. Implement binary search with O(log n) complexity
// 4. Validate with comparison counting and benchmarking
//=============================================================

std::string japan_station_file = "../../src/japan_station.txt";
std::string singapore_station_file = "../../src/singapore_station.txt";
int main() {
    Algo algo;
    //algo.initialize_stations();
    algo.benchmark_find_faulty_station_binary(singapore_station_file,1000);
    // algo.random_faulty_station();
    // //algo.print_stations();
    // //algo.find_faulty_station();
    return 0;
}
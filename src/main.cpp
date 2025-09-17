#include <iostream>
#include <string>
#include "algo.hpp"
//=============================================================
// PROBLEM: Efficient Fault Detection in International MRT Networks
//
// Urban mass transit systems (e.g., Singapore: 150+ stations, Japan: 1000+ 
// stations) require efficient fault detection algorithms. Given a 
// monotonic ordering where all non-faulty stations precede the first 
// faulty station, design an O(log n) solution to identify the threshold
// station where faults start.
//
// OBJECTIVES:
// 1. Handle network sizes from 150 to 1,000,000+ stations efficiently
// 2. Minimize station checks using a predicate-based binary search
// 3. Demonstrate logarithmic complexity through empirical benchmarking
// 4. Provide scalable solution for future network expansions
//
// APPROACH:
// 1. Generate or load sorted station datasets
// 2. Simulate fault propagation by randomly choosing a threshold
//    station, marking it and all subsequent stations as faulty
// 3. Implement binary search to locate the first faulty station
// 4. Validate correctness and measure search performance across
//    varying dataset sizes
//=============================================================


//file path to the txt files.
std::string japan_station_file = "../../src/japan_station.txt";
std::string singapore_station_file = "../../src/singapore_station.txt";
std::string onemillion_station_file = "../../src/OneMillion.txt";
std::string one_thousand_station_file = "../../src/OneThousand.txt";
std::string ten_station_file = "../../src/ten_Stations.txt";
std::string hundred_station_file = "../../src/hundred_Stations.txt";

int main() {
    Algo algo;
    std::cout << 
        "==============================================================\n"
        "Station Fault Detection Benchmark\n"
        "--------------------------------------------------------------\n"
        "This simulation benchmarks algorithms for finding the first\n"
        "faulty station within a dataset.\n\n"
        "The program generates a list of stations sorted by ID (all healthy\n"
        "by default). For each trial, a random threshold station is chosen\n"
        "and all stations from that point onward are marked faulty.\n\n"
        "The binary search algorithm is then applied to efficiently locate\n"
        "the first faulty station in the dataset.\n\n"
        "The benchmark runs the search across different dataset sizes\n"
        "(e.g., 10, 100, 1,000, 10,000, ... up to 1,000,000) to measure\n"
        "performance and visualize how the algorithm scales with input size.\n\n"
        "Goal: Compare execution time and verify the expected O(log n)\n"
        "behavior of binary search on a predicate (finding the first true).\n"
        "==============================================================\n"
    << std::endl;

    algo.benchmark_find_faulty_station_binary(ten_station_file, 10);
    algo.benchmark_find_faulty_station_binary(hundred_station_file, 10);
    algo.benchmark_find_faulty_station_binary(one_thousand_station_file, 10);
    algo.benchmark_find_faulty_station_binary(onemillion_station_file, 10);
    return 0;
}
#include <iostream>
#include "algo.hpp"
//=============================================================
// Problem Statement:
// In the Singapore MRT network, stations occasionally experience technical faults. 
// For efficient maintenance, it is important to quickly identify the first faulty station along a line. 
// We assume that stations are arranged such that all non-faulty stations appear before any faulty stations, creating a monotonic ordering. 
// The goal is to design an algorithm that finds the first faulty station efficiently, minimizing the number of checks required. 
// This allows maintenance teams to respond faster while reducing computational effort.
//=============================================================
int main() {
    //this is a test :)
    std::cout << "Hello, World!" << std::endl;

    Algo algo;
    algo.initialize_stations();
    algo.random_faulty_station();
    algo.print_stations();
    algo.find_faulty_station();
    return 0;
}
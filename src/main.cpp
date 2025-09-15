#include <iostream>
#include "algo.hpp"


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
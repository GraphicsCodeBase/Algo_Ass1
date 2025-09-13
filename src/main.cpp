#include <iostream>
#include "algo.hpp"


int main() {
    //this is a test :)
    std::cout << "Hello, World!" << std::endl;

    Algo algo;
    algo.initalise_stations();
    algo.random_faulty_station();
    algo.print_stations();

    return 0;
}
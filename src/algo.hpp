#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
//this is to hold the station struct data
struct Station{
    std::string name; // name of station
    bool faulty;     //check if faulty or not.
};


class Algo {
    public :

    void initialize_stations();
    void random_faulty_station();
    void find_faulty_station();
    void find_faulty_station_binary();
    void print_stations();
    void print_performance_analysis();

    protected:
    //holding the list of stations.
    std::vector<Station> stations;
};
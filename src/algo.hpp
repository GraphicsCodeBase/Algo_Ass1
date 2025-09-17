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
    std::string find_faulty_station_binary();
    void print_stations();
    void print_performance_analysis();
    void benchmark_find_faulty_station_binary(std::string file_Path , int iterations = 1000);
    void initialize_stations_from_file(const std::string& filename);
    void generate_large_station_list(int count, std::string& fileName);

    void generateStationsWithThreshold(std::vector<Station>& stations, int numStations);
    int find_faulty_station_threshold(int& comparisons);
    void reset();

    //holding the list of stations.
    std::vector<Station> stations;

};
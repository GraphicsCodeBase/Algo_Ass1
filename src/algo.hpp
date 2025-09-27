#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <string>
//this is to hold the station struct data
struct Station{
    std::int64_t id;
    std::string name; // name of station
    bool faulty;     //check if faulty or not.
};


class Algo {
    public :
    //interpolation search functions 
    void loadStations(std::string file_path);
    int setRandomFaultyStation();
    int interpolationSearch(int64_t targetID, int& probes);
    void benchmarkInterpolationSearch(int targetID);
    //void generateNonUniformStations(const std::string& filepath, int numStations, int minGap = 1, int maxGap = 50);
    void generateSequentialStations(const std::string& filepath, int limit);
    void generateHighlyNonUniformStations(const std::string &filepath, int numStations);
    int64_t generateHardTarget();
    int64_t generateHardExistingTarget();
    int64_t pickTargetFromStations();
    void clearStations();
    private:
    //holding the list of stations.
    std::vector<Station> stations;
    std::mt19937 gen;  // RNG reused
};
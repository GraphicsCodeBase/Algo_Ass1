#include <iostream>
#include <vector>
#include <random>
//this is to hold the station struct data
struct Station{
    std::string name; // name of station
    bool faulty;     //check if faulty or not.
};


class Algo {
    public :

    void initalise_stations();
    void random_faulty_station();
    void find_faulty_station();
    void print_stations();

    private:
    //holding the list of stations.
    std::vector<Station> stations;
};
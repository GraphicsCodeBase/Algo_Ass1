#include "algo.hpp"

void Algo::initalise_stations()
{
    stations = {
        {"Jurong East", false},
        {"Bukit Batok", false},
        {"Bukit Gombak", false},
        {"Choa Chu Kang", false},
        {"Yew Tee", false},
        {"Kranji", false},
        {"Marsiling", false},
        {"Woodlands", false},
        {"Admiralty", false},
        {"Sembawang", false},
        {"Canberra", false},
        {"Yishun", false},
        {"Khatib", false},
        {"Yio Chu Kang", false},
        {"Ang Mo Kio", false},
        {"Bishan", false},
        {"Braddell", false},
        {"Toa Payoh", false},
        {"Novena", false},
        {"Newton", false},
        {"Orchard", false},
        {"Somerset", false},
        {"Dhoby Ghaut", false},
        {"City Hall", false},
        {"Raffles Place", false},
        {"Marina Bay", false},
        {"Marina South Pier", false},
        {"Pasir Ris", false},
        {"Tampines", false},
        {"Simei", false},
        {"Tanah Merah", false},
        {"Bedok", false},
        {"Kembangan", false},
        {"Eunos", false},
        {"Paya Lebar", false},
        {"Aljunied", false},
        {"Kallang", false},
        {"Lavender", false},
        {"Bugis", false},
        {"Tanjong Pagar", false},
        {"Outram Park", false},
        {"Tiong Bahru", false},
        {"Redhill", false},
        {"Queenstown", false},
        {"Commonwealth", false},
        {"Buona Vista", false},
        {"Dover", false},
        {"Clementi", false},
        {"Chinese Garden", false},
        {"Lakeside", false},
        {"Boon Lay", false},
        {"Pioneer", false},
        {"Joo Koon", false},
        {"Gul Circle", false},
        {"Tuas Crescent", false},
        {"Tuas West Road", false},
        {"Tuas Link", false},
        {"Expo", false},
        {"Changi Airport", false},
        {"HarbourFront", false},
        {"Chinatown", false},
        {"Clarke Quay", false},
        {"Little India", false},
        {"Farrer Park", false},
        {"Boon Keng", false},
        {"Potong Pasir", false},
        {"Woodleigh", false},
        {"Serangoon", false},
        {"Kovan", false},
        {"Hougang", false},
        {"Buangkok", false},
        {"Sengkang", false},
        {"Punggol", false},
        {"Bras Basah", false},
        {"Esplanade", false},
        {"Promenade", false},
        {"Nicoll Highway", false},
        {"Stadium", false},
        {"Mountbatten", false},
        {"Dakota", false},
        {"Tai Seng", false},
        {"Bartley", false},
        {"Lorong Chuan", false},
        {"Marymount", false},
        {"Caldecott", false},
        {"Botanic Gardens", false},
        {"Farrer Road", false},
        {"Holland Village", false},
        {"one-north", false},
        {"Kent Ridge", false},
        {"Haw Par Villa", false},
        {"Pasir Panjang", false},
        {"Labrador Park", false},
        {"Telok Blangah", false},
        {"Bayfront", false},
        {"Downtown", false},
        {"Telok Ayer", false},
        {"Fort Canning", false},
        {"Bencoolen", false},
        {"Jalan Besar", false},
        {"Bendemeer", false},
        {"Geylang Bahru", false},
        {"Mattar", false},
        {"Bedok North", false},
        {"Bedok Reservoir", false},
        {"Tampines West", false},
        {"Tampines East", false},
        {"Upper Changi", false},
        {"Gardens by the Bay", false},
        {"Tanjong Rhu", false},
        {"Katong Park", false},
        {"Tanjong Katong", false},
        {"Marine Parade", false},
        {"Marine Terrace", false},
        {"Siglap", false},
        {"Bayshore", false}
    };
}

void Algo::random_faulty_station()
{
    if (stations.empty())
    {
        return;
    }

    // random number generator seeded once per call
    static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<size_t> dist(0, stations.size() - 1);

    size_t randomIndex = dist(rng);
    stations[randomIndex].faulty = true;

    // optional: debug print
    // std::cout << "Station " << stations[randomIndex].name 
    //           << " is now faulty!" << std::endl;
}

void Algo::find_faulty_station()
{
    //use an algorithm to find the faulty station.
}

void Algo::print_stations()
{
    for (const auto& station : stations)
    {
        std::cout << "Station Name: " << station.name 
                  << ", Faulty: " << (station.faulty ? "Yes" : "No") << std::endl;
    }
}

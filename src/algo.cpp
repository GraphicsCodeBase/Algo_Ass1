#include "algo.hpp"
#include <algorithm>
#include <chrono>

void Algo::initialize_stations()
{
    //all stattions initalised to not faulty.
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

    //set a random station to faulty (true).
    size_t randomIndex = dist(rng);
    stations[randomIndex].faulty = true;

    // optional: debug print
    // std::cout << "Station " << stations[randomIndex].name 
    //           << " is now faulty!" << std::endl;
}

void Algo::find_faulty_station()
{
    // Main method that demonstrates both algorithms
    std::cout << "\n=== FAULTY STATION DETECTION ===" << std::endl;
        
    // Binary Search (requires sorting first)
    std::cout << "\n2. Binary Search Algorithm:" << std::endl;
    find_faulty_station_binary();
    
    // Performance Analysis
    print_performance_analysis();
}

std::string Algo::find_faulty_station_binary()
{
   if (stations.empty()) return "";

    std::vector<Station> sorted_stations = stations;
    std::stable_sort(sorted_stations.begin(), sorted_stations.end(),
                     [](const Station& a, const Station& b) {
                         return a.faulty < b.faulty;
                     });

    int left = 0;
    int right = (int)sorted_stations.size() - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (sorted_stations[mid].faulty) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    if (sorted_stations[left].faulty) {
        return sorted_stations[left].name; // return name instead of index
    }
    return "";
}

void Algo::print_performance_analysis()
{
    std::cout << "\n=== PERFORMANCE ANALYSIS ===" << std::endl;
    std::cout << "Total stations: " << stations.size() << std::endl;
    std::cout << "\nAlgorithm Comparison:" << std::endl;
    
    std::cout << "\n2. Binary Search:" << std::endl;
    std::cout << "   - Time Complexity: O(log n) + O(n log n) for sorting" << std::endl;
    std::cout << "   - Space Complexity: O(n) for sorted copy" << std::endl;
    std::cout << "   - Best Case: O(log n) - if data is pre-sorted" << std::endl;
    std::cout << "   - Worst Case: O(n log n) - due to sorting requirement" << std::endl;
    std::cout << "   - Note: Binary search is not optimal for this problem since" << std::endl;
    std::cout << "     we're searching for a boolean property, not a sorted value" << std::endl;
    
    std::cout << "\nRecommendation:" << std::endl;
    std::cout << "For this specific problem, Linear Search is more efficient" << std::endl;
    std::cout << "because we're looking for a boolean property (faulty/not faulty)" << std::endl;
    std::cout << "rather than searching for a specific value in a sorted array." << std::endl;
}

void Algo::benchmark_find_faulty_station_binary(int iterations)
{
    using namespace std::chrono;

    //return if stations container is empty.
    if (stations.empty()) {
            std::cout << "No stations available for benchmarking." << std::endl;
            return;
        }

    nanoseconds total_time(0);
        for (int t = 0; t < iterations; ++t) {
        initialize_stations();       // reset all to not faulty
        random_faulty_station();    // mark one as faulty

        auto start = std::chrono::high_resolution_clock::now();
        find_faulty_station_binary();
        auto end = std::chrono::high_resolution_clock::now();

        total_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    }
    //bench mark and print out the stats.
    double avg_ns = static_cast<double>(total_time.count()) / iterations;

    std::cout << "Benchmark results over " << iterations << " trials:\n";
    std::cout << "  Avg time: " << avg_ns << " ns"
              << " (" << (avg_ns / 1000.0) << " µs, "
              << (avg_ns / 1e6) << " ms)" << std::endl;
}

void Algo::print_stations()
{
    for (const auto& station : stations)
    {
        std::cout << "Station Name: " << station.name 
                  << ", Faulty: " << (station.faulty ? "Yes" : "No") << std::endl;
    }
}

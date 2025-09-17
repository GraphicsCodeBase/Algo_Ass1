#include "algo.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <string>

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

void Algo::benchmark_find_faulty_station_binary(std::string file_Path, int iterations)
{
    using namespace std::chrono;
    long long total_comparisons = 0;
    // First load the stations from file
    initialize_stations_from_file(file_Path);
    
    // Now check if stations were actually loaded
    if (stations.empty()) {
        std::cout << "No stations available for benchmarking. File: " << file_Path << std::endl;
        return;
    }

    nanoseconds total_time(0);
    
    for (int t = 0; t < iterations; ++t) {
        // Reset all stations to not faulty for this iteration
        reset();
        
        // Mark one random station as faulty
        generateStationsWithThreshold(stations, static_cast<int>(stations.size()));

        int compare_count = 0;
        auto start = high_resolution_clock::now();
        int index = find_faulty_station_threshold(compare_count);
        auto end = high_resolution_clock::now();

        total_time += duration_cast<nanoseconds>(end - start);
        total_comparisons += compare_count;
    }

    // Benchmark and print out the stats
    double avg_ns = static_cast<double>(total_time.count()) / iterations;
    // Average comparisons
    double avg_comparisons = static_cast<double>(total_comparisons) / iterations;
    std::cout << "Benchmark results for: " << file_Path << "\n";
    std::cout << "Stations count: " << stations.size() << "\n";
    std::cout << "Iterations: " << iterations << "\n";
    std::cout << "Avg time: " << avg_ns << " ns"
              << " (" << (avg_ns / 1000.0) << " µs, "
              << (avg_ns / 1e6) << " ms)" << std::endl;
    std::cout << "Avg comparisons: " << avg_comparisons << "\n";
    std::cout << "Expected max comparisons (log2 n): "
            << std::ceil(std::log2(stations.size())) << "\n";
}

void Algo::initialize_stations_from_file(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << "\n";
        return;
    }

    stations.clear();
    std::string line;

    while (std::getline(file, line)) {
        // Trim spaces at start and end
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (line.empty()) continue; // skip empty lines

        stations.push_back({ line, false }); // all stations not faulty
    }

    file.close();
}

void Algo::generate_large_station_list(int count, std::string &fileName)
{
     std::ofstream out(fileName);
    if (!out.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        Station s;
        s.name = "Station" + std::to_string(i);
        s.faulty = false;

        // Write as "StationName false"
        out << s.name << " " << (s.faulty ? "true" : "false") << "\n";
    }

    out.close();
    std::cout << "Generated " << count << " stations into " << fileName << std::endl;
}

void Algo::generateStationsWithThreshold(std::vector<Station> &stations, int numStations)
{
    stations.clear();
    stations.reserve(numStations);

    // Fill stations with names and all false
    for (int i = 0; i < numStations; ++i) {
        stations.push_back({ "Station" + std::to_string(i), false });
    }

    // Pick a random threshold index
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, numStations - 1);
    int threshold = dis(gen);

    // Mark all stations from threshold onward as faulty
    for (int i = threshold; i < numStations; ++i) {
        stations[i].faulty = true;
    }

    std::cout << "Threshold index: " << threshold << " (" << stations[threshold].name << ")\n";
}

int Algo::find_faulty_station_threshold(int& comparisons)
{
    int left = 0;
    int right = static_cast<int>(stations.size()) - 1; // vector size is size_t, cast to int
    int result = -1; // stores index of first faulty station
    comparisons = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparisons++; // counting the mid check
        if (stations[mid].faulty) {
            // Possible first faulty station
            result = mid;
            // Look left to find an earlier faulty
            right = mid - 1;
        } else {
            // No fault here, move right
            left = mid + 1;
        }
    }

    return result; // -1 if no faulty station
}

void Algo::print_stations()
{
    for (const auto& station : stations)
    {
        std::cout << "Station Name: " << station.name 
                  << ", Faulty: " << (station.faulty ? "Yes" : "No") << std::endl;
    }
    std::cout << "Total stations: " << stations.size() << std::endl;
}

void Algo::reset()
{
    for (auto& station : stations) {
        station.faulty = false;
    }
}
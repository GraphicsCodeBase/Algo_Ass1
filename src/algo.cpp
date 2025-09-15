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

void Algo::find_faulty_station_binary()
{
    if (stations.empty()) {
        std::cout << "No stations available for search." << std::endl;
        return;
    }

    // Sort by faulty flag so predicate is monotonic: all false then all true.
    std::vector<Station> sorted_stations = stations;
    std::stable_sort(sorted_stations.begin(), sorted_stations.end(),
                     [](const Station& a, const Station& b) {
                         if (a.faulty == b.faulty) return false;
                         return (!a.faulty && b.faulty);
                     });

    // previous single-run timing replaced with repeated trials for accuracy
    const int trials = 1000; // increase if you need smoother averages
    {
        std::vector<Station> warm = stations;
        std::stable_sort(warm.begin(), warm.end(),
                         [](const Station& a, const Station& b) {
                             if (a.faulty == b.faulty) return false;
                             return (!a.faulty && b.faulty);
                         });
        // run one binary-search to warm caches
        int l = 0, r = static_cast<int>(warm.size()) - 1;
        while (l < r) {
            int m = l + (r - l) / 2;
            if (warm[m].faulty) r = m; else l = m + 1;
        }
    }

    std::chrono::nanoseconds total_duration(0);
    long long total_comparisons = 0;
    int last_found_index = -1;

    for (int t = 0; t < trials; ++t) {
        std::vector<Station> sorted_stations = stations; // sort cost included if that matches your scenario

        auto start_time = std::chrono::high_resolution_clock::now();

        std::stable_sort(sorted_stations.begin(), sorted_stations.end(),
                         [](const Station& a, const Station& b) {
                             if (a.faulty == b.faulty) return false;
                             return (!a.faulty && b.faulty);
                         });

        int left = 0;
        int right = static_cast<int>(sorted_stations.size()) - 1;
        int faulty_index_local = -1;
        int comparisons_local = 0;

        while (left < right) {
            ++comparisons_local;
            int mid = left + (right - left) / 2;
            if (sorted_stations[mid].faulty) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        if (!sorted_stations.empty() && sorted_stations[left].faulty) {
            faulty_index_local = left;
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        total_duration += std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        total_comparisons += comparisons_local;
        last_found_index = faulty_index_local;
    }

    double avg_ns = static_cast<double>(total_duration.count()) / trials;
    double avg_comparisons = static_cast<double>(total_comparisons) / trials;

    if (last_found_index != -1) {
        std::cout << "✓ Found faulty station: " << sorted_stations[last_found_index].name
                  << " at sorted index " << last_found_index << std::endl;
        std::cout << "  Avg comparisons: " << avg_comparisons << std::endl;
        std::cout << "  Avg time per trial: " << avg_ns << " ns"
                  << " (" << (avg_ns / 1000.0) << " µs, " << (avg_ns / 1e6) << " ms)" << std::endl;
        std::cout << "  Time Complexity: O(n log n) for sorting + O(log n) for search" << std::endl;
    } else {
        std::cout << "✗ No faulty station found!" << std::endl;
    }
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

void Algo::print_stations()
{
    for (const auto& station : stations)
    {
        std::cout << "Station Name: " << station.name 
                  << ", Faulty: " << (station.faulty ? "Yes" : "No") << std::endl;
    }
}

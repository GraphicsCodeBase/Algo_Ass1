#include <iostream>
#include <string>
#include "algo.hpp"
#include "bucket_sort.hpp"
//file path to the txt files.
std::string japan_station_file = "../../src/japan_station.txt";
std::string singapore_station_file = "../../src/singapore_station.txt";
std::string onemillion_station_file = "../../src/OneMillion.txt";
std::string one_thousand_station_file = "../../src/OneThousand.txt";
std::string ten_station_file = "../../src/ten_Stations.txt";
std::string hundred_station_file = "../../src/hundred_Stations.txt";
std::string random_station_file = "../../src/randomStations.txt";
std::string thousand_numbers_file = "../../../src/thousand.txt";

int main() {
    Algo algo;
    // Load stations from file
    algo.generateHighlyNonUniformStations(random_station_file,1000000);
    algo.loadStations("../../src/randomStations.txt");
    // Set a random faulty station
    int targetID = algo.generateHardTarget();
    
    std::cout << "Benchmarking Interpolation Search for target ID: " << targetID << std::endl;
    algo.benchmarkInterpolationSearch(targetID);  


    // ===== BUCKET SORT TESTING =====
    std::cout << "\n\n2. BUCKET SORT TESTING" << std::endl;
    std::cout << "======================" << std::endl;

    BucketSort bucketSorter;


    std::cout << "Loading numbers from: " << thousand_numbers_file << std::endl;
    bucketSorter.loadFromFile(thousand_numbers_file);
    std::cout << "Loaded " << bucketSorter.getNumberCount() << " numbers." << std::endl;

    // Perform bucket sort
    std::cout << "\nPerforming bucket sort" << std::endl;
    bucketSorter.bucketSort();


    const auto& sortedNumbers = bucketSorter.getNumbers();
    bool isSorted = true;
    for (size_t i = 1; i < sortedNumbers.size(); i++) {
        if (sortedNumbers[i - 1] > sortedNumbers[i]) {
            isSorted = false;
            break;
        }
    }

    if (isSorted) {
        std::cout << " Bucket sort completed successfully" << std::endl;
        std::cout << "First 10 sorted numbers: ";
        for (int i = 0; i < 10 && i < static_cast<int>(sortedNumbers.size()); i++) {
            std::cout << sortedNumbers[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "Last 10 sorted numbers: ";
        int start = std::max(0, static_cast<int>(sortedNumbers.size()) - 10);
        for (int i = start; i < static_cast<int>(sortedNumbers.size()); i++) {
            std::cout << sortedNumbers[i] << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << " Bucket sort failed" << std::endl;
    }

    // Run benchmark
    std::cout << "\nRunning bucket sort benchmark." << std::endl;
    bucketSorter.benchmark(20);  // Run 20 iterations for benchmarking

    std::cout << "\n=== TESTING COMPLETE ===" << std::endl;

    return 0;
}
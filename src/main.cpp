#include <iostream>
#include <string>
#include "algo.hpp"
#include "bucket_sort.hpp"
#include "transport.hpp"
//file path to the txt files.
std::string random_station_file = "../../src/randomStations.txt";
std::string thousand_numbers_file = "../../src/thousand.txt";
//hundred entries
std::string hundred_Uniform_file = "../../src/hundred_Uniform.txt";
std::string hundred_NonUniform_file = "../../src/hundred_NonUniform.txt";
//thousand entries.
std::string thousand_Uniform_file = "../../src/thousand_uniform.txt";
std::string thousand_NonUniform_file = "../../src/thousand_nonUniform.txt";
//ten thousand entries.
std::string ten_thousand_Uniform_file = "../../src/ten_thousand_uniform.txt";
std::string ten_thousand_NonUniform_file = "../../src/ten_thousand_nonUniform.txt";
int main() {
    Algo algo;
    int targetID = 0;
    // ===== INTERPOLATION SEARCH TESTING =====
    std::cout << "\n\n1. INTERPOLATION SEARCH TESTING" << std::endl;
    std::cout << "======================" << std::endl;

    //Test for 100 sequential entries
    algo.loadStations(hundred_Uniform_file);
    // Set a random faulty station
    targetID = algo.pickTargetFromStations();
    std::cout << "Benchmarking Interpolation Search for target ID: " << targetID << std::endl;
    algo.benchmarkInterpolationSearch(targetID);  
    algo.clearStations();

    //Test for 100 non-uniform entries
    algo.loadStations(hundred_NonUniform_file);
    // Set a random faulty station
    targetID = algo.pickTargetFromStations();
    std::cout << "Benchmarking Interpolation Search for target ID: " << targetID << std::endl;
    algo.benchmarkInterpolationSearch(targetID);  
    algo.clearStations();

    //Test for 1000 non-uniform entries
    algo.loadStations(thousand_Uniform_file);
    // Set a random faulty station
    targetID = algo.pickTargetFromStations();
    std::cout << "Benchmarking Interpolation Search for target ID: " << targetID << std::endl;
    algo.benchmarkInterpolationSearch(targetID);  
    algo.clearStations();

    //Test for 1000 non-uniform entries
    algo.loadStations(thousand_NonUniform_file);
    // Set a random faulty station
    targetID = algo.pickTargetFromStations();
    std::cout << "Benchmarking Interpolation Search for target ID: " << targetID << std::endl;
    algo.benchmarkInterpolationSearch(targetID);  
    algo.clearStations();

     //Test for 10000 non-uniform entries
    algo.loadStations(ten_thousand_Uniform_file);
    // Set a random faulty station
    targetID = algo.pickTargetFromStations();
    std::cout << "Benchmarking Interpolation Search for target ID: " << targetID << std::endl;
    algo.benchmarkInterpolationSearch(targetID);  
    algo.clearStations();

     //Test for 10000 non-uniform entries
    algo.loadStations(ten_thousand_NonUniform_file);
    // Set a random faulty station
    targetID = algo.pickTargetFromStations();
    std::cout << "Benchmarking Interpolation Search for target ID: " << targetID << std::endl;
    algo.benchmarkInterpolationSearch(targetID);  
    algo.clearStations();

    //Test for 1000000 non-uniform entries
    algo.loadStations(random_station_file);
    // Set a random faulty station
    targetID = algo.pickTargetFromStations();
    std::cout << "Benchmarking Interpolation Search for target ID: " << targetID << std::endl;
    algo.benchmarkInterpolationSearch(targetID);  
    algo.clearStations();
    std::cout << "======================" << std::endl;
    std::cout << "INTERPOLATION SEARCH TESTING END" << std::endl;
    std::cout << "======================" << std::endl;

   // ===== INTERPOLATION SEARCH TESTING END =====
    std::cout << "\nRecursive Subset Sum Count Testing" << std::endl;
    std::vector<int> arr1 = {1, 2, 3, 4, 5};
    std::vector<int> arr2 = {2, 3, 5, 6, 8, 10};
    std::vector<int> arr3 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> arr4 = {1, 2, 3, 4, 5, 6};

    algo.benchmarkSubsetSum(arr1, 5);   // subsets that sum to 5
    algo.benchmarkSubsetSum(arr2, 10);  // subsets that sum to 10
    algo.benchmarkSubsetSum(arr3, 15);  // subsets that sum to 15
    algo.benchmarkSubsetSum(arr4, 7);  // subsets that sum to 7
    std::cout << "======================" << std::endl;
    std::cout << "Recursive Subset Sum Count Testing END" << std::endl;
    std::cout << "======================" << std::endl;


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

    std::cout << std::endl;
    std::cout << "==============================" << std::endl;
	std::cout << "TRANSPORT NETWORK OPTIMIZATION" << std::endl;
	std::cout << "==============================" << std::endl;

    std::vector<int> test_sizes = { 4, 8, 16 };

    for (int size : test_sizes) {
        std::cout << "Network size: " << size << "x" << size << std::endl;

        SingaporeTransportOptimizer optimizer(size);
        auto network = SingaporeTransportOptimizer::generateNetwork(size);

        auto start = std::chrono::high_resolution_clock::now();
        int result = optimizer.optimizeTransport(network);
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Optimization result: " << result << std::endl;
        std::cout << "Execution time: " << duration.count() << " microseconds\n" << std::endl;
    }

    // Complexity analysis
    SingaporeTransportOptimizer analyzer(16);
    analyzer.analyzeComplexity();

    std::cout << "==================================" << std::endl;
    std::cout << "TRANSPORT NETWORK OPTIMIZATION END" << std::endl;
    std::cout << "==================================" << std::endl;

    return 0;
}
#include <gtest/gtest.h>
#include <iostream>
#include <chrono>
#include "../src/algo.hpp"

//the class will inhherit from the test framework of GTest.
class AlgoTest : public ::testing::Test{

protected :
    Algo algo;

    void SetUp() override
    {
        // This runs before each test
        //this will set every station to not faulty.(false)
        algo.initialize_stations();
    }

     void TearDown() override {
        // This runs after each test (optional here)
        //thinking if i need to call the desctructor or not.
    }
};

TEST_F(AlgoTest, Single_Run_Nano)
{
    algo.random_faulty_station();

    auto start = std::chrono::high_resolution_clock::now();
    std::string faulty = algo.find_faulty_station_binary();
    auto end = std::chrono::high_resolution_clock::now();

    // Measure in nanoseconds
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    // 1. Check correctness
    ASSERT_FALSE(faulty.empty());
    auto it = std::find_if(algo.stations.begin(), algo.stations.end(),
                           [&](const Station& s) { return s.name == faulty; });
    ASSERT_NE(it, algo.stations.end());
    ASSERT_TRUE(it->faulty);

    // 2. Print / check nanoseconds
    std::cout << "Binary search took " << elapsed_ns << " ns\n";

    // Optional: enforce an upper bound
    EXPECT_LT(elapsed_ns, 1000000) << "Binary search took too long!"; // e.g., 1 ms = 1,000,000 ns
}

TEST_F(AlgoTest, Twenty_Runs)
{
    const int num_runs = 20;
    int successes = 0;
    long long total_ns = 0;

    for (int i = 0; i < num_runs; ++i) {
        algo.initialize_stations();      // reset all stations to non-faulty
        algo.random_faulty_station();    // randomly set one station to faulty

        auto start = std::chrono::high_resolution_clock::now();
        std::string faulty_name = algo.find_faulty_station_binary(); // or return index
        auto end = std::chrono::high_resolution_clock::now();

        auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        total_ns += elapsed_ns;

        // Check if the returned station is actually faulty
        auto it = std::find_if(algo.stations.begin(), algo.stations.end(),
                               [&](const Station& s){ return s.name == faulty_name; });

        if (it != algo.stations.end() && it->faulty) {
            ++successes;
        }
    }

    double avg_ns = static_cast<double>(total_ns) / num_runs;
    std::cout << "Successes: " << successes << " / " << num_runs << "\n";
    std::cout << "Average search time: " << avg_ns << " ns\n";

    // Ensure algorithm succeeded every run
    ASSERT_EQ(successes, num_runs);
}

TEST_F(AlgoTest, Hundred_Runs)
{
    const int num_runs = 100;
    int successes = 0;
    long long total_ns = 0;

    for (int i = 0; i < num_runs; ++i) {
        algo.initialize_stations();      // reset all stations to non-faulty
        algo.random_faulty_station();    // randomly set one station to faulty

        auto start = std::chrono::high_resolution_clock::now();
        std::string faulty_name = algo.find_faulty_station_binary(); // or return index
        auto end = std::chrono::high_resolution_clock::now();

        auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        total_ns += elapsed_ns;

        // Check if the returned station is actually faulty
        auto it = std::find_if(algo.stations.begin(), algo.stations.end(),
                               [&](const Station& s){ return s.name == faulty_name; });

        if (it != algo.stations.end() && it->faulty) {
            ++successes;
        }
    }

    double avg_ns = static_cast<double>(total_ns) / num_runs;
    std::cout << "Successes: " << successes << " / " << num_runs << "\n";
    std::cout << "Average search time: " << avg_ns << " ns\n";

    // Ensure algorithm succeeded every run
    ASSERT_EQ(successes, num_runs);
}

TEST_F(AlgoTest, Multiple_Runs)
{
    const int num_runs = 1000;
    int successes = 0;
    long long total_ns = 0;

    for (int i = 0; i < num_runs; ++i) {
        algo.initialize_stations();      // reset all stations to non-faulty
        algo.random_faulty_station();    // randomly set one station to faulty

        auto start = std::chrono::high_resolution_clock::now();
        std::string faulty_name = algo.find_faulty_station_binary(); // or return index
        auto end = std::chrono::high_resolution_clock::now();

        auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        total_ns += elapsed_ns;

        // Check if the returned station is actually faulty
        auto it = std::find_if(algo.stations.begin(), algo.stations.end(),
                               [&](const Station& s){ return s.name == faulty_name; });

        if (it != algo.stations.end() && it->faulty) {
            ++successes;
        }
    }

    double avg_ns = static_cast<double>(total_ns) / num_runs;
    std::cout << "Successes: " << successes << " / " << num_runs << "\n";
    std::cout << "Average search time: " << avg_ns << " ns\n";

    // Ensure algorithm succeeded every run
    ASSERT_EQ(successes, num_runs);
}

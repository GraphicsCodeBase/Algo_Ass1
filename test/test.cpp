#include <gtest/gtest.h>
#include "../src/algo.hpp"

// class AlgoTest : public ::testing::Test {
// protected:
//     void SetUp() override {
//         algo.initialize_stations();
//     }
    
//     Algo algo;
// };

// // Test station initialization
// TEST_F(AlgoTest, StationInitialization) {
//     // Check that all stations are initialized as not faulty
//     for (const auto& station : algo.stations) {
//         EXPECT_FALSE(station.faulty) << "Station " << station.name << " should not be faulty initially";
//     }
//     EXPECT_GT(algo.stations.size(), 0) << "Should have stations initialized";
// }

// // Test random faulty station selection
// TEST_F(AlgoTest, RandomFaultyStation) {
//     algo.random_faulty_station();
    
//     // Count faulty stations
//     int faulty_count = 0;
//     for (const auto& station : algo.stations) {
//         if (station.faulty) {
//             faulty_count++;
//         }
//     }
    
//     EXPECT_EQ(faulty_count, 1) << "Should have exactly one faulty station";
// }

// // Test linear search algorithm
// TEST_F(AlgoTest, LinearSearchFindsFaultyStation) {
//     // Set a specific station as faulty for testing
//     if (!algo.stations.empty()) {
//         algo.stations[0].faulty = true;
        
//         // Test that linear search finds it
//         // Note: This tests the logic, actual output testing would require capturing cout
//         EXPECT_TRUE(algo.stations[0].faulty) << "First station should be faulty";
//     }
// }

// // Test with no faulty stations
// TEST_F(AlgoTest, NoFaultyStations) {
//     // Ensure no stations are faulty
//     for (auto& station : algo.stations) {
//         station.faulty = false;
//     }
    
//     // Count faulty stations
//     int faulty_count = 0;
//     for (const auto& station : algo.stations) {
//         if (station.faulty) {
//             faulty_count++;
//         }
//     }
    
//     EXPECT_EQ(faulty_count, 0) << "Should have no faulty stations";
// }

// // Test station count
// TEST_F(AlgoTest, StationCount) {
//     // Based on the implementation, we should have 121 stations
//     EXPECT_EQ(algo.stations.size(), 121) << "Should have 121 MRT stations";
// }
#include <gtest/gtest.h>
#include <iostream>
#include <chrono>
#include <map>
#include <iomanip>
#include <string>
#include "../src/algo.hpp"

// Test fixture for the Gale-Shapley Algorithm
class AlgoTest : public ::testing::Test {

protected:
    GaleShapleyAlgorithm algo;

    const int EXPECTED_MATCHES = 5; // 5 Platforms x 5 Restaurants

    void SetUp() override
    {
        // Re-initialize data before each test run
        algo.initializeData();
    }

    // Helper function to execute the G-S algorithm and display all requested output
    int executeAndReport(const std::string& test_name) {

        std::cout << "\n\n<<< " << test_name << " SUMMARY >>>" << std::endl;
        std::cout << std::string(70, '=') << std::endl;

        // 1. Display Preference Lists
        algo.displayPreferences();

        // 2. Execute Algorithm and Time It
        auto start = std::chrono::high_resolution_clock::now();
        algo.runGaleShapleyAlgorithm();
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

        // 3. Report Results
        std::cout << "Algorithm Execution Time: " << duration_ms << " ms" << std::endl;

        std::map<std::string, std::string> final_matches_r = algo.getFinalMatches();
        std::vector<std::string> platforms = algo.getPlatforms();

        std::cout << "\n--- FINAL MATCHES ---" << std::endl;
        int matched_count = 0;

        // Output matches from the perspective of the Proposer (Platform)
        for (const auto& platform : platforms) {
            std::string partner = "";
            for (const auto& pair : final_matches_r) {
                if (pair.second == platform) {
                    partner = pair.first;
                    break;
                }
            }

            if (!partner.empty()) {
                std::cout << "   " << std::left << std::setw(12) << platform
                    << " <--> " << partner << std::endl;
                matched_count++;
            }
            else {
                std::cout << "   " << std::left << std::setw(12) << platform
                    << " <--> (Unmatched)" << std::endl;
            }
        }

        std::cout << "\nAlgorithm Performance:" << std::endl;
        std::cout << "   Total Matches: " << matched_count << "/" << EXPECTED_MATCHES << std::endl;

        // 4. STABILITY CHECK
        bool is_stable = algo.isStable();
        std::cout << "   Stability: " << (is_stable ? "STABLE" : "UNSTABLE") << std::endl;

        std::cout << std::string(70, '=') << std::endl;

        return matched_count;
    }
};

// Scenario 1: BASELINE TEST - Verify stability and max matches with default data (Platform-Optimal)
TEST_F(AlgoTest, Case_01_Baseline_Stability) {
    int matches = executeAndReport("Case_01_Baseline_Stability");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed: Did not achieve maximum possible matches.";
    ASSERT_TRUE(algo.isStable()) << "Test failed: Matching is not stable.";
}

// Scenario 2: High Conflict - Swap the top two preferences for both GrabFood and ChiliCrab
TEST_F(AlgoTest, Case_02_High_Conflict_Swap) {
    // GrabFood prefers PastaExpress over ChiliCrab (original top choice)
    algo.swapPlatformPreferences("GrabFood", "ChiliCrab_Marina", "PastaExpress_Orchard");
    // ChiliCrab prefers Foodpanda over GrabFood (original top choice)
    algo.swapRestaurantPreferences("ChiliCrab_Marina", "GrabFood", "Foodpanda");

    int matches = executeAndReport("Case_02_High_Conflict_Swap");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed after preference swap.";
    ASSERT_TRUE(algo.isStable()) << "Test failed: Matching is not stable after conflict change.";
}

// Scenario 3: All Platforms Agree - Change all platforms' top choice to ChiliCrab
TEST_F(AlgoTest, Case_03_Platforms_Agree_ChiliCrab) {
    for (const auto& p : algo.getPlatforms()) {
        // Set ChiliCrab to rank 1, and the original rank 1 to rank 2
        algo.swapPlatformPreferences(p, "ChiliCrab_Marina", algo.getPlatforms()[0]);
    }
    int matches = executeAndReport("Case_03_Platforms_Agree_ChiliCrab");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed: Consensus matching failure.";
    ASSERT_TRUE(algo.isStable()) << "Test failed: Matching is not stable.";
}

// Scenario 4: Reverse Preferences - Reverse the proposer's (Platforms) entire preference list
TEST_F(AlgoTest, Case_04_Reverse_Proposer_Prefs) {
    // This forces platforms to propose to their worst options first
    algo.swapPlatformPreferences("GrabFood", "ChiliCrab_Marina", "BakKutTeh_Chinatown"); // Swap 1st and 5th
    algo.swapPlatformPreferences("GrabFood", "PastaExpress_Orchard", "ChickenRice_Bugis"); // Swap 2nd and 4th

    int matches = executeAndReport("Case_04_Reverse_Proposer_Prefs");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed: Reverse preference failure.";
    ASSERT_TRUE(algo.isStable()) << "Test failed: Matching is not stable.";
}

// Scenario 5: Receiver-Pessimal Match - The current implementation is Platform-Optimal. 
// A receiver-pessimal match should still be stable.
TEST_F(AlgoTest, Case_05_Proposer_Optimal_Check) {
    int matches = executeAndReport("Case_05_Proposer_Optimal_Check");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed: Proposer optimal check failed.";
    ASSERT_TRUE(algo.isStable()) << "Test failed: Proposer optimal match should be stable.";
}

// Scenario 6: Simple Rotation - Create a simple 3-way cycle in preferences to test the iterative rejection process
TEST_F(AlgoTest, Case_06_Simple_Rotation_Cycle) {
    // Force a cycle that should be resolved by G-S
    algo.swapPlatformPreferences("Deliveroo", "LaksaKing_Katong", "ChiliCrab_Marina"); // Del prefers ChiliCrab
    algo.swapRestaurantPreferences("ChiliCrab_Marina", "GrabFood", "Deliveroo"); // ChiliCrab prefers Deliveroo

    int matches = executeAndReport("Case_06_Simple_Rotation_Cycle");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed: Rotation cycle resolution failure.";
    ASSERT_TRUE(algo.isStable()) << "Test failed: Matching is not stable after cycle.";
}

// Scenario 7: All Restaurants Prefer One Platform - Deliveroo becomes the favorite
TEST_F(AlgoTest, Case_07_Receiver_Consensus_Deliveroo) {
    // Deliveroo's rank is 1 for all restaurants
    for (const auto& r : algo.getRestaurants()) {
        std::string current_best = "";
        // Find current best partner for restaurant r
        for (const auto& p : algo.getPlatforms()) {
            if (algo.getRestaurantRank(r, p) == 1) {
                current_best = p;
                break;
            }
        }
        if (!current_best.empty() && current_best != "Deliveroo") {
            // Swap Deliveroo (rank 3) with current best (rank 1)
            algo.swapRestaurantPreferences(r, "Deliveroo", current_best);
        }
    }
    int matches = executeAndReport("Case_07_Receiver_Consensus_Deliveroo");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed: Receiver consensus failure.";
    ASSERT_TRUE(algo.isStable()) << "Test failed: Matching is not stable.";
}

// Scenario 8: Platform's Worst Match - Ensures a platform gets their lowest preference if rejected by all else
TEST_F(AlgoTest, Case_08_Platform_Worst_Match) {
    // GrabFood's worst is BakKutTeh_Chinatown (rank 5)
    // Make BakKutTeh's worst platform GrabFood (rank 5)
    algo.swapRestaurantPreferences("BakKutTeh_Chinatown", "Deliveroo", "GrabFood");

    int matches = executeAndReport("Case_08_Platform_Worst_Match");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed: Platform's worst match check failure.";
    ASSERT_TRUE(algo.isStable()) << "Test failed: Matching is not stable.";
}

// Scenario 9: Platform First Choice Success - Set GrabFood's and its top choice's preferences high for each other
TEST_F(AlgoTest, Case_09_First_Choice_Success) {
    // GrabFood's top choice: ChiliCrab_Marina
    // Swap GrabFood's next choice to the bottom to ensure quick success
    algo.swapPlatformPreferences("GrabFood", "PastaExpress_Orchard", "BakKutTeh_Chinatown"); // PastaExpress now rank 5 for GF

    int matches = executeAndReport("Case_09_First_Choice_Success");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed: First choice success failure.";
    ASSERT_TRUE(algo.isStable()) << "Test failed: Matching is not stable.";
}

// Scenario 10: Restaurant First Choice Failure - Test the rejection mechanism
TEST_F(AlgoTest, Case_10_Restaurant_Rejection_Test) {
    // PastaExpress's top choice: Deliveroo
    // Make Deliveroo's top choice NOT PastaExpress
    algo.swapPlatformPreferences("Deliveroo", "LaksaKing_Katong", "ChiliCrab_Marina"); // Deliveroo top is ChiliCrab

    int matches = executeAndReport("Case_10_Restaurant_Rejection_Test");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed: Rejection test failure.";
    ASSERT_TRUE(algo.isStable()) << "Test failed: Matching is not stable after rejection setup.";
}
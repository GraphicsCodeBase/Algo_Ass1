#include <gtest/gtest.h>
#include <iostream>
#include <chrono>
#include <map>
#include <iomanip>
#include <string>
#include "../src/algo.hpp"

// Test fixture for the Weighted Preference Bidding Algorithm
class AlgoTest : public ::testing::Test {

protected:
    WeightedPreferenceBiddingAlgorithm algo;

    const size_t EXPECTED_PLATFORMS = 8;
    const size_t EXPECTED_RESTAURANTS = 10;
    const int EXPECTED_MATCHES = 8; // Max possible matches is min(P, R) = 8

    void SetUp() override
    {
        // Re-initialize data before each test run
        algo.initializeData();
    }

    // Helper function to execute the WPBA and display all requested output
    int executeAndReport(const std::string& test_name) {

        // --- EXECUTE ALGORITHM AND TIME IT ---
        auto start = std::chrono::high_resolution_clock::now();
        algo.runWeightedPreferenceBiddingAlgorithm();
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

        // --- REPORT RESULTS ---

        std::cout << "\n\n<<< " << test_name << " SUMMARY >>>" << std::endl;
        std::cout << std::string(70, '=') << std::endl;

        std::cout << "Algorithm Execution Time: " << duration_ms << " ms" << std::endl;

        // Use a temporary map to get the results for printing
        std::map<std::string, std::string> final_matches = algo.getFinalMatches();
        std::map<std::string, double> satisfaction_scores = algo.getSatisfactionScores();
        std::vector<std::string> platforms = algo.getPlatforms();

        std::cout << "\n--- FINAL MATCHES AND SATISFACTION ---" << std::endl;
        double total_satisfaction = 0.0;
        int matched_platforms_count = 0;
        for (const auto& platform : platforms) {
            std::string partner = final_matches[platform];
            double satisfaction = satisfaction_scores[platform];

            if (!partner.empty()) {
                std::cout << "   " << std::left << std::setw(12) << platform
                    << " <--> " << std::left << std::setw(25) << partner
                    << " (Satisfaction: " << std::fixed << std::setprecision(1)
                    << satisfaction << "%)" << std::endl;
                total_satisfaction += satisfaction;
                matched_platforms_count++;
            }
            else {
                std::cout << "   " << std::left << std::setw(12) << platform
                    << " <--> (Unmatched)" << std::endl;
            }
        }

        std::cout << "\nAlgorithm Performance:" << std::endl;
        std::cout << "   Platforms Matched: " << matched_platforms_count << "/" << EXPECTED_PLATFORMS << std::endl;
        if (matched_platforms_count > 0) {
            std::cout << "   Average Satisfaction (Platforms): " << std::fixed << std::setprecision(1)
                << (total_satisfaction / matched_platforms_count) << "%" << std::endl;
        }

        // --- ANALYZE STABILITY ---
        algo.analyzeStability();
        std::cout << std::string(70, '=') << std::endl;

        return matched_platforms_count;
    }

};

// Scenario 1: BASELINE TEST - Verify Max Matches (8) are achieved with default data
TEST_F(AlgoTest, Case_01_Baseline_Max_Matches) {
    int matches = executeAndReport("Case_01_Baseline_Max_Matches");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed: Did not achieve maximum possible matches.";
}

// Scenario 2: BASELINE TEST - Matches Reproducibility (Asserting the output is the same as Case 01)
TEST_F(AlgoTest, Case_02_Baseline_Matches_Reproducibility) {
    int matches = executeAndReport("Case_02_Baseline_Matches_Reproducibility");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed: Matches not reproducible.";
}

// Scenario 3: ECONOMIC SHIFT - WhyQ's budget increases significantly (should allow it to win a better restaurant)
TEST_F(AlgoTest, Case_03_EconomicShift_WhyQ_Budget) {
    // Modify a key input parameter before running: WhyQ's budget (default: 800)
    algo.setPlatformBudget("WhyQ", 2000.0);
    int matches = executeAndReport("Case_03_EconomicShift_WhyQ_Budget");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed after budget modification.";
}

// Scenario 4: ECONOMIC SHIFT - GrabFood's budget is severely cut (should force it to match with a lower preference)
TEST_F(AlgoTest, Case_04_EconomicShift_GrabFood_Budget) {
    // Modify a key input parameter before running: GrabFood's budget (default: 1500)
    algo.setPlatformBudget("GrabFood", 500.0);
    int matches = executeAndReport("Case_04_EconomicShift_GrabFood_Budget");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed after budget modification.";
}

// Scenario 5: CAPACITY SHIFT - Halve the capacity of the highest-capacity restaurant (ChiliCrab)
TEST_F(AlgoTest, Case_05_CapacityShift_ChiliCrab_Halved) {
    // Modify capacity: ChiliCrab (default: 100)
    algo.setRestaurantCapacity("ChiliCrab_Marina", 50);
    int matches = executeAndReport("Case_05_CapacityShift_ChiliCrab_Halved");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed after capacity modification.";
}

// Scenario 6: CAPACITY SHIFT - Double the capacity of the lowest-capacity restaurant (ZiChar)
TEST_F(AlgoTest, Case_06_CapacityShift_ZiChar_Doubled) {
    // Modify capacity: ZiChar (default: 55)
    algo.setRestaurantCapacity("ZiChar_Toa", 110);
    int matches = executeAndReport("Case_06_CapacityShift_ZiChar_Doubled");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed after capacity modification.";
}

// Scenario 7: PLATFORM PREFERENCE SHIFT - Foodpanda shifts focus to SatayGrill (changing P-weight)
TEST_F(AlgoTest, Case_07_PreferenceShift_Foodpanda_SatayGrill) {
    // Change Foodpanda's preference for SatayGrill to be the best (10)
    algo.setPlatformWeight("Foodpanda", "SatayGrill_Clarke", 10);
    // Set their former top choice (PastaExpress) lower (1)
    algo.setPlatformWeight("Foodpanda", "PastaExpress_Orchard", 1);
    int matches = executeAndReport("Case_07_PreferenceShift_Foodpanda_SatayGrill");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed after preference shift.";
}

// Scenario 8: RESTAURANT PREFERENCE SHIFT - LaksaKing strongly prefers Oddle (changing R-weight)
TEST_F(AlgoTest, Case_08_PreferenceShift_LaksaKing_Oddle) {
    // Change LaksaKing's preference for Oddle to be the best (8)
    algo.setRestaurantWeight("LaksaKing_Katong", "Oddle", 8);
    // Set their former top choice (GrabFood) lower (1)
    algo.setRestaurantWeight("LaksaKing_Katong", "GrabFood", 1);
    int matches = executeAndReport("Case_08_PreferenceShift_LaksaKing_Oddle");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed after preference shift.";
}

// Scenario 9: BUDGET CRISIS - All platform budgets are cut in half
TEST_F(AlgoTest, Case_09_EconomicCrisis_Halved_Budgets) {
    std::map<std::string, double> current_budgets = algo.getPlatformBudgets();
    for (auto const& [platform, budget] : current_budgets) {
        algo.setPlatformBudget(platform, budget / 2.0);
    }
    int matches = executeAndReport("Case_09_EconomicCrisis_Halved_Budgets");
    // Assert that the max possible matches are still achieved even with less money
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed: Crisis caused unmatched platforms.";
}

// Scenario 10: SATURATION - All restaurant capacities are reduced to the minimum (50)
TEST_F(AlgoTest, Case_10_Saturation_Low_Capacities) {
    std::vector<std::string> restaurants = algo.getRestaurants();
    for (const auto& restaurant : restaurants) {
        // Reducing capacity increases the Score factor, making matches easier to achieve
        algo.setRestaurantCapacity(restaurant, 50);
    }
    int matches = executeAndReport("Case_10_Saturation_Low_Capacities");
    ASSERT_EQ(matches, EXPECTED_MATCHES) << "Test failed after capacity saturation.";
}
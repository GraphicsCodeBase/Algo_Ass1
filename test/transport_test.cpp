/**
 * @file transport_test.cpp
 * @brief Unit tests for Singapore Transport Network Optimization algorithm
 * @author Ho Jing Rui
 * @date 28/9/2025
 *
 * @section description Description
 * This file contains comprehensive unit tests for the SingaporeTransportOptimizer class
 * which implements a divide-and-conquer algorithm with time complexity T(n) = 4T(n/2) + n.
 * The tests validate algorithm correctness, recurrence relation behavior, and
 * Singapore-specific regional division functionality.
 *
 * @section test_cases Test Cases
 * - Base case functionality with 1x1 networks
 * - Small network optimization with 2x2 matrices
 * - Empirical validation of O(n²) complexity growth
 * - Network generation with proper constraints
 * - Geographical region division for Singapore transport planning
 *
 * @section dependencies Dependencies
 * - Google Test Framework (gtest)
 * - transport.hpp (main algorithm header)
 * - C++ Standard Library (vector, chrono, iostream)
 *
 * @section notes Notes
 * - Tests use empirical timing to validate theoretical complexity
 * - Region division tests model Singapore's geographical quadrants
 * - All tests are designed to be deterministic and repeatable
 */

#include <gtest/gtest.h>
#include "../src/transport.hpp"
#include <vector>
#include <chrono>

/**
 * @brief Test fixture for Singapore Transport Optimizer tests
 *
 * Base fixture for transport optimization tests. Currently minimal
 * but provides structure for future common setup requirements.
 */
class SingaporeTransportTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Reserved for future common test setup
    }

    void TearDown() override {
        // Reserved for future cleanup operations
    }
};

/**
 * @brief Tests the base case of the transport optimization algorithm
 *
 * Verifies that a 1x1 network returns the correct single value.
 * This tests the termination condition of the recursive algorithm.
 */
TEST_F(SingaporeTransportTest, BaseCaseTest) {
    SingaporeTransportOptimizer optimizer(1);
    std::vector<std::vector<int>> network = { {5} };
    int result = optimizer.optimizeTransport(network);
    EXPECT_EQ(result, 5);  // Expected: Return base case single value
}

/**
 * @brief Tests optimization of a small 2x2 transport network
 *
 * Validates that the algorithm produces a result greater than the simple sum
 * of individual values, confirming that additional processing occurs.
 */
TEST_F(SingaporeTransportTest, SmallNetworkTest) {
    SingaporeTransportOptimizer optimizer(2);
    std::vector<std::vector<int>> network = { {1, 2}, {3, 4} };
    int result = optimizer.optimizeTransport(network);
    EXPECT_GT(result, 10);  // Expected: base(1)+base(2)+base(3)+base(4) + linear work
}

/**
 * @brief Tests the recurrence relation T(n) = 4T(n/2) + n empirically
 *
 * Measures execution times for networks of sizes 2, 4, 8, and 16.
 * Verifies that time complexity follows O(n²) by checking that
 * execution time roughly quadruples when problem size doubles.
 */
TEST_F(SingaporeTransportTest, RecurrenceRelationTest) {
    std::vector<int> sizes = { 2, 4, 8, 16 };
    std::vector<long long> durations;

    for (int size : sizes) {
        SingaporeTransportOptimizer optimizer(size);
        auto network = SingaporeTransportOptimizer::generateNetwork(size);
        auto start = std::chrono::high_resolution_clock::now();

        const int iterations = 10;
        int result = 0;
        for (int i = 0; i < iterations; ++i) {
            result = optimizer.optimizeTransport(network);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        long long avg_duration = std::max(1LL, duration.count() / iterations);
        durations.push_back(avg_duration);
        std::cout << "Size: " << size << ", Time: " << avg_duration << " microseconds, Result: " << result << std::endl;
    }

    // Verify that time grows quadratically
    for (size_t i = 1; i < durations.size(); ++i) {
        if (durations[i - 1] == 0) {
            GTEST_SKIP() << "Time measurement too small for reliable ratio calculation";
        }

        double ratio = static_cast<double>(durations[i]) / durations[i - 1];
        std::cout << "Ratio " << sizes[i] << "/" << sizes[i - 1] << ": " << ratio << std::endl;

        EXPECT_GE(ratio, 2.0);
        EXPECT_LE(ratio, 10.0);
        EXPECT_FALSE(std::isinf(ratio));
        EXPECT_FALSE(std::isnan(ratio));
    }
}

/**
 * @brief Tests the network generation functionality
 *
 * Verifies that generated networks have correct dimensions and that
 * all values fall within the expected range of 1 to 100.
 */
TEST_F(SingaporeTransportTest, NetworkGenerationTest) {
    int size = 4;
    auto network = SingaporeTransportOptimizer::generateNetwork(size);

    EXPECT_EQ(network.size(), size);
    for (const auto& row : network) {
        EXPECT_EQ(row.size(), size);
        for (int val : row) {
            EXPECT_GE(val, 1);
            EXPECT_LE(val, 100);
        }
    }
}

/**
 * @brief Tests the region division functionality
 *
 * Verifies that a 4x4 network is correctly divided into four 2x2 regions
 * representing North-East, North-West, South-East, and South-West quadrants
 * with correct values in each position.
 */
TEST_F(SingaporeTransportTest, RegionDivisionTest) {
    SingaporeTransportOptimizer optimizer(4);
    std::vector<std::vector<int>> network = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    std::vector<std::vector<int>> ne, nw, se, sw;
    optimizer.testDivideIntoRegions(network, ne, nw, se, sw);

    // North-East region (top-left 2x2)
    EXPECT_EQ(ne[0][0], 1);  // row0,col0
    EXPECT_EQ(ne[0][1], 2);  // row0,col1
    EXPECT_EQ(ne[1][0], 5);  // row1,col0
    EXPECT_EQ(ne[1][1], 6);  // row1,col1

    // North-West region (top-right 2x2)
    EXPECT_EQ(nw[0][0], 3);  // row0,col2
    EXPECT_EQ(nw[0][1], 4);  // row0,col3
    EXPECT_EQ(nw[1][0], 7);  // row1,col2
    EXPECT_EQ(nw[1][1], 8);  // row1,col3

    // South-East region (bottom-left 2x2)
    EXPECT_EQ(se[0][0], 9);   // row2,col0
    EXPECT_EQ(se[0][1], 10);  // row2,col1
    EXPECT_EQ(se[1][0], 13);  // row3,col0
    EXPECT_EQ(se[1][1], 14);  // row3,col1

    // South-West region (bottom-right 2x2)
    EXPECT_EQ(sw[0][0], 11);  // row2,col2
    EXPECT_EQ(sw[0][1], 12);  // row2,col3
    EXPECT_EQ(sw[1][0], 15);  // row3,col2
    EXPECT_EQ(sw[1][1], 16);  // row3,col3
}

/**
 * @brief Main function to run all Google Tests
 *
 * Initializes the Google Test framework and runs all test cases.
 * Returns 0 if all tests pass, 1 otherwise.
 */
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
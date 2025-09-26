#include <gtest/gtest.h>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include <set>
#include "../src/bucket_sort.hpp"

class BucketSortTest : public ::testing::Test {
protected:
    BucketSort sorter;

    void SetUp() override {
        sorter.clearNumbers();
    }

    void TearDown() override {
        sorter.clearNumbers();
    }


    bool isSorted() {
        const auto& nums = sorter.getNumbers();
        for (size_t i = 1; i < nums.size(); i++) {
            if (nums[i - 1] > nums[i]) {
                return false;
            }
        }
        return true;
    }


    bool hasAllOriginalData(const std::vector<int>& original) {
        const auto& nums = sorter.getNumbers();
        if (nums.size() != original.size()) return false;

        std::set<int> origSet(original.begin(), original.end());
        std::set<int> sortedSet(nums.begin(), nums.end());
        return origSet == sortedSet;
    }
};

TEST_F(BucketSortTest, EmptyArray) {
    sorter.clearNumbers();
    EXPECT_NO_THROW(sorter.bucketSort());
    EXPECT_EQ(sorter.getNumberCount(), 0);
}

TEST_F(BucketSortTest, SingleElement) {
    sorter.addNumber(42);
    sorter.bucketSort();
    EXPECT_EQ(sorter.getNumberCount(), 1);
    EXPECT_EQ(sorter.getNumbers()[0], 42);
}

TEST_F(BucketSortTest, SmallDataset) {
    std::vector<int> original = { 5, 3, 8, 1, 7 };
    for (int n : original) sorter.addNumber(n);

    sorter.bucketSort();
    EXPECT_TRUE(isSorted());
    EXPECT_TRUE(hasAllOriginalData(original));
}

TEST_F(BucketSortTest, LoadFromFileAndSort) {
    sorter.loadFromFile("../../../src/thousand.txt");

    ASSERT_EQ(sorter.getNumberCount(), 1000) << "File should contain 1000 numbers";

    sorter.bucketSort();
    EXPECT_TRUE(isSorted());

    // Verify it sorted into 1..1000
    const auto& nums = sorter.getNumbers();
    for (int i = 1; i <= 1000; i++) {
        EXPECT_EQ(nums[i - 1], i);
    }
}

TEST_F(BucketSortTest, StressTestMultipleRuns) {
    sorter.loadFromFile("../../../src/thousand.txt");
    ASSERT_EQ(sorter.getNumberCount(), 1000);

    std::vector<int> original = sorter.getNumbers();
    int runs = 20;
    int successes = 0;

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < runs; i++) {
        std::shuffle(original.begin(), original.end(), gen);
        sorter.clearNumbers();
        for (int n : original) sorter.addNumber(n);

        sorter.bucketSort();

        if (isSorted() && hasAllOriginalData(original)) {
            successes++;
        }
    }

    EXPECT_EQ(successes, runs) << "Some stress test runs failed";
}

//test same elements
TEST_F(BucketSortTest, DuplicateElements) {
    std::vector<int> data = { 5, 3, 5, 1, 3, 1, 5 };
    for (int n : data) sorter.addNumber(n);

    sorter.bucketSort();
    EXPECT_TRUE(isSorted());
    EXPECT_TRUE(hasAllOriginalData(data));
}

TEST_F(BucketSortTest, AlreadySorted) {
    for (int i = 1; i <= 100; i++) sorter.addNumber(i);

    sorter.bucketSort();
    EXPECT_TRUE(isSorted());
}

TEST_F(BucketSortTest, ReverseSorted) {
    for (int i = 100; i >= 1; i--) sorter.addNumber(i);

    sorter.bucketSort();
    EXPECT_TRUE(isSorted());
}

TEST_F(BucketSortTest, PerformanceComparison) {
    sorter.loadFromFile("../../../src/thousand.txt");
    ASSERT_EQ(sorter.getNumberCount(), 1000);

    std::vector<int> original = sorter.getNumbers();
    const int num_runs = 20;
    std::random_device rd;
    std::mt19937 gen(rd());

    // Bucket sort benchmark
    long long bucket_total_ns = 0;
    for (int i = 0; i < num_runs; i++) {
        std::shuffle(original.begin(), original.end(), gen);
        sorter.clearNumbers();
        for (int n : original) sorter.addNumber(n);

        auto start = std::chrono::high_resolution_clock::now();
        sorter.bucketSort();
        auto end = std::chrono::high_resolution_clock::now();

        bucket_total_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        ASSERT_TRUE(isSorted());
    }


    long long std_total_ns = 0;
    for (int i = 0; i < num_runs; i++) {
        std::vector<int> temp = original;
        std::shuffle(temp.begin(), temp.end(), gen);

        auto start = std::chrono::high_resolution_clock::now();
        std::sort(temp.begin(), temp.end());
        auto end = std::chrono::high_resolution_clock::now();

        std_total_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }



    double bucket_avg = static_cast<double>(bucket_total_ns) / num_runs;
    double std_avg = static_cast<double>(std_total_ns) / num_runs;

    std::cout << "\n=== PERFORMANCE COMPARISON ===" << std::endl;
    std::cout << "Bucket sort avg: " << bucket_avg / 1000.0 << " microseconds" << std::endl;
    std::cout << "Std sort avg: " << std_avg / 1000.0 << " microseconds" << std::endl;
}

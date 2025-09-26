#include "bucket_sort.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <random>

void BucketSort::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    int value;

    numbers.clear();

    while (file >> value) {
        numbers.push_back(value);
    }
}

void BucketSort::insertionSort(std::vector<int>& bucket) {
    for (size_t i = 1; i < bucket.size(); i++) {
        int key = bucket[i];
        int j = static_cast<int>(i) - 1;

        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

void BucketSort::bucketSort() {
    if (numbers.empty()) return;

    int minVal = *std::min_element(numbers.begin(), numbers.end());
    int maxVal = *std::max_element(numbers.begin(), numbers.end());

    if (minVal == maxVal) return;

    int bucketCount = std::max(1, static_cast<int>(std::sqrt(numbers.size())));
    std::vector<std::vector<int>> buckets(bucketCount);

    for (int num : numbers) {
       
        double normalized = static_cast<double>(num - minVal) / (maxVal - minVal);
        int idx = std::min(bucketCount - 1, static_cast<int>(normalized * bucketCount));
        buckets[idx].push_back(num);
    }

    numbers.clear();
    for (auto& bucket : buckets) {
        if (!bucket.empty()) {
            insertionSort(bucket);
            for (int num : bucket) {
                numbers.push_back(num);
            }
        }
    }
}

void BucketSort::printNumbers() const {
    for (int num : numbers) {
        std::cout << num << std::endl;
    }
}

void BucketSort::benchmark(int iterations) {
    if (numbers.empty()) return;

    std::vector<int> original = numbers;
    long long totalTime = 0;
    std::random_device rd;
    std::mt19937 gen(rd());

    std::cout << "\nBenchmarking Bucket Sort:" << std::endl;
    std::cout << "Dataset size: " << original.size() << std::endl;
    std::cout << "Iterations: " << iterations << std::endl;

    for (int i = 0; i < iterations; i++) {
        numbers = original;
        std::shuffle(numbers.begin(), numbers.end(), gen);

        auto start = std::chrono::high_resolution_clock::now();
        bucketSort();
        auto end = std::chrono::high_resolution_clock::now();

        totalTime += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();


        for (size_t j = 1; j < numbers.size(); j++) {
            if (numbers[j - 1] > numbers[j]) {
                std::cerr << "ERROR: Sorting failed at iteration " << i << std::endl;
                return;
            }
        }
    }

    double avgTimeNs = static_cast<double>(totalTime) / iterations;
    double avgTimeMicros = avgTimeNs / 1000.0;
    double avgTimeMs = avgTimeMicros / 1000.0;

    std::cout << "Average time: " << avgTimeMicros << " microseconds ("
        << avgTimeMs << " ms)" << std::endl;
}

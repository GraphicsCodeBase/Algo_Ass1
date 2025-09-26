#ifndef BUCKET_SORT_HPP
#define BUCKET_SORT_HPP

#include <vector>
#include <string>

class BucketSort {
public:
    void loadFromFile(const std::string& filename);
    void bucketSort();
    void printNumbers() const;
    void benchmark(int iterations = 1000);


    std::vector<int>& getNumbers() { return numbers; }
    const std::vector<int>& getNumbers() const { return numbers; }
    void clearNumbers() { numbers.clear(); }
    void addNumber(int num) { numbers.push_back(num); }
    size_t getNumberCount() const { return numbers.size(); }

private:
    std::vector<int> numbers;
    void insertionSort(std::vector<int>& bucket);
};

#endif

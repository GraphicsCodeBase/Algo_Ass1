#include "algo.hpp"

void Algo::loadStations(std::string file_path)
{
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return;
    }

    stations.clear();
    std::string line;

    while (std::getline(file, line)) {
        Station s;
        s.name = line;
        s.faulty = false;

        // Parse ID from the line
        size_t underscorePos = line.find('_');
        if (underscorePos != std::string::npos) {
            s.id = std::stoi(line.substr(underscorePos + 1));
        } else {
            s.id = 1; // fallback
        }

        stations.push_back(s);
    }

    file.close();
}


int Algo::setRandomFaultyStation()
{
 if (stations.size() < 2) return -1; // Need at least 2 stations

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, stations.size() - 2); // avoid last

    int index = dist(gen);

    int baseID = stations[index].id;
    int nextID = stations[index + 1].id;

    int targetID;

    if (nextID - baseID > 1) {
        // There is a gap; pick a random number in-between
        std::uniform_int_distribution<> offsetDist(1, nextID - baseID - 1);
        int offset = offsetDist(gen);
        targetID = baseID + offset;
    } else {
        // No gap; fallback to picking a station ID (will be found in 1 probe)
        targetID = baseID;
    }

    std::cout << "Generated hard target ID: " << targetID 
              << " (between " << baseID << " and " << nextID << ")\n";

    return targetID;
}

int Algo::interpolationSearch(int64_t targetID, int& probes)
{
    int low = 0;
    int high = stations.size() - 1;
    probes = 0;

    while (low <= high && targetID >= stations[low].id && targetID <= stations[high].id) {
        ++probes;

        if (low == high) {
            if (stations[low].id == targetID) return low;
            return -1;
        }

        int pos = low + (int)((double)(targetID - stations[low].id) * (high - low) /
                              (stations[high].id - stations[low].id));

        if (stations[pos].id == targetID)
            return pos;
        else if (stations[pos].id < targetID)
            low = pos + 1;
        else
            high = pos - 1;
    }

    return -1;
}

void Algo::benchmarkInterpolationSearch(int targetID)
{
    int probes = 0;

    auto start = std::chrono::high_resolution_clock::now();
    int pos = interpolationSearch(targetID, probes);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::micro> duration = end - start;

    std::cout << "----- Interpolation Search Benchmark -----" << std::endl;
    std::cout << "Array size: " << stations.size() << std::endl;
    std::cout << "Target station ID: " << targetID << std::endl;

    if (pos != -1)
        std::cout << "Found at index: " << pos << std::endl;
    else
        std::cout << "Station not found." << std::endl;

    std::cout << "Probes/iterations: " << probes << std::endl;
    std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
}

void Algo::generateSequentialStations(const std::string& filepath, int limit) {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filepath << std::endl;
        return;
    }

    for (int id = 1; id <= limit; ++id) {
        file << "Station_" << id << std::endl; // write station name
    }

    file.close();
    std::cout << "Generated stations from 1 to " << limit << " in " << filepath << std::endl;
}


void Algo::generateHighlyNonUniformStations(const std::string &filepath, int numStations)
{
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return;
    }

    std::random_device rd;
    std::mt19937_64 gen(rd()); // 64-bit RNG
    std::uniform_int_distribution<int64_t> tinyGap(1, 5);
    std::uniform_int_distribution<int64_t> mediumGap(50, 200);
    std::uniform_int_distribution<int64_t> hugeGap(5000, 20000);

    int64_t currentID = 1;

    for (int i = 0; i < numStations; ++i) {
        file << "Station_" << currentID << std::endl;

        // Use highly irregular gaps
        if (i % 10 == 0)
            currentID += hugeGap(gen);
        else if (i % 3 == 0)
            currentID += mediumGap(gen);
        else
            currentID += tinyGap(gen);
    }

    file.close();
    std::cout << "Generated " << numStations << " highly non-uniform stations in "
              << filepath << std::endl;
}

int64_t Algo::generateHardTarget()
{
    if (stations.size() < 2) return -1;

    std::random_device rd;
    std::mt19937_64 gen(rd());

    // Find a random gap big enough
    std::vector<int> candidateIndices;
    const int64_t minGap = 50; // minimum gap to generate a “hard target”

    for (size_t i = 0; i < stations.size() - 1; ++i) {
        if (stations[i + 1].id - stations[i].id > minGap)
            candidateIndices.push_back(i);
    }

    if (candidateIndices.empty()) return stations[stations.size()/2].id;

    std::uniform_int_distribution<> dist(0, candidateIndices.size() - 1);
    int idx = candidateIndices[dist(gen)];

    int64_t baseID = stations[idx].id;
    int64_t nextID = stations[idx + 1].id;

    std::uniform_int_distribution<int64_t> offsetDist(1, nextID - baseID - 1);
    int64_t targetID = baseID + offsetDist(gen);

    std::cout << "Generated hard target ID: " << targetID
              << " (between " << baseID << " and " << nextID << ")\n";

    return targetID;
}

int64_t Algo::generateHardExistingTarget()
{
    if (stations.empty()) return -1;

    std::random_device rd;
    std::mt19937_64 gen(rd());

    // Pick one of the first or last 5% of stations
    size_t range = stations.size() / 20; // 5%
    std::uniform_int_distribution<size_t> dist(0, range - 1);

    bool pickStart = (gen() % 2 == 0);
    size_t idx = pickStart ? dist(gen) : stations.size() - 1 - dist(gen);

    int64_t targetID = stations[idx].id;

    std::cout << "Generated hard-but-existing target: " << targetID
              << " at index " << idx << "\n";

    return targetID;
}

int64_t Algo::pickTargetFromStations()
{
    if (stations.empty()) return -1;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, stations.size() - 1);

    size_t idx = dist(gen);
    return stations[idx].id; // Guaranteed to exist
}

void Algo::clearStations()
{
    stations.clear();
}

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

struct Metrics {
    long long comparisons = 0;
    long long swaps = 0;
    double duration_ms = 0.0;
};

bool isSorted(const std::vector<int>& arr);

std::vector<int> generateRandomData(int size);
std::vector<int> generateSortedData(int size);
std::vector<int> generateReverseSortedData(int size);
std::vector<int> generatePartiallySortedData(int size);

#endif // UTILS_H
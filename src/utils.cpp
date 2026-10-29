#include "utils.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Dizinin sıralı olup olmamasını kontrol eder
bool isSorted(const std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

// Rastgele veri üretir
std::vector<int> generateRandomData(int size) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(NULL));
        seeded = true;
    }

    std::vector<int> data(size);
    for (int i = 0; i < size; i++) {
        data[i] = rand() % (size * 10) + 1;
    }
    return data;
}

// Sıralı veri üretir
std::vector<int> generateSortedData(int size) {
    std::vector<int> data = generateRandomData(size);

    std::sort(data.begin(), data.end());
    return data;
}

// Ters sıralı veri üretir
std::vector<int> generateReverseSortedData(int size) {
    std::vector<int> data = generateSortedData(size);

    std::reverse(data.begin(), data.end());
    return data;
}

// Kısmen sıralı veri üretir
std::vector<int> generatePartiallySortedData(int size) {
    std::vector<int> data = generateSortedData(size);

    int swap_count = size / 10;

    for (int i = 0; i < swap_count; i++) {
        int index1 = rand() % size;
        int index2 = rand() % size;

        std::swap(data[index1], data[index2]);
    }
    return data;
}
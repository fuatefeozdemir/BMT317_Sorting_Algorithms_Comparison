#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include "utils.h"

void selectionSort(std::vector<int>& arr, Metrics& metrics);
void insertionSort(std::vector<int>& arr, Metrics& metrics);
void bubbleSort(std::vector<int>& arr, Metrics& metrics);
void shellSort(std::vector<int>& arr, Metrics& metrics); 
void quickSort(std::vector<int>& arr, int low, int high, Metrics& metrics);
void mergeSort(std::vector<int>& arr, int left, int right, Metrics& metrics);
void heapSort(std::vector<int>& arr, Metrics& metrics);
void quickSortFirstPivot(std::vector<int>& arr, int lo, int hi, Metrics& m);
void shellSortKnuth(std::vector<int>& arr, Metrics& m);

inline void trackedSwap(int& a, int& b, Metrics& metrics) {
    int temp = a;
    a = b;
    b = temp;
    metrics.swaps++;
}

#endif // ALGORITHMS_H
#include <vector>
#include <algorithm>

struct Metrics { long long comparisons = 0, swaps = 0; double duration_ms = 0.0; };

// 1. Selection Sort
void selectionSort(std::vector<int>& arr, Metrics& m) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            m.comparisons++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(arr[i], arr[min_idx]);
            m.swaps++;
        }
    }
}

// 2. Insertion Sort
void insertionSort(std::vector<int>& arr, Metrics& m) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            m.comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                m.swaps++;
                j--;
            }
            else {
                break;
            }
        }
        arr[j + 1] = key;
        m.swaps++; 
    }
}

// 3. Bubble Sort
void bubbleSort(std::vector<int>& arr, Metrics& m) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            m.comparisons++;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                m.swaps++;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

// 4. Shell Sort
void shellSort(std::vector<int>& arr, Metrics& m) {
    int n = arr.size();
    for (int h = n / 2; h > 0; h /= 2) { 
        for (int i = h; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= h; j -= h) {
                m.comparisons++;
                if (arr[j - h] > temp) {
                    arr[j] = arr[j - h];
                    m.swaps++;
                } else break;
            }
            arr[j] = temp;
            m.swaps++;
        }
    }
}

// 5. Quick Sort
void quickSort(std::vector<int>& arr, int lo, int hi, Metrics& m) {
    if (lo >= hi) {
        return;
    }

    int pivot = arr[lo + (hi - lo) / 2]; 
    int i = lo, j = hi;
    
    while (i <= j) {
        while (arr[i] < pivot) {
            m.comparisons++; i++;
        }
        m.comparisons++; // Döngüden çıkaran başarısız karşılaştırma için
        
        while (arr[j] > pivot) {
            m.comparisons++; j--;
        }
        m.comparisons++; 

        if (i <= j) {
            std::swap(arr[i], arr[j]);
            m.swaps++;
            i++; j--;
        }
    }
    quickSort(arr, lo, j, m);
    quickSort(arr, i, hi, m);
}

// 6. Merge Sort 
void mergeSort(std::vector<int>& arr, int lo, int hi, Metrics& m) {
    if (lo >= hi) {
        return;
    }
    int mid = lo + (hi - lo) / 2;
    mergeSort(arr, lo, mid, m);
    mergeSort(arr, mid + 1, hi, m);
    
    std::vector<int> temp;
    int i = lo, j = mid + 1;
    
    while (i <= mid && j <= hi) {
        m.comparisons++;
        if (arr[i] <= arr[j]) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
        m.swaps++;
    }
    while (i <= mid) {
        temp.push_back(arr[i++]); m.swaps++;
    }
    while (j <= hi) {
        temp.push_back(arr[j++]); m.swaps++;
    }
    
    for (size_t k = 0; k < temp.size(); k++) {
        arr[lo + k] = temp[k];
        m.swaps++;
    }
}

// 7. Heap Sort
void heapify(std::vector<int>& arr, int n, int i, Metrics& m) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        m.comparisons++;
        if (arr[left] > arr[largest]) largest = left;
    }
    if (right < n) {
        m.comparisons++;
        if (arr[right] > arr[largest]) largest = right;
    }
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        m.swaps++;
        heapify(arr, n, largest, m);
    }
}

void heapSort(std::vector<int>& arr, Metrics& m) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, m);
    }
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        m.swaps++;
        heapify(arr, i, 0, m);
    }
}

// Bonus 1: Quick Sort (Pivot: Ilk Eleman)
void quickSortFirstPivot(std::vector<int>& arr, int lo, int hi, Metrics& m) {
    if (lo >= hi) return;

    int pivot = arr[lo];
    int i = lo, j = hi + 1;

    while (true) {
        while (arr[++i] < pivot) {
            m.comparisons++;
            if (i == hi) break;
        }
        m.comparisons++;

        while (arr[--j] > pivot) {
            m.comparisons++;
            if (j == lo) break;
        }
        m.comparisons++;

        if (i >= j) break;
        std::swap(arr[i], arr[j]);
        m.swaps++;
    }
    std::swap(arr[lo], arr[j]);
    m.swaps++;

    quickSortFirstPivot(arr, lo, j - 1, m);
    quickSortFirstPivot(arr, j + 1, hi, m);
}

// Bonus 2: Shell Sort
void shellSortKnuth(std::vector<int>& arr, Metrics& m) {
    int n = arr.size();
    int h = 1;
    while (h < n / 3) h = 3 * h + 1;

    while (h >= 1) {
        for (int i = h; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= h; j -= h) {
                m.comparisons++;
                if (arr[j - h] > temp) {
                    arr[j] = arr[j - h];
                    m.swaps++;
                } else break;
            }
            arr[j] = temp;
            m.swaps++;
        }
        h = h / 3;
    }
}

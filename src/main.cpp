#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "utils.h"
#include "algorithms.h"

// Hangi algoritmanın çalıştırılacağı seçiliyor
void runAlgorithm(std::string algoName, void (*sortFunc)(std::vector<int>&, Metrics&),
             std::vector<int> originalData, std::string dataType, int n, std::ofstream& csvFile) {

    // Çok büyük verilerde uzun sürecek algoritmalar atlanır ve rapora yazılır
    if (n > 10000 && (algoName == "Selection" || algoName == "Insertion" || algoName == "Bubble" || algoName == "Quick_FirstPivot")) {
        std::cout << "  -> HATA/BILGI: " << algoName << " " << n << " boyutunda atlandi (Zaman/Bellek Siniri).\n";
        csvFile << algoName << "," << dataType << "," << n << ",Limit Asimi,-,-\n";
        return; // Sıralama yapmadan fonksiyondan çık
    }

    Metrics totalMetrics;
    totalMetrics.comparisons = 0;
    totalMetrics.swaps = 0;
    totalMetrics.duration_ms = 0.0;

    // Her deneyin 5 kez tekrarlanması için döngü
    for (int t = 0; t < 5; t++) {
        std::vector<int> testData = originalData; // Her seferinde dizinin kopyası alınır
        Metrics currentMetrics;
        currentMetrics.comparisons = 0;
        currentMetrics.swaps = 0;

        // Zaman ölçümü başlangıcı
        auto start = std::chrono::high_resolution_clock::now();

        sortFunc(testData, currentMetrics); // Seçilen algoritma seçilen verilerle çalıştırılır

        // Zaman ölçümü bitişi
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> sure = end - start; // Hatalı satır düzeltildi
        currentMetrics.duration_ms = sure.count();

        // Sıralı değilse uyarı
        if (!isSorted(testData)) {
            std::cout << "HATA: " << algoName << " siralamayi basaramadi!\n";
        }

        totalMetrics.comparisons += currentMetrics.comparisons;
        totalMetrics.swaps += currentMetrics.swaps;
        totalMetrics.duration_ms += currentMetrics.duration_ms;
    }

    // 5 deneyin ortalaması alınır
    totalMetrics.comparisons /= 5;
    totalMetrics.swaps /= 5;
    totalMetrics.duration_ms /= 5.0;

    // Her deney en son dosyaya yazdırılır
    csvFile << algoName << "," << dataType << "," << n << ","
            << totalMetrics.duration_ms << "," << totalMetrics.comparisons << ","
            << totalMetrics.swaps << "\n";
}

// Quick ve Merge Sort parametrelerine uygun fonksiyonlar
void callQuickSort(std::vector<int>& arr, Metrics& m) {
    quickSort(arr, 0, arr.size() - 1, m);
}

void callQuickSortFirstPivot(std::vector<int>& arr, Metrics& m) {
    quickSortFirstPivot(arr, 0, arr.size() - 1, m);
}

void callMergeSort(std::vector<int>& arr, Metrics& m) {
    mergeSort(arr, 0, arr.size() - 1, m);
}

int main() {
    int sizes[] = {100, 1000, 5000, 10000, 50000, 100000};
    int numSizes = 6;

    std::ofstream csvFile("deney_sonuclari.csv");
    csvFile << "Algoritma,Veri_Tipi,Boyut(n),Ortalama_Sure(ms),Karsilastirma,Swap_Hareket\n";

    for (int i = 0; i < numSizes; i++) {
        int n = sizes[i];
        std::cout << "Boyut isleniyor: " << n << "\n";

        std::vector<int> randomData = generateRandomData(n);
        std::vector<int> sortedData = generateSortedData(n);
        std::vector<int> reverseData = generateReverseSortedData(n);
        std::vector<int> partialData = generatePartiallySortedData(n);

        runAlgorithm("Selection", selectionSort, randomData, "Rastgele", n, csvFile);
        runAlgorithm("Selection", selectionSort, sortedData, "Sirali", n, csvFile);
        runAlgorithm("Selection", selectionSort, reverseData, "Ters Sirali", n, csvFile);
        runAlgorithm("Selection", selectionSort, partialData, "Kismen Sirali", n, csvFile);

        runAlgorithm("Insertion", insertionSort, randomData, "Rastgele", n, csvFile);
        runAlgorithm("Insertion", insertionSort, sortedData, "Sirali", n, csvFile);
        runAlgorithm("Insertion", insertionSort, reverseData, "Ters Sirali", n, csvFile);
        runAlgorithm("Insertion", insertionSort, partialData, "Kismen Sirali", n, csvFile);

        runAlgorithm("Bubble", bubbleSort, randomData, "Rastgele", n, csvFile);
        runAlgorithm("Bubble", bubbleSort, sortedData, "Sirali", n, csvFile);
        runAlgorithm("Bubble", bubbleSort, reverseData, "Ters Sirali", n, csvFile);
        runAlgorithm("Bubble", bubbleSort, partialData, "Kismen Sirali", n, csvFile);

        runAlgorithm("Shell", shellSort, randomData, "Rastgele", n, csvFile);
        runAlgorithm("Shell", shellSort, sortedData, "Sirali", n, csvFile);
        runAlgorithm("Shell", shellSort, reverseData, "Ters Sirali", n, csvFile);
        runAlgorithm("Shell", shellSort, partialData, "Kismen Sirali", n, csvFile);

        runAlgorithm("Quick", callQuickSort, randomData, "Rastgele", n, csvFile);
        runAlgorithm("Quick", callQuickSort, sortedData, "Sirali", n, csvFile);
        runAlgorithm("Quick", callQuickSort, reverseData, "Ters Sirali", n, csvFile);
        runAlgorithm("Quick", callQuickSort, partialData, "Kismen Sirali", n, csvFile);

        runAlgorithm("Merge", callMergeSort, randomData, "Rastgele", n, csvFile);
        runAlgorithm("Merge", callMergeSort, sortedData, "Sirali", n, csvFile);
        runAlgorithm("Merge", callMergeSort, reverseData, "Ters Sirali", n, csvFile);
        runAlgorithm("Merge", callMergeSort, partialData, "Kismen Sirali", n, csvFile);

        runAlgorithm("Heap", heapSort, randomData, "Rastgele", n, csvFile);
        runAlgorithm("Heap", heapSort, sortedData, "Sirali", n, csvFile);
        runAlgorithm("Heap", heapSort, reverseData, "Ters Sirali", n, csvFile);
        runAlgorithm("Heap", heapSort, partialData, "Kismen Sirali", n, csvFile);

        runAlgorithm("Quick_FirstPivot", callQuickSortFirstPivot, randomData, "Rastgele", n, csvFile);
        runAlgorithm("Quick_FirstPivot", callQuickSortFirstPivot, sortedData, "Sirali", n, csvFile);
        runAlgorithm("Quick_FirstPivot", callQuickSortFirstPivot, reverseData, "Ters Sirali", n, csvFile);
        runAlgorithm("Quick_FirstPivot", callQuickSortFirstPivot, partialData, "Kismen Sirali", n, csvFile);

        runAlgorithm("Shell_Knuth", shellSortKnuth, randomData, "Rastgele", n, csvFile);
        runAlgorithm("Shell_Knuth", shellSortKnuth, sortedData, "Sirali", n, csvFile);
        runAlgorithm("Shell_Knuth", shellSortKnuth, reverseData, "Ters Sirali", n, csvFile);
        runAlgorithm("Shell_Knuth", shellSortKnuth, partialData, "Kismen Sirali", n, csvFile);
    }

    csvFile.close();
    std::cout << "Testler tamamlandi ve dosya olusturuldu.\n";
    return 0;
}
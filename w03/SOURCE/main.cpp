#include "function.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct sortMethod {
    void (*func)(int a[], int n);
    string name;
};

// Mảng struct để liên kết tên thuật toán với hàm tương ứng
sortMethod sorters[] = {{selectionSort, "selection-sort"}, {insertionSort, "insertion-sort"}, {bubbleSort, "bubble-sort"}, {shakerSort, "shaker-sort"}, {shellSort, "shell-sort"}, {heapSort, "heap-sort"}, {mergeSort, "merge-sort"}, {quickSort, "quick-sort"}, {countingSort, "counting-sort"}, {radixSort, "radix-sort"}, {flashSort, "flash-sort"}};


int* readArrayFromFile(const char* inputFile, int &n) {
    ifstream ifs(inputFile);
    if (!ifs.is_open()) {
        cout << "Can not open input file." << endl;
        return nullptr;
    }
    ifs >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        ifs >> a[i];
    }
    ifs.close();
    return a;
}

void writeArrayToFile(const char* outputFile, int a[], int n) {
    ofstream ofs(outputFile);
    if (!ofs.is_open()) {
        cout << "Can not open output file." << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        ofs << a[i] << " ";
    }
    ofs << endl;
    ofs.close();
}

int main(int argc, char* argv[]) {
    if (argc != 7 || strcmp(argv[1], "-a") != 0 || strcmp(argv[3], "-i") != 0 || strcmp(argv[5], "-o") != 0) {
        cout << "Usage: main.exe -a <algorithm> -i <input_file> -o <output_file>" << endl;
        return 1;
    }

    string algo = argv[2];
    const char* inputFile = argv[4];
    const char* outputFile = argv[6];

    // Tìm thuật toán
    void (*sortFunc)(int[], int) = nullptr;
    for (auto s : sorters) {
        if (s.name == algo) {
            sortFunc = s.func;
            break;
        }
    }

    if (!sortFunc) {
        cout << "Unknown algorithm: " << algo << endl;
        return 1;
    }

    int n;
    int* arr = readArrayFromFile(inputFile, n);
    if (!arr) return 1;

    sortFunc(arr, n);

    writeArrayToFile(outputFile, arr, n);
    delete[] arr;

    return 0;
}

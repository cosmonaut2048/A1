#include "StringSortTester.h"

// MSD Radix Sort без переключения.
void StringSortTester::msdRadixSortRec(std::vector<std::string>& arr, int low, int high, int d) {
    if (high <= low) return;

    // Массивы для подсчета частот.
    std::vector<int> count(ALPHABET_SIZE + 2, 0);

    // Подсчет частот символов на позиции d.
    for (int i = low; i <= high; ++i) {
        int c = charAt(arr[i], d);
        count[c + 2]++;
    }

    // Преобразование в индексы.
    for (int r = 0; r <= ALPHABET_SIZE; ++r) {
        count[r + 1] += count[r];
    }

    std::vector<std::string> aux(high - low + 1);

    // Распределение строк.
    for (int i = low; i <= high; ++i) {
        int c = charAt(arr[i], d);
        aux[count[c + 1]++] = arr[i];
    }

    // Копирование обратно.
    for (int i = low; i <= high; ++i) {
        arr[i] = aux[i - low];
    }

    // Рекурсивно сортируем подмассивы для каждого символа.
    for (int r = 0; r < ALPHABET_SIZE; ++r) {
        msdRadixSortRec(arr, low + count[r], low + count[r + 1] - 1, d + 1);
    }
}

void StringSortTester::msdRadixSort(std::vector<std::string>& arr) {
    if (arr.empty()) return;
    msdRadixSortRec(arr, 0, arr.size() - 1, 0);
}

// MSD Radix Sort с переключением на Ternary QuickSort.
void StringSortTester::msdRadixSortCutoffRec(std::vector<std::string>& arr, int low, int high, int d, int alphabetSize) {
    if (high <= low) return;

    if (high - low + 1 < alphabetSize) {
        ternaryQuickSortRec(arr, low, high, d);
        return;
    }

    std::vector<int> count(ALPHABET_SIZE + 2, 0);

    // Подсчет частот на позиции d.
    for (int i = low; i <= high; ++i) {
        int c = charAt(arr[i], d);
        count[c + 2]++;
    }

    // Преобразование в индексы.
    for (int r = 0; r <= ALPHABET_SIZE; ++r) {
        count[r + 1] += count[r];
    }

    std::vector<std::string> aux(high - low + 1);

    // Распределение строк.
    for (int i = low; i <= high; ++i) {
        int c = charAt(arr[i], d);
        aux[count[c + 1]++] = arr[i];
    }

    // Копирование обратно.
    for (int i = low; i <= high; ++i) {
        arr[i] = aux[i - low];
    }

    // Рекурсивно сортируем подмассивы для каждого символа.
    for (int r = 0; r < ALPHABET_SIZE; ++r) {
        int newLow = low + count[r];
        int newHigh = low + count[r + 1] - 1;
        if (newLow < newHigh) {
            msdRadixSortCutoffRec(arr, newLow, newHigh, d + 1, alphabetSize);
        }
    }
}

void StringSortTester::msdRadixSortWithCutoff(std::vector<std::string>& arr) {
    if (arr.empty()) return;
    msdRadixSortCutoffRec(arr, 0, arr.size() - 1, 0, 74); // 74 -- размер из условия.
}
#ifndef A1_STRINGSORTTESTER_H
#define A1_STRINGSORTTESTER_H

#pragma once
#include <vector>
#include <string>
#include <utility>
#include <chrono>
#include <functional>

class StringSortTester {
public:
    // Стандартные алгоритмы.
    static void quickSort(std::vector<std::string>& arr);
    static void mergeSort(std::vector<std::string>& arr);

    // Специализированные алгоритмы.
    static void ternaryQuickSort(std::vector<std::string>& arr);
    static void stringMergeSort(std::vector<std::string>& arr);
    static void msdRadixSort(std::vector<std::string>& arr);
    static void msdRadixSortWithCutoff(std::vector<std::string>& arr);

    // Функция для измерения времени и количества сравнений.
    static std::pair<double, long long> measurePerformance(
            void (*sortFunc)(std::vector<std::string>&),
            const std::vector<std::string>& data,
            int runs = 10);

private:
    // Вспомогательные функции для StringMergeSort.
    static std::pair<int, size_t> lcpCompare(const std::string& a, const std::string& b, size_t k);
    static std::vector<std::pair<std::string, size_t>> stringMerge(
            const std::vector<std::pair<std::string, size_t>>& P,
            const std::vector<std::pair<std::string, size_t>>& Q);
    static std::vector<std::pair<std::string, size_t>> stringMergeSortRec(
            const std::vector<std::string>& arr);

    // Вспомогательные функции для Ternary QuickSort.
    static void ternaryQuickSortRec(std::vector<std::string>& arr, int low, int high, int d);
    static int charAt(const std::string& s, int d);

    // Вспомогательные функции для MSD Radix Sort.
    static void msdRadixSortRec(std::vector<std::string>& arr, int low, int high, int d);
    static void msdRadixSortCutoffRec(std::vector<std::string>& arr, int low, int high, int d, int alphabetSize);

    static const int ALPHABET_SIZE = 256; // Расширенный ASCII.
    static const int CUTOFF_THRESHOLD = 15; // Порог для переключения на insertion sort.
};

#endif //A1_STRINGSORTTESTER_H
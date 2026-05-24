#include "StringSortTester.h"
#include "char_counter.h"
#include <chrono>
#include <iostream>
#include <algorithm>

std::pair<double, long long> StringSortTester::measurePerformance(
        void (*sortFunc)(std::vector<std::string>&),
        const std::vector<std::string>& data,
        int runs)
{

    // 3 прогона без замеров.
    for (int i = 0; i < 3; ++i) {
        std::vector<std::string> temp = data;
        sortFunc(temp);
    }

    // Замеры.
    std::vector<double> times;
    std::vector<long long> comparisons;

    for (int i = 0; i < runs; ++i) {
        std::vector<std::string> temp = data;
        reset_char_counter();

        auto start = std::chrono::high_resolution_clock::now();
        sortFunc(temp);
        auto end = std::chrono::high_resolution_clock::now();

        double time = std::chrono::duration<double, std::micro>(end - start).count();
        long long comps = get_char_counter();

        times.push_back(time);
        comparisons.push_back(comps);

        // Проверка корректности сортировки.
        if (i == 0) {
            bool isSorted = std::is_sorted(temp.begin(), temp.end());
            if (!isSorted) {
                std::cerr << "WARNING: Sorting algorithm produced incorrect result!" << std::endl;
            }
        }
    }

    // Вычисляем медиану для времени.
    std::sort(times.begin(), times.end());
    std::sort(comparisons.begin(), comparisons.end());

    double median_time = (runs % 2 == 0) ?
                         (times[runs/2 - 1] + times[runs/2]) / 2.0 :
                         times[runs/2];

    long long median_comparisons = (runs % 2 == 0) ?
                                   (comparisons[runs/2 - 1] + comparisons[runs/2]) / 2 :
                                   comparisons[runs/2];

    return {median_time, median_comparisons};
}
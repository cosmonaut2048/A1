#ifndef A1_STRINGGENERATOR_H
#define A1_STRINGGENERATOR_H

#pragma once
#include <string>
#include <vector>
#include <random>
#include <algorithm>

class StringGenerator {
public:
    // Генерирует случайный массив строк.
    static std::vector<std::string> generateRandom(int size);

    // Генерирует массив, отсортированный в обратном лексикографическом порядке.
    static std::vector<std::string> generateReverseSorted(int size);

    // Генерирует почти отсортированный массив.
    static std::vector<std::string> generateAlmostSorted(int size, int swapCount = 10);

    // Генерирует массив строк с длинным общим префиксом.
    static std::vector<std::string> generateWithCommonPrefix(int size, const std::string& basePrefix = "LongCommonPrefix_");

private:
    static std::string generateRandomString();
    static const std::string ALPHABET;

    // Статический генератор случайных чисел.
    static std::mt19937& getRNG();
    static std::uniform_int_distribution<>& getLenDist();
    static std::uniform_int_distribution<>& getCharDist();
};


#endif //A1_STRINGGENERATOR_H

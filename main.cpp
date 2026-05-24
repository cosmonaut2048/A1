#include "StringGenerator.h"
#include "StringSortTester.h"
#include "char_counter.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <iomanip>

int main() {
    std::ofstream resultsFile("sorting_results.csv");
    resultsFile << "Algorithm,DataType,Size,TimeMicroseconds,Comparisons\n";

    std::vector<int> sizes;
    for (int s = 100; s <= 3000; s += 100) sizes.push_back(s);

    using GenFunc = std::function<std::vector<std::string>(int)>;
    std::vector<std::pair<std::string, GenFunc>> dataTypes = {
            {"Random", [](int size) { return StringGenerator::generateRandom(size); }},
            {"ReverseSorted", [](int size) { return StringGenerator::generateReverseSorted(size); }},
            {"AlmostSorted", [](int size) { return StringGenerator::generateAlmostSorted(size); }},
            {"CommonPrefix", [](int size) {
                return StringGenerator::generateWithCommonPrefix(size, "LongCommonPrefix_");
            }},
            {"VeryLongCommonPrefix", [](int size) {
                return StringGenerator::generateWithCommonPrefix(size,
                                                                 "VeryLongCommonPrefixForTestingPurposes_");
            }}
    };

    std::vector<std::pair<std::string, void(*)(std::vector<std::string>&)>> algorithms = {
            {"StandardQuickSort", StringSortTester::quickSort},
            {"StandardMergeSort", StringSortTester::mergeSort},
            {"TernaryQuickSort", StringSortTester::ternaryQuickSort},
            {"StringMergeSort", StringSortTester::stringMergeSort},
            {"MSDRadixSort", StringSortTester::msdRadixSort},
            {"MSDRadixSortWithCutoff", StringSortTester::msdRadixSortWithCutoff}
    };

    std::cout << std::fixed << std::setprecision(2);

    for (const auto& [typeName, genFunc] : dataTypes) {
        std::cout << "Testing data type: " << typeName << std::endl;
        std::cout << "Generating maximum array of 3000 strings..." << std::endl;

        auto maxData = genFunc(3000);
        std::cout << "Generation complete.\n" << std::endl;

        for (int size : sizes) {
            std::cout << "  Size: " << size << std::endl;

            std::vector<std::string> testData(maxData.begin(), maxData.begin() + size);

            for (const auto& [algoName, algoFunc] : algorithms) {
                int runs = (size <= 500) ? 10 : (size <= 1500) ? 7 : 5;

                try {
                    auto [time, comps] = StringSortTester::measurePerformance(
                            algoFunc, testData, runs);

                    resultsFile << algoName << "," << typeName << "," << size << ","
                                << time << "," << comps << "\n";

                    std::cout << "    " << std::left << std::setw(25) << algoName
                              << " Time: " << std::setw(10) << time << " mcs"
                              << " Comparisons: " << comps << std::endl;

                } catch (const std::exception& e) {
                    std::cerr << "    ERROR in " << algoName << ": " << e.what() << std::endl;
                }
            }
            std::cout << std::endl;
        }
        std::cout << "Completed testing for " << typeName << "\n" << std::endl;
    }

    resultsFile.close();
    std::cout << "All tests completed successfully!" << std::endl;
    std::cout << "Results saved to sorting_results.csv" << std::endl;

    return 0;
}
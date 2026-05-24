#include "StringSortTester.h"
#include "char_counter.h"
#include <algorithm>

void StringSortTester::quickSort(std::vector<std::string>& arr) {
    std::sort(arr.begin(), arr.end(), [](const std::string& a, const std::string& b) {
        size_t minLen = std::min(a.length(), b.length());
        for (size_t i = 0; i < minLen; ++i) {
            auto ca = static_cast<unsigned char>(a[i]);
            auto cb = static_cast<unsigned char>(b[i]);
            char_compare(ca, cb);
            if (ca != cb) {
                return ca < cb;
            }
        }
        return a.length() < b.length();
    });
}

void StringSortTester::mergeSort(std::vector<std::string>& arr) {
    std::stable_sort(arr.begin(), arr.end(), [](const std::string& a, const std::string& b) {
        size_t minLen = std::min(a.length(), b.length());
        for (size_t i = 0; i < minLen; ++i) {
            auto ca = static_cast<unsigned char>(a[i]);
            auto cb = static_cast<unsigned char>(b[i]);
            char_compare(ca, cb);
            if (ca != cb) {
                return ca < cb;
            }
        }
        return a.length() < b.length();
    });
}
#include "StringSortTester.h"
#include "char_counter.h"

int StringSortTester::charAt(const std::string& s, int d) {
    if (d < static_cast<int>(s.length())) {
        return static_cast<unsigned char>(s[d]);
    }
    return -1;
}

void StringSortTester::ternaryQuickSortRec(std::vector<std::string>& arr, int low, int high, int d) {
    if (high <= low) return;

    int lt = low, gt = high;
    int v = charAt(arr[low], d);
    int i = low + 1;

    while (i <= gt) {
        int t = charAt(arr[i], d);
        int cmp;
        if (t < v) cmp = -1;
        else if (t > v) cmp = 1;
        else cmp = 0;
        unsigned char ut = (t == -1) ? 0 : static_cast<unsigned char>(t);
        unsigned char uv = (v == -1) ? 0 : static_cast<unsigned char>(v);
        char_compare(ut, uv);

        if (cmp < 0) {
            std::swap(arr[lt], arr[i]);
            ++lt;
            ++i;
        } else if (cmp > 0) {
            std::swap(arr[i], arr[gt]);
            --gt;
        } else {
            ++i;
        }
    }

    // Рекурсивно сортируем три части.
    ternaryQuickSortRec(arr, low, lt - 1, d);
    if (v >= 0) {
        ternaryQuickSortRec(arr, lt, gt, d + 1);
    }
    ternaryQuickSortRec(arr, gt + 1, high, d);
}

void StringSortTester::ternaryQuickSort(std::vector<std::string>& arr) {
    if (arr.empty()) return;
    ternaryQuickSortRec(arr, 0, arr.size() - 1, 0);
}
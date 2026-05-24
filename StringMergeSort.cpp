#include "StringSortTester.h"
#include "char_counter.h"
#include <algorithm>

// LCP-сравнение: возвращает (<, =, >) и длину LCP.
std::pair<int, size_t> StringSortTester::lcpCompare(const std::string& a, const std::string& b, size_t k) {
    // Символы до k включительно уже совпадают. Сравниваем начиная с k.
    size_t i = k;
    while (i < a.size() && i < b.size()) {
        int cmp = char_compare(static_cast<unsigned char>(a[i]), static_cast<unsigned char>(b[i]));
        if (cmp != 0) {
            return {cmp, i}; // i -- длина общего префикса.
        }
        ++i;
    }
    // Одна строка является префиксом другой.
    if (a.size() == b.size()) {
        return {0, a.size()}; // a == b.
    } else if (i == a.size()) {
        return {-1, a.size()}; // a < b.
    } else {
        return {1, b.size()}; // a > b.
    }
}

// Слияние двух отсортированных половин с LCP.
std::vector<std::pair<std::string, size_t>> StringSortTester::stringMerge(
        const std::vector<std::pair<std::string, size_t>>& P,
        const std::vector<std::pair<std::string, size_t>>& Q)
{
    std::vector<std::pair<std::string, size_t>> R;
    size_t i = 0, j = 0;
    size_t m = P.size(), f = Q.size();

    // Копируем для возможности изменения LCP-значений.
    auto P_mod = P;
    auto Q_mod = Q;

    while (i < m && j < f) {
        size_t ki = P_mod[i].second;
        size_t pj = Q_mod[j].second;

        if (ki > pj) {
            R.push_back(P_mod[i]);
            ++i;
        } else if (ki < pj) {
            R.push_back(Q_mod[j]);
            ++j;
        } else {
            auto [cmp_res, h] = lcpCompare(P_mod[i].first, Q_mod[j].first, ki);
            if (cmp_res < 0) { // P[i] < Q[j].
                R.push_back(P_mod[i]);
                ++i;
                if (j < f) {
                    Q_mod[j].second = h; // обновляем LCP для Q[j].
                }
            } else { // P[i] >= Q[j].
                R.push_back(Q_mod[j]);
                ++j;
                if (i < m) {
                    P_mod[i].second = h; // обновляем LCP для P[i].
                }
            }
        }
    }

    while (i < m) {
        R.push_back(P_mod[i]);
        ++i;
    }
    while (j < f) {
        R.push_back(Q_mod[j]);
        ++j;
    }

    return R;
}

// Рекурсивная сортировка.
std::vector<std::pair<std::string, size_t>> StringSortTester::stringMergeSortRec(
        const std::vector<std::string>& arr)
{
    if (arr.size() <= 1) {
        if (arr.empty()) return {};
        return {{arr[0], 0}};
    }

    size_t mid = arr.size() / 2;
    std::vector<std::string> left(arr.begin(), arr.begin() + mid);
    std::vector<std::string> right(arr.begin() + mid, arr.end());

    auto sorted_left = stringMergeSortRec(left);
    auto sorted_right = stringMergeSortRec(right);

    return stringMerge(sorted_left, sorted_right);
}

// Публичная обертка.
void StringSortTester::stringMergeSort(std::vector<std::string>& arr) {
    if (arr.empty()) return;
    auto result = stringMergeSortRec(arr);
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] = result[i].first;
    }
}
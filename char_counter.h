#ifndef A1_CHAR_COUNTER_H
#define A1_CHAR_COUNTER_H

#pragma once
#include <atomic>

extern std::atomic<long long> char_comp_counter;

inline void reset_char_counter() {
    char_comp_counter = 0;
}

inline long long get_char_counter() {
    return char_comp_counter.load();
}

inline int char_compare(unsigned char c1, unsigned char c2) {
    ++char_comp_counter;
    if (c1 < c2) return -1;
    if (c1 > c2) return 1;
    return 0;
}

#endif //A1_CHAR_COUNTER_H
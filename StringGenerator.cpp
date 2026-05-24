#include "StringGenerator.h"
#include <chrono>

const std::string StringGenerator::ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#%:;^&*()-.";

std::mt19937& StringGenerator::getRNG() {
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    return rng;
}

std::uniform_int_distribution<>& StringGenerator::getLenDist() {
    static std::uniform_int_distribution<> dist(10, 200);
    return dist;
}

std::uniform_int_distribution<>& StringGenerator::getCharDist() {
    static std::uniform_int_distribution<> dist(0, ALPHABET.size() - 1);
    return dist;
}

std::string StringGenerator::generateRandomString() {
    int len = getLenDist()(getRNG());
    std::string s(len, '\0');
    for (int i = 0; i < len; ++i) {
        s[i] = ALPHABET[getCharDist()(getRNG())];
    }
    return s;
}

std::vector<std::string> StringGenerator::generateRandom(int size) {
    std::vector<std::string> arr(size);
    for (auto& str : arr) {
        str = generateRandomString();
    }
    return arr;
}

std::vector<std::string> StringGenerator::generateReverseSorted(int size) {
    std::vector<std::string> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = generateRandomString();
    }
    std::sort(arr.begin(), arr.end(), std::greater<std::string>());
    return arr;
}

std::vector<std::string> StringGenerator::generateAlmostSorted(int size, int swapCount) {
    std::vector<std::string> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = generateRandomString();
    }
    std::sort(arr.begin(), arr.end());
    for (int i = 0; i < swapCount; ++i) {
        int idx1 = getRNG()() % size;
        int idx2 = getRNG()() % size;
        std::swap(arr[idx1], arr[idx2]);
    }
    return arr;
}

std::vector<std::string> StringGenerator::generateWithCommonPrefix(int size, const std::string& basePrefix) {
    std::vector<std::string> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = basePrefix + generateRandomString();
    }
    return arr;
}

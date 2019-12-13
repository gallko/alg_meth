#include <gtest/gtest.h>
#include <algorithm>
#include <functional>
#include "sequences.h"
#include "../../src/utils.h"
#include "../../src/lesson_6.5.h"


class TestQuickSort: public ::testing::Test
{
public:
    static std::vector<std::vector<int>> increasing;
    static std::vector<std::vector<int>> decreasing;
    static void SetUpTestSuite() {
        std::cout << std::endl << std::endl << "SetUpTestSuite" << std::endl;
        for(auto &line: increasing) {
            std::sort(line.begin(), line.end(), std::less<int>());
        }
        for(auto &line: decreasing) {
            std::sort(line.begin(), line.end(), std::greater<int>());
        }
    }
};
std::vector<std::vector<int>> TestQuickSort::increasing = sequences::sequence;
std::vector<std::vector<int>> TestQuickSort::decreasing = sequences::sequence;


TEST_F(TestQuickSort, increasing) {
    for(size_t i = 0; i < increasing.size(); ++i) {
        auto tmp(sequences::sequence[i]);
        lesson_6_5::quick_sort(tmp, [](int p1, int p2){
            if (p1 == p2) return 0;
            if (p1 > p2) return 1;
            return -1;
        });
    }
}

TEST_F(TestQuickSort, decreasing) {
    for(size_t i = 0; i < decreasing.size(); ++i) {
        auto tmp(sequences::sequence[i]);
        lesson_6_5::quick_sort(tmp, [](int p1, int p2){
            if (p1 == p2) return 0;
            if (p1 < p2) return 1;
            return -1;
        });
    }
}

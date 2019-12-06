//
// Created by RYunusov on 21.11.2019.
//

#ifndef HELLO_VSC_LESSON_6_1_H
#define HELLO_VSC_LESSON_6_1_H

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

namespace lesson_6_1 {

int get_pos(const std::vector<int> &numbers, int number) {
    // TODO optimize this function
    int left = 0, right = (int)numbers.size() - 1;
    while (left <= right) {
        int middle = (right + left) / 2;
        if (numbers[middle] == number)
            return middle + 1;
        if (number < numbers[middle])
            right = middle - 1;
        else
            left = middle + 1;
    }
    return -1;
}

int main_1(void) {
    size_t number_count;
    std::cin >> number_count;
    std::vector<int> numbers(number_count);
    for (auto &number:numbers) {
        std::cin >> number;
    }
    assert(std::is_sorted(numbers.begin(), numbers.end()));

    size_t query_count;
    std::cin >> query_count;
    while (query_count-- > 0) {
        int number;
        std::cin >> number;
        std::cout << get_pos(numbers, number) << " ";
    }
    std::cout << std::endl;
    return 0;
}
}

#endif //HELLO_VSC_LESSON_6_1_H

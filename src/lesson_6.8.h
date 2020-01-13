#ifndef STEPIKALGORITHMSSTRUCTURES_LESSON_6_8_H
#define STEPIKALGORITHMSSTRUCTURES_LESSON_6_8_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <array>

namespace lesson_6_8
{

    int main_1() {
        std::vector<int> dict(11, 0);
        int count = 0;
        std::cin >> count;
        std::vector<int> in_digit(count);
        std::vector<int> out_digit(count);
        for(auto &it: in_digit) {
            std::cin >> it;
            ++dict[it];
        }
        for(auto it = std::next(dict.begin()); it < dict.end(); ++it) {
            *it += *std::prev(it);
        }
        for(auto it = in_digit.rbegin(); it < in_digit.rend(); ++it) {
            out_digit.at(dict[*it] - 1) = *it;
            dict[*it]--;
        }
        std::copy(out_digit.begin(), out_digit.end(), std::ostream_iterator<int>(std::cout, " "));
        return 0;
    }

}

#endif //STEPIKALGORITHMSSTRUCTURES_LESSON_6_8_H

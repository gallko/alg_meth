//
// Created by RYunusov on 25.11.2019.
//

#ifndef HELLO_VSC_LESSON_6_4_H
#define HELLO_VSC_LESSON_6_4_H

#include <vector>
#include <iostream>
#include <algorithm>

namespace lesson_6_4 {

    template<class T, template<class, class...> class C, class... _args>
    std::ostream &operator<<(std::ostream &os, const C<T, _args...> &m) {
        for (auto &it: m) os << it << " ";
        return os;
    }

    template<template<typename, typename...> class S, typename T, typename ..._args>
    struct helper_sort {
        using iterator = typename S<T, _args...>::iterator;
        using full_type = S<T, _args...>;
        size_t m = 0;

        template<typename _compare>
        full_type _gluing(const full_type &left, const full_type &right, const _compare &comparator) {
            full_type tmp;
            tmp.reserve(left.size() + right.size());
            auto left_it = left.cbegin();
            auto right_it = right.cbegin();
            while (left_it != left.cend() || right_it != right.cend()) {
                if (left_it == left.cend()) {
                    tmp.push_back(std::move(*right_it++));
                } else if (right_it == right.cend()) {
                    tmp.push_back(std::move(*left_it++));
                } else if (comparator(*left_it, *right_it)) {
                    m += left.cend() - left_it;
                    tmp.push_back(std::move(*right_it++));
                } else {
                    tmp.push_back(std::move(*left_it++));
                }
            }
            return tmp;
        }

        template<typename _compare>
        full_type sort(iterator left_begin, iterator left_end, const _compare &comparator) {
            auto c = (left_end - left_begin) / 2;
            if (!c) {
                return full_type{*left_begin};
            }
            auto m1 = sort(left_begin, left_begin + c, comparator);
            auto m2 = sort(left_begin + c, left_end, comparator);
            auto result = _gluing(m1, m2, comparator);
            return result;
        }
    };

    template<template<class, class...> class S, class T, class _compare, class... _args>
    size_t merge_sort(S<T, _args...> &m, const _compare &comparator) {
        auto helper = helper_sort<S, T, _args...>();
        auto r = helper.sort(m.begin(), m.end(), comparator);
        m.swap(r);
        return helper.m;
    }

    int main_1() {
        size_t n = 0;
        std::cin >> n;
        std::vector<int> m(n);
        for (auto &it: m) std::cin >> it;
        std::cout << merge_sort(m, std::greater<int>{}) << std::endl;
        return 0;
    }

}

#endif //HELLO_VSC_LESSON_6_4_H

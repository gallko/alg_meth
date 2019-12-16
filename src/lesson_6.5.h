//
// Created by RYunusov on 27.11.2019.
//

#ifndef HELLO_VSC_LESSON_6_5_H
#define HELLO_VSC_LESSON_6_5_H

#include "utils.h"
#include <fstream>

namespace lesson_6_5 {
    using point2d = std::pair<int, int>;
    using ref_point2d = std::reference_wrapper<point2d>;

    template<template<typename, typename...> class S, typename T, typename ..._args>
    struct helper_qsort {
        using iterator = typename S<T, _args...>::iterator;

        template<typename _compare>
        static void sort(iterator begin, iterator end, const _compare &comparator) {
            if (begin >= (end - 1))
                return;
            iterator new_end, new_begin;
            std::tie(new_end, new_begin) = partition(begin, end, comparator);

            sort(begin, new_end, comparator);

            sort(new_begin, end, comparator);
        }

        template<typename _compare>
        static std::tuple<iterator, iterator> partition(iterator begin, iterator end, const _compare &comparator) {
            auto el = std::reference_wrapper<T>(*begin);
            auto less = begin +1, greater = begin + 1;
            for (auto it = greater; it < end; ++it) {
                auto r = comparator(el.get(), *it);
                if (r > 0) {
                    std::swap(*greater++, *it);
                    std::swap(*(greater - 1), *less++);
                } if (r == 0) {
                    std::swap(*greater++, *it);
                }
            }
            std::swap(el.get(), *(less - 1));
            return std::pair<iterator, iterator>(less, greater);
        }
    };

    template<template<typename, typename...> class S, typename T, typename ..._args>
    struct helper_count_if {
        using iterator = typename S<T, _args...>::iterator;
        template<class _compare>
        iterator count_if(iterator first, iterator last, const _compare &comparator) {

            iterator it;
            typename std::iterator_traits<iterator>::difference_type count, step;
            count = std::distance(first, last);

            while(count > 0) {
                it = first;
                step = count/2;
                std::advance (it, step);
                if (comparator(*it)) {
                    first = ++it;
                    count -= step;
                } else count = step;
            }
            return first;
        }
    };

    template<template<class, class...> class S, class T, class _compare, class... _args>
    void quick_sort(S<T, _args...> &m, const _compare &comparator) {
        helper_qsort<S, T, _args...>::sort(m.begin(), m.end(), comparator);
    }

    template <class ForwardIterator, class T, class _compare>
    size_t count_if(ForwardIterator first, ForwardIterator last, const T& val, _compare comp = std::less<int>()) {
        ForwardIterator middle;
        typename std::iterator_traits<ForwardIterator>::difference_type count, step;
        count = std::distance(first, last);
        while (count > 0) {
            step = count / 2;
            middle = std::next(first, step);
            if (comp(*middle, val)) {
                first = ++middle;
                count -= step+1;
            } else count = step;
        }
        return std::distance(first, last);
    }

    int main_1() {
        std::ifstream in("a.txt");
        std::cin.rdbuf(in.rdbuf());

        int n = 0, m = 0;
        std::cin >> n >> m;
        std::vector<point2d> segments(n);
        std::vector<ref_point2d> ref_segments;
        ref_segments.reserve(n);

        std::vector<int> points(m);
        for(auto &it: segments) {
            std::cin >> it;
            ref_segments.emplace_back(it);
        }
        std::cin >> points;

        quick_sort(segments, [](const point2d& p1, const point2d& p2) -> int {
            if (p1.first == p2.first) return 0;
            if (p1.first > p2.first) return 1;
            return -1;
        });
        quick_sort(ref_segments, [](const ref_point2d& p1, const ref_point2d& p2) -> int {
            if (p1.get().second == p2.get().second) return 0;
            if (p1.get().second > p2.get().second) return 1;
            return -1;
        });

        std::cout << "real: " << segments << std::endl;
        std::cout << "ref : " << ref_segments << std::endl;
        std::cout << points << std::endl;
        return 0;
    }
}

#endif //HELLO_VSC_LESSON_6_5_H

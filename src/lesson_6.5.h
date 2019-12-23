//
// Created by RYunusov on 27.11.2019.
//

#ifndef HELLO_VSC_LESSON_6_5_H
#define HELLO_VSC_LESSON_6_5_H

#include "utils.h"
#include <fstream>
#include <complex>
#include <algorithm>

std::vector<int> v{7,6,5,2,2,2,9};

namespace lesson_6_5 {
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

    template<template<class, class...> class S, class T, class _compare, class... _args>
    void quick_sort(S<T, _args...> &m, const _compare &comparator) {
        helper_qsort<S, T, _args...>::sort(m.begin(), m.end(), comparator);
    }

    template <class ForwardIterator, class T, class _compare>
    ForwardIterator get_position(ForwardIterator first, ForwardIterator last, const T& val, const _compare &comp) {
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
        return first;
    }

    template <class ForwardIterator, class T, class _compare = std::less_equal<int>>
    size_t count_less_equal(ForwardIterator first, ForwardIterator last, const T& val, _compare comp = std::less_equal<int>()) {
        auto tmp = get_position(first, last, val, comp);
        return std::distance(first, tmp);
    }

    template <class ForwardIterator, class T, class _compare = std::less<int>>
    size_t count_greater_equal(ForwardIterator first, ForwardIterator last, const T& val, _compare comp = std::less<int>()) {
        auto tmp = get_position(first, last, val, comp);
        return std::distance(tmp, last);
    }


    template <class ForwardIterator, class _compare>
    std::tuple<ForwardIterator, ForwardIterator> partition(ForwardIterator first, ForwardIterator last, const _compare &comparator) {
        auto middle = std::next(first, std::distance(first, last) >> 1);
    }

    template <class ForwardIterator, class _compare>
    std::tuple<ForwardIterator, ForwardIterator>
            partition_qsort(ForwardIterator first, ForwardIterator last, const _compare &comparator)
    {
        ForwardIterator end, begin;
        end = std::next(first, std::distance(first, last) / 2);
        begin = std::next(end);
        const auto &op = *end;

        while (first < end) {
            auto r = comparator(op, *first);
            if (r < 0) {
                ++first;
            } else if (r > 0) {
                if (begin !=last)
                    std::swap(*first, *std::prev(last--));
                else {
                    std::swap(*--begin, *--end);
                    if (first != end)
                        std::swap(*first, *begin);
                    --last;
                }



            } else /* r == 0 */{
                if (std::prev(end) != first)
                    std::swap(*std::prev(end--), *first);
                else end--;
            }
        }

        while (begin < last) {
            auto el = std::prev(last);
            auto r = comparator(op, *el);
            if (r < 0) {
                std::swap(*end++, *el);
            } else if (r > 0) {
                --last;
            } else /* r == 0 */{
                if (begin != el)
                    std::swap(*std::next(begin++), *el);
                else begin++;
            }
        }

        return std::make_tuple(end, std::next(begin));
    }

    template <class ForwardIterator, class _compare>
    void qsort(ForwardIterator first, ForwardIterator last, const _compare &comp)
    {
        if (std::distance(first, last) <= 1)
            return;
        ForwardIterator first_end, last_begin;
        std::tie<ForwardIterator, ForwardIterator>(first_end, last_begin) =
                partition_qsort(first, last, comp);

        qsort(first, first_end, comp);
        qsort(last_begin, last, comp);
    }

    int main_1() {
//        int n = 0, m = 0;
//        std::cin >> n >> m;
//        std::vector<int> begin(n);
//        std::vector<int> end(n);
//        std::vector<int> points(m);
//        for(auto i = 0; i < n; ++i) {
//            std::cin >> begin[i];
//            std::cin >> end[i];
//        }
//        for(auto &p: points) {
//            std::cin >> p;
//        }
//
//        quick_sort(begin, [](const int& p1, const int& p2) -> int {
//            if (p1 == p2) return 0;
//            if (p1 > p2) return 1;
//            return -1;
//        });
//        quick_sort(end, [](const int& p1, const int& p2) -> int {
//            if (p1 == p2) return 0;
//            if (p1 > p2) return 1;
//            return -1;
//        });
//
//        for(const auto &it: points) {
//            auto r1 = count_less_equal(begin.begin(), begin.end(), it, std::less_equal<int>());
//            auto r2 = count_less_equal(end.begin(), end.end(), it, std::less<int>());
//            std::cout << r1 - r2 << " ";
//        }
        lesson_6_5::qsort(v.begin(), v.end(), [](const int &op, const int &el){
            if (op == el) return 0;
            if (el > op) return 1;
            return -1;
        });
        return 0;
    }
}

#endif //HELLO_VSC_LESSON_6_5_H

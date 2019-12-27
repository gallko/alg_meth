//
// Created by RYunusov on 27.11.2019.
//

#ifndef HELLO_VSC_LESSON_6_5_H
#define HELLO_VSC_LESSON_6_5_H

#include "utils.h"
#include <fstream>
#include <complex>
#include <tuple>

namespace lesson_6_5 {
template <class BidirectionalIterator, class Predicate>
std::tuple<BidirectionalIterator, BidirectionalIterator>
        partition_qsort(BidirectionalIterator first,
                BidirectionalIterator last, const Predicate &cmp)
{
    /**
     * [first,end)              *it <  op
     *       [end, begin)       *it == op
     *            [begin, last) *it >  op
     * */
     ///       end                    begin
    std::tuple<BidirectionalIterator, BidirectionalIterator> _r;
    std::get<0>(_r) = std::next(first,std::distance(first, last) / 2);
    std::get<1>(_r) = std::next( std::get<0>(_r));

    while (first < std::get<0>(_r))
    {
        auto c = cmp(*std::get<0>(_r), *first);
        if (c == 0)
            if (std::next(first) != std::get<0>(_r))
                std::iter_swap(--std::get<0>(_r), first);
            else --std::get<0>(_r);
        else if (c > 0)
            if (std::get<1>(_r) != last)
                std::iter_swap(first, --last);
            else {
                std::iter_swap(first,--std::get<1>(_r));
                --std::get<0>(_r); --last;
                if (first != std::get<0>(_r))
                    std::iter_swap(first, std::get<0>(_r));

            }
        else ++first;
    }

    while (std::get<1>(_r) < last)
    {
        auto c = cmp(*std::get<0>(_r), *std::prev(last));
        if (c == 0) {
            if (std::distance(std::get<1>(_r), last) == 1)
                std::get<1>(_r)++;
            else
                std::iter_swap(std::prev(last), std::get<1>(_r)++);
        }
        else if (c < 0) {
            if (std::prev(last) != std::get<1>(_r))
                std::iter_swap(std::prev(last), std::get<1>(_r));
            std::iter_swap(std::get<0>(_r)++, std::get<1>(_r)++);
        }
        else --last;
    }

    return _r;
}

template <class BidirectionalIterator, class Predicate>
void qsort(BidirectionalIterator first, BidirectionalIterator last, const Predicate &comp)
{
    if (std::distance(first, last) <= 1)
        return;
    BidirectionalIterator first_end, last_begin;
    std::tie<BidirectionalIterator, BidirectionalIterator>
            (first_end, last_begin) = partition_qsort(first, last, comp);

    qsort(first, first_end, comp);
    qsort(last_begin, last, comp);
}

template <class BidirectionalIterator, class T, class Predicate>
BidirectionalIterator left_elem(BidirectionalIterator first, BidirectionalIterator last, const T &el,
        const Predicate &predicate)
{
    using DistanceType = typename std::iterator_traits<BidirectionalIterator>::difference_type;
    DistanceType len = std::distance(first, last);
    while (len > 0)
    {
        DistanceType half = len >> 1;
        BidirectionalIterator mid = std::next(first, half);
        if (predicate(*mid, el)) {
            first = std::next(mid);
            len = len - half - 1;
        } else {
            len = half;
        }
    }
    return first;
}

int main_1() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<int> p1(n);
    std::vector<int> p2(n);
    std::vector<int> points(m);
    for(auto i = 0; i < n; ++i) {
        std::cin >> p1[i];
        std::cin >> p2[i];
    }
    for(auto &p: points) {
        std::cin >> p;
    }

    qsort(p1.begin(), p1.end(), [](const int& op, const int& el) -> int {
        if (op == el) return 0;
        if (op < el) return 1;
        return -1;
    });
    qsort(p2.begin(), p2.end(), [](const int& op, const int& el) -> int {
        if (op == el) return 0;
        if (op < el) return 1;
        return -1;
    });
    for(const auto &it: points) {
        auto r1 = left_elem(p1.begin(), p1.end(), it, std::less_equal<int>());
        auto r2 = left_elem(p2.begin(), p2.end(), it, std::less<int>());
        std::cout << std::distance(p1.begin(), r1) - std::distance(p2.begin(), r2) << " ";
    }

    return 0;

}
}


#endif //HELLO_VSC_LESSON_6_5_H

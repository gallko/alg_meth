//
// Created by RYunusov on 25.11.2019.
//

#ifndef HELLO_VSC_LESSON_6_4_H
#define HELLO_VSC_LESSON_6_4_H

#include <vector>
#include <iostream>

namespace lesson_6_4 {

template<class T, template<class, class...> class C, class... _args>
// iterator
std::ostream &operator<<(std::ostream &os, const C<T, _args...>& m) {
    os << __PRETTY_FUNCTION__ << '\n';
    for(auto &it: m)
        os << it << " ";
    return os;
}

template<class T, template<class, class...> class C, class... _args, class _compare>
// push_back, back, pop_back, [] or/and iterator
size_t insert_sort(C<T, _args...> &m, _compare comparator) {
    using collection = C<T, _args...>;
    collection tmp;
    tmp.push_back(5);



    return 0;
}

int main_1() {
    size_t count = 5;
//    std::cin >> count;
    std::vector<int32_t> m{2, 3, 9, 2, 9};
//    for(auto &it: m)
//        std::cin >> it;

    insert_sort(m, std::greater<int32_t>{});

        std::cout << m << " " << std::endl;
    return 0;
}

}

#endif //HELLO_VSC_LESSON_6_4_H

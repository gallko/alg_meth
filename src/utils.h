//
// Created by RYunusov on 28.11.2019.
//

#ifndef HELLO_VSC_UTILS_H
#define HELLO_VSC_UTILS_H
#include <type_traits>
#include <vector>
#include <iostream>
#include <functional>
#include <cassert>

template<template <typename, typename> class C, typename F, typename S>
typename std::enable_if< std::is_base_of<std::__pair_base<F,S>, C<F,S> >::value, std::istream &>::
type operator>>(std::istream &is, C<F, S> &pair) {
    is >> pair.first >> pair.second;
    return is;
}

template<template <typename, typename ...> class C, typename T, typename ..._args>
typename std::enable_if< true , std::istream &>::
type operator>>(std::istream &is, C<T, _args...> &container) {
    for(auto &it: container) is >> it;
    return is;
}

template<template <typename, typename> class C, typename F, typename S>
typename std::enable_if< std::is_base_of<std::__pair_base<F,S>, C<F,S> >::value, std::ostream &>::
type operator<<(std::ostream &os, const C<F, S> &pair) {
    os << pair.first << ":" << pair.second;
    return os;
}

template<template<class, class...> class C, class T, class... _args>
typename std::enable_if< true , std::ostream &>::
type operator<<(std::ostream &os, C< std::reference_wrapper<T>, _args...> &m) {
    for (const auto it: m) os << it.get() << " ";
    return os;
}


template<template<class, class...> class C, class T, class... _args>
typename std::enable_if<
        !std::is_same<C<T, _args...>, std::string>::value,
std::ostream &>::type operator<<(std::ostream &os, const C<T, _args...> &m) {
    for (const auto &it: m) os << it << " ";
    return os;
}

//template<class _arq>
//std::ostream & operator<<(std::ostream &os, _arq) {
//    assert(false);
//    return os;
//}

#endif //HELLO_VSC_UTILS_H

#pragma once

#include <iostream>

void print() {
    std::cout << std::endl;
}

template <typename T>
void print(T arg, int endl = 1) {
    if (endl) std::cout << arg << std::endl;
    else std::cout << arg;
}

template <typename T, typename... Types>
void print(T arg, Types... args) {
    std::cout << arg << " ";
    print(args...);
}


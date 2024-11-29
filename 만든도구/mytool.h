#pragma once

#include <iostream>
#include <chrono>
#include <thread>


namespace my{
    ////////////////////////////////////////////////////////////////////
    void print() {
        std::cout << std::endl;
    }

    template <typename T>
    void print(T arg, char end = '\n') { // 공백표현은 '\0'
        std::cout << arg << end;
    }

    template <typename T, typename... Types>
    void print(T arg, Types... args) {
        std::cout << arg << " ";
        print(args...);
    }

    ////////////////////////////////////////////////////////////////////
    void sleep(int t) {
        std::this_thread::sleep_for(std::chrono::milliseconds(t));
    }

    //////////////////////////////////////////////////////////////////////
    std::chrono::time_point<std::chrono::high_resolution_clock> time() {
        return std::chrono::high_resolution_clock::now();
    }
    
    template <typename T>
    double get_diff_time(T end, T start) {
        return std::chrono::duration<double>(end - start).count();
    }



}

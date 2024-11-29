
#include <iostream>
#include <algorithm>
#include <vector>
#include "mytool.h"

template <typename Iter>
void print_iter(Iter begin, Iter end) {
    while (begin != end) {
        print(*begin, " ");
        begin++;
    }
    print();
}

struct IntCompare {
    bool operator()(const int& a, const int& b) const { return a > b; }
};

bool int_compare(const int& a, const int& b) { return a > b; }

int main()
{
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(0);
    vec.push_back(1);


    print("정렬전 ---");
    print_iter(vec.begin(), vec.end());

    print("오름차순");
    //std::sort(vec.begin(), vec.end());
    std::stable_sort(vec.begin(), vec.end());
    print_iter(vec.begin(), vec.end());

    print("내림차순");
    auto& func = int_compare;
    //std::sort(vec.begin(), vec.end(), func);
    //std::sort(vec.begin(), vec.end(), int_compare);
    std::sort(vec.begin(), vec.end(),
        [](const int& a, const int& b) -> bool { return a > b; } ); // 람다함수
    print_iter(vec.begin(), vec.end());

}

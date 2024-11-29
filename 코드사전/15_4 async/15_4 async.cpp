
#include <iostream>
#include <future>
#include <vector>
#include <numeric>

#include "mytool.h"
namespace my = mytool;


int main() {
    std::vector<int> data(100000, 1); // 10만 개의 원소를 1로 채운 벡터 생성

    // 벡터를 절반으로 나눈 구간의 반복자 계산
    auto mid = data.begin() + data.size() / 2;

    //int first_half = std::accumulate(data.begin(), mid, 0);
    // 첫 번째 구간의 합을 비동기로 계산 (람다를 사용하여 std::accumulate 호출)
    //std::future<int> first_half = std::async(std::launch::async,
    //    [&]() { return std::accumulate(data.begin(), mid, 0); });
    auto first_half = std::async(std::launch::async,
        [&]() { return std::accumulate(data.begin(), mid, 0); });

    // 두 번째 구간의 합을 메인 스레드에서 계산
    int second_half = std::accumulate(mid, data.end(), 0);

    // 두 구간의 결과를 합산하여 최종 합 계산
    int total_sum = first_half.get() + second_half;

    std::cout << "Total sum: " << total_sum << std::endl;

    return 0;
}
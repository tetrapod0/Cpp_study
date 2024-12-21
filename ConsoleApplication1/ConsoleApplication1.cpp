#include <iostream>
//#include <string>
#include <fstream>
#include "json.hpp"
#include "mytool.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <filesystem>
#include <unordered_set>
#include <map>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

namespace fs = std::filesystem;
using json = nlohmann::json;

bool ready = false;
bool fin = false;

std::mutex m1, m2;
std::condition_variable cv1, cv2;

void notifier() {
    std::unique_lock<std::mutex> lock(m1);
    cv1.wait(lock, [] {return !ready || fin;});
    ready = true;
    my::print("wakeup 1 worker");
    cv2.notify_one();

}


void worker() {
    std::unique_lock<std::mutex> lock(m2);
    cv2.wait(lock, [] {return ready || fin;});
    ready = false;
    my::print("wakeup 1 notifier");
    cv1.notify_one();
}


int main() {

    std::vector<std::thread> worker_threads;
    std::vector<std::thread> notifier_threads;

    for (int i = 0; i < 3; ++i)
        worker_threads.push_back(std::thread(worker));
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    for (int i = 0; i < 3; ++i)
        notifier_threads.push_back(std::thread(notifier));
    


    std::this_thread::sleep_for(std::chrono::milliseconds(5000));  // 대기 시간 추가
    my::print("끝났어");
    fin = true;
    cv1.notify_all();
    cv2.notify_all();


    for (auto& t : worker_threads) t.join();
    for (auto& t : notifier_threads) t.join();

    return 0;
}
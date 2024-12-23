#include <iostream>
//#include <string>
#include <fstream>
#include "json.hpp"
#include "mytool.h"
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <unordered_set>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include "test2.h"
#include <tuple>

namespace fs = std::filesystem;
using json = nlohmann::json;



int main() {
    std::vector<int> int_list;
    int_list.push_back(1);
    int_list.push_back(2);
    int_list.push_back(3);

    std::tuple < std::vector<int>, std::vector<int> > tup = {int_list, int_list};

    int_list[0] = 111;
    int v = std::get<0>(tup)[0];
    std::cout << v << std::endl;

    auto [v1, v2] = tup;
    std::cout << v1[0] << std::endl;

    return 0;
}
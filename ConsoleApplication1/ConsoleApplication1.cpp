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

namespace fs = std::filesystem;
using json = nlohmann::json;



int main() {
    cv::Mat img = cv::imread("./yen_front.jpg");
    cv::imshow("img", img);
    cv::waitKey(0);

    return 0;
}
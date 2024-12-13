#include <iostream>
//#include <string>
#include <fstream>
#include "json.hpp"
#include "mytool.h"
#include <opencv2/opencv.hpp>

using json = nlohmann::json;
using namespace my;

void foo(float a1, float a2, float a3, float a4,
    float a5, float a6, float a7, float a8) {

}

class Foo {
public:
    Foo(float a1, float a2, float a3, float a4,
        float a5, float a6, float a7, float a8) {
    }
};

int main() {
    // json 열기
    std::ifstream i("yen_front.json", std::ios::in);
    json data;
    i >> data;

    json shapes = data["shapes"];
    //print(shapes.dump(2));

    json points = shapes[0]["points"];
    print(points.dump(2));

    json flat = points.flatten();
    print(flat.size());

    //for (auto& v : flat.items()) {
    //    float zz = v.value();
    //    print(zz);
    //}



    std::vector<cv::Point2f> pts = { {1,2}, {3,4} };
    std::vector<cv::Point2f> pts2 = pts;
    std::vector<cv::Point2f> pts3(pts);

    pts[0].x = 99;
    print(pts2[0].x, pts3[0].x);

    pts.insert(pts.begin(), std::move(pts.back()));
    pts.pop_back();
    print(pts.size());

    json aa;
    aa["aa"] = pts;
    aa.get<std::wstring>();

    std::ofstream o("test.json", std::ios::out);
    o << aa;

    return 0;
}
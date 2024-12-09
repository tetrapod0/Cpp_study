

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>


class Point {
public:
	float x, y;
	Point(float x_val, float y_val) : x(x_val), y(y_val) {};
	Point(const Point& p) : x(p.x), y(p.y) {};

	int foo() {
		return bar();
	}
	int bar() {
		return 77;
	}
};

#include <cassert>

int main()
{
	cv::Point2f pos = { 123.22, 33.3 };
	Point pos2 = { 23.3, 4.4 };
	//cv::Point2f pos3 = (cv::Point2f)pos2;

	//cv::getPerspectiveTransform(,);

	std::cout << pos.x << std::endl;

	pos *= 3;
	pos + pos;
	std::cout << pos.x << std::endl;


	int d = 0;
	//assert(d != 0 && "Denominator cannot be zero!");



	std::cout << 16%5 << std::endl;

	Point aa = { 1,2 };
	std::cout << aa.foo() << std::endl;


	std::vector<int> seq_list;
	seq_list = { 1,2,3,4 };
	seq_list.insert(seq_list.end(), { 3,4,5,6 });
	std::cout << seq_list[5] << std::endl;
}


#include <iostream>
#include <algorithm>
#include <vector>
#include "mytool.h"

int main()
{
	std::vector<int> vec1 = { 1,3,3,1,1,5 };
	auto func = [](int v) -> bool {return v % 2;};
	print(std::all_of(vec1.begin(), vec1.end(), func));

	std::vector<int> vec2 = { 1,3,3,1,1,2 };
	auto func2 = [](int v) -> bool {return v % 2==0;};
	print(std::all_of(vec2.begin(), vec2.end(), func2));
	print(std::any_of(vec2.begin(), vec2.end(), func2));
}


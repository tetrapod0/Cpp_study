
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <functional>
#include "mytool.h"

template <typename Iter>
void show_iter(Iter begin, Iter end) {
	while (begin != end) {
		print("[", *begin, "]", '\0');
		begin++;
	}
	print();
}

int main()
{
	std::vector<int> vec;
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	std::vector<int> vec2(6, 0);

	print("처음 vec과 vec2 상태---");
	show_iter(vec.begin(), vec.end());
	show_iter(vec2.begin(), vec2.end());

	print("vec 전체에 1을 더한 것을 vec2 에 저장 ---");
	std::transform(vec.begin(), vec.end(), vec2.begin(), [](int v) {return v + 1;});
	show_iter(vec.begin(), vec.end());
	show_iter(vec2.begin(), vec2.end());

	print("---------");

	auto current = vec.begin();
	while (1) {
		current = std::find_if(current, vec.end(), [](int v) -> bool {return v % 2 == 0;});
		//current = std::find(current, vec.end(), 3);
		if (current == vec.end()) break;
		print(std::distance(vec.begin(), current), "번째원소");
		current++;
	}

}

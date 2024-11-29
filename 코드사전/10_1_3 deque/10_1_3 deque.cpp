
#include <iostream>
#include <deque>
#include "mytool.h"

template <typename T>
void print_deque(std::deque<T>& dq) {
	std::cout << "[ ";
	for (const auto& elem : dq) {
		std::cout << elem << " ";
	}
	std::cout << " ]" << std::endl;
}

int main()
{
	std::deque<int> dq;
	dq.push_back(10);
	dq.push_back(20);
	dq.push_front(30);
	dq.push_front(40);

	print("초기 dq 상태");
	print_deque(dq);

	print("맨 앞의 원소 제거");
	dq.pop_front();
	print_deque(dq);

}


#include "mytool.h"

#include <iostream>
#include <vector>
#include <typeinfo>

template <typename T>
void print_vector(std::vector<T>& vec) {
	// 전체 벡터를 출력하기
	std::cout << "[ ";
	for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end();
		++itr) {
		std::cout << *itr << " ";
	}
	std::cout << "]";
}

int main()
{
	std::vector<int> vec; // 내가 아는 리스트 // insert: O(n), access: O(1)
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);

	// range-based for 문
	for (int elem : vec) {
		std::cout << "원소 : " << elem << std::endl;
	}

	for (int i = 0; i < vec.size(); i++) {
		print("vec의", i + 1, "번째 원소 :", vec[i]);
	}
	print();

	for (std::vector<int>::iterator itr = vec.begin(); itr != vec.end(); ++itr) {
		print(*itr);
	}
	print();

	std::vector<int>::iterator itr = vec.begin() + 2;
	print("3번째 원소 :", *itr);

	vec.insert(vec.begin() + 2, 15);
	print_vector(vec);
	print();

	vec.erase(vec.begin() + 3);
	print_vector(vec);
	print();
}

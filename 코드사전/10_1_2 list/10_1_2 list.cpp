
#include <iostream>
#include <list>

#include "mytool.h"

template <typename T>
void print_list(std::list<T>& lst) {
	std::cout << "[ ";
	for (const auto& elem : lst) {
		std::cout << elem << " ";
	}
	std::cout << "]" << std::endl;
}

int main()
{
	std::list<int> lst; // 양방향 링크드 리스트
	lst.push_back(10);
	lst.push_back(20);
	lst.push_back(30);
	lst.push_back(40);

	for (std::list<int>::iterator itr = lst.begin(); itr != lst.end(); ++itr) {
		print(*itr);
	}
	// itr + 5 // 불가능

	print_list(lst);

	
}

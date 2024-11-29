
#include <iostream>
#include <map>
#include <string>
#include "mytool.h"

template <typename K, typename V>
void print_map(std::map<K, V>& m) {
	for (auto itr = m.begin(); itr != m.end(); ++itr) print(itr->first, itr->second);
}

int main()
{
	std::map<std::string, double> pitcher_list; // 이것도 트리 구조

	// 맵의 insert 함수는 pair 객체를 인자로 받습니다.
	pitcher_list.insert(std::pair<std::string, double>("박세웅", 2.23));
	pitcher_list.insert(std::pair<std::string, double>("해커", 2.93));
	pitcher_list.insert(std::pair<std::string, double>("피어밴드", 2.95));
	pitcher_list.insert(std::make_pair("차우찬", 3.04));
	pitcher_list.insert(std::make_pair("정원준", 3.05));
	pitcher_list.insert(std::make_pair("헥터", 3.09));
	pitcher_list["니퍼트"] = 3.56;
	pitcher_list["박종훈"] = 3.76;
	pitcher_list["켈리"] = 3.90;

	print_map(pitcher_list);
	print("박세웅?", pitcher_list["박세웅2"]);

	print_map(pitcher_list);


	std::string key = "test";
	auto itr = pitcher_list.find(key);
	if (itr != pitcher_list.end()) {
		std::cout << key << " --> " << itr->second << std::endl;
	}
	else {
		std::cout << key << "은(는) 목록에 없습니다" << std::endl;
	}
}

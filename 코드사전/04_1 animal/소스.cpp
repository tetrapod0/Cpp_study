# include <iostream>
# include "test.h"

void test() {
	std::cout << "test" << std::endl;
}

namespace test_namespace {
	int Animal::val = 10; // static 변수는 외부에서 초기화

	// 디폴트 복사 생성자에 의존하면 안됨 // 여기서 깊은복사 만들어줘야됨
	Animal::Animal(const Animal& animal) {
		food = animal.food;
		weight = animal.weight;
	}

	Animal::Animal(int food, int weight) {
		//this->food = food;
		Animal::food = food;
		this->weight = weight;
	}

	Animal& Animal::increase_food(int inc) {
		food += inc;
		//this->food += inc;
		//Animal::food += inc;
		weight += (inc / 3);
		return *this;
	}

	void Animal::view_stat() {
		std::cout << "이 동물의 food  \t: " << food << std::endl;
		std::cout << "이 동물의 weight\t: " << weight << std::endl;
	}
}
# include <iostream>
# include "test.h"

void test() {
	std::cout << "test" << std::endl;
}

namespace test_namespace {
	int Animal::val = 10; // static ������ �ܺο��� �ʱ�ȭ

	// ����Ʈ ���� �����ڿ� �����ϸ� �ȵ� // ���⼭ �������� �������ߵ�
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
		std::cout << "�� ������ food  \t: " << food << std::endl;
		std::cout << "�� ������ weight\t: " << weight << std::endl;
	}
}
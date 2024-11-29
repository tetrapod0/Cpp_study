#pragma once

void test();

namespace test_namespace{
	class Animal {
	private:
		int food;
		int weight;
	public:
		static int val; // 외부에서 초기화해야됨
		static const int val2 = 20; // 이 경우는 선언과 동시에 초기화

		Animal() = default; // 기본 생성자 // 없어도되는데 명시한거임
		Animal(const Animal& animal); // 복사 생성자
		Animal(int food, int weight);
		Animal& increase_food(int inc);
		void view_stat();
	};
}
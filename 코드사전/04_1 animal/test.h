#pragma once

void test();

namespace test_namespace{
	class Animal {
	private:
		int food;
		int weight;
	public:
		static int val; // �ܺο��� �ʱ�ȭ�ؾߵ�
		static const int val2 = 20; // �� ���� ����� ���ÿ� �ʱ�ȭ

		Animal() = default; // �⺻ ������ // ����Ǵµ� ����Ѱ���
		Animal(const Animal& animal); // ���� ������
		Animal(int food, int weight);
		Animal& increase_food(int inc);
		void view_stat();
	};
}
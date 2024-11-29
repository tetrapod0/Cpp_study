
#include <iostream>
#include <thread>
#include "mytool.h"

void func1() {
	for (int i = 0;i < 10;i++) print("thread1");
}

void func2() {
	for (int i = 0;i < 10;i++) print("thread2");
}

void func3() {
	for (int i = 0;i < 10;i++) print("thread3");
}


int main()
{
	std::thread t1(func1);
	std::thread t2(func2);
	std::thread t3(func3);

	// t1.join();
	// t2.join();
	// t3.join();

	t1.detach(); // 백그라운드로
	t2.detach();
	t3.detach();
	
	// detach 되지 않은 쓰레드가 실행중에 메인이 종료되면 에러
	print("메인종료");
}

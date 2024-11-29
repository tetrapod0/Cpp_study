
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include "mytool.h"

void worker(int& result, std::mutex& m) {
	for (int i = 0; i < 10000; i++) {
		m.lock();
		result += 1;
		m.unlock();
	}
}

void worker2(int& result, std::mutex& m) {
	for (int i = 0; i < 10000; i++) {
		std::lock_guard<std::mutex> lock(m);
		result += 1;
	}
}

void run() {

	int counter = 0;
	std::mutex m;
	std::vector<std::thread> workers;
	for (int i = 0;i < 4;i++) {
		//workers.push_back(std::thread(worker, std::ref(counter), std::ref(m)));
		workers.push_back(std::thread(worker2, std::ref(counter), std::ref(m)));
	}

	for (int i = 0; i < 4;i++) workers[i].join(); // 

	print("최종값:", counter);
}

//int main() {
//	run();
//	std::this_thread::sleep_for(std::chrono::seconds(1));
//	print("메인종료");
//}

int main() {
	{

		int counter = 0;
		std::mutex m;
		std::vector<std::thread> workers;
		for (int i = 0;i < 4;i++) {
			//workers.push_back(std::thread(worker, std::ref(counter), std::ref(m)));
			workers.push_back(std::thread(worker2, std::ref(counter), std::ref(m)));
		}

		//for (int i = 0; i < 4;i++) workers[i].join(); // 
		//for (int i = 0; i < 4;i++) workers[i].detach(); // 

		std::this_thread::sleep_for(std::chrono::seconds(1));
		print("최종값:", counter);
	}
	std::this_thread::sleep_for(std::chrono::seconds(1));
	print("메인종료");
}

//int main()
//{
//	int counter = 0;
//	std::mutex m;
//	std::vector<std::thread> workers;
//	for (int i = 0;i < 4;i++) {
//		//workers.push_back(std::thread(worker, std::ref(counter), std::ref(m)));
//		workers.push_back(std::thread(worker2, std::ref(counter), std::ref(m)));
//	}
//
//	for (int i = 0; i < 4;i++) workers[i].join();
//
//	print("최종값:", counter);
//}


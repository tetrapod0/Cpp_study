
#include <iostream>
#include <stdexcept>
#include "mytool.h"

int divide(int a, int b) {
	if (b == 0) {
		throw std::invalid_argument("Division by zero error");  // 예외를 발생시킴
	}
	return a / b;
}

int main()
{
	//throw "throw!";
	//throw std::out_of_range("vector 의 index 가 범위를 초과하였습니다.");
	print("hello1");

	try {
		int a = 10;
		int b = 0;
		int result = divide(a, b);
		print("Result:", result);
		//throw "throw!";
	}
	catch (const std::invalid_argument& e) {  // invalid_argument 예외를 잡음
		std::cerr << "Caught exception: " << e.what() << std::endl;
	}
	catch (...) {
		print("예외발생!");
	}
	print("hello");
	
}

#include "mycomplex.h"
#include <iostream>
#include <format>
#include <string>
#include <cassert>


MyComplex::MyComplex(double real, double img) {
	this->real = real;
	this->img = img;
}

MyComplex::MyComplex(const char* str0) {
	// 공백 제거
	std::string str = str0;
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	int index = str.find('i');

	// i 기준 문자열 분할
	std::string str1 = str.substr(0, index-1);
	std::string str2 = str.substr(index + 1);

	// 값 변환 및 할당
	this->real = 0;
	this->img = 0;
	if (index == -1) {
		this->real = std::stod(str);
	}
	else if (index == 0) {
		this->img = std::stod(str2);
	}
	else {
		if (str1.length()) this->real = std::stod(str1);
		this->img = 1;
		if (str2.length()) this->img *= std::stod(str2);
		assert(str[index - 1] == '-' || str[index - 1] == '+');
		if (str[index - 1] == '-') this->img *= -1;
	}
}

MyComplex::MyComplex(const MyComplex& c) {
	this->real = c.real;
	this->img = c.img;
	std::cout << "복사생성자" << std::endl;
}

MyComplex::~MyComplex() {
	//std::cout << "소멸자" << std::endl;
}

//MyComplex MyComplex::operator+(const MyComplex& c) const {
//	return MyComplex(this->real + c.real, this->img + c.img);
//}

MyComplex MyComplex::operator-(const MyComplex& c) const {
	return MyComplex(this->real - c.real, this->img - c.img);
}

MyComplex MyComplex::operator*(const MyComplex& c) const {
	return MyComplex(
		this->real * c.real - this->img * c.img,
		this->real * c.img + this->img * c.real);
}

MyComplex MyComplex::operator/(const MyComplex& c) const {
	return MyComplex(
		(this->real * c.real + this->img * c.img) / (c.real * c.real + c.img * c.img),
		(this->img * c.real - this->real * c.img) / (c.real * c.real + c.img * c.img));
}

MyComplex& MyComplex::operator=(const MyComplex& c) {
	this->real = c.real;
	this->img = c.img;
	return *this;
}

MyComplex& MyComplex::operator+=(const MyComplex& c) {
	this->real += c.real;
	this->img += c.img;
	return *this;
}

MyComplex& MyComplex::operator-=(const MyComplex& c){
	this->real -= c.real;
	this->img -= c.img;
	return *this;
}

MyComplex& MyComplex::operator*=(const MyComplex& c){
	this->real = this->real * c.real - this->img * c.img;
	this->img = this->real * c.img + this->img * c.real;
	return *this;
}

MyComplex& MyComplex::operator/=(const MyComplex& c){
	this->real = (this->real * c.real + this->img * c.img) / (c.real * c.real + c.img * c.img);
	this->img = (this->img * c.real - this->real * c.img) / (c.real * c.real + c.img * c.img);
	return *this;
}


void MyComplex::println() const {
	std::cout << std::format("({:.4f}, {:.4f})", this->real, this->img) << std::endl;
}


MyComplex operator+(const MyComplex& a, const MyComplex& b) {
	return MyComplex(a.real + b.real, a.img + b.img);
}

std::ostream& operator<<(std::ostream& os, const MyComplex& c) {
	os << "(" << c.real << ", " << c.img << ")";
	return os;
}
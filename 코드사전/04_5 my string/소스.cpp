#include <iostream>
#include <string.h>
#include "mystring.h"
//#include <memory>

MyString::MyString(char c) {
	this->content = new char[1];
	this->content[0] = c;
	this->length = 1;
	this->capacity = 1;
}

MyString::MyString(const char* str) {
	this->length = strlen(str);
	this->capacity = this->length;
	this->content = new char[this->length];
	for (int i = 0; i < this->length; i++) {
		this->content[i] = str[i];
	}
}

MyString::MyString(const MyString& str) {
	this->content = new char[str.length];
	this->length = str.length; // 같은 클래스의 다른 객체라도 클래스 내부라면 접근가능
	this->capacity = this->length;
	for (int i = 0; i < this->length; i++) {
		this->content[i] = str.content[i];
	}
}

MyString::~MyString() {
	delete[] this->content;
}

int MyString::get_length() const {
	return this->length;
}

int MyString::get_capacity() const {
	return this->capacity;
}

void MyString::print() const {
	for (int i = 0; i < this->length; i++) {
		std::cout << this->content[i];
	}
	std::cout << std::endl;
}

char MyString::at(int i) const {
	if (i < 0 || this->length <= i) return NULL;
	return this->content[i];
}

MyString& MyString::assign(const MyString& str) {
	if (this->length < str.length) {
		delete[] this->content;
		this->content = new char[str.length];
		this->capacity = str.length;
	}
	this->length = str.length;
	for (int i = 0; i < this->length; i++) this->content[i] = str.content[i];
	return *this;
}

//MyString& MyString::assign(const char* str) {
//	int str_length = strlen(str);
//	if (this->length < str_length) {
//		delete[] this->content;
//		this->content = new char[str_length];
//		this->capacity = str_length;
//	}
//	this->length = str_length;
//	for (int i = 0; i < this->length; i++) this->content[i] = str[i];
//	return *this;
//}

MyString& MyString::reserve(int size) {
	if (size <= this->capacity) return *this;

	char* big_cap_content = new char[size];
	for (int i = 0; i < this->length; i++) big_cap_content[i] = this->content[i];
	delete[] this->content;
	this->content = big_cap_content;
	this->capacity = size;
	return *this;
}

MyString& MyString::insert(int loc, const MyString& str) {
	// loc이 범위를 넘어가면 수행안함
	if (loc < 0 || this->length < loc) return *this;

	// 더 큰 수용량 배열로 이동
	int new_length = this->length + str.length;
	if (this->capacity < new_length && new_length < this->capacity*2) {
		this->reserve(this->capacity * 2);
	}
	else if (this->capacity * 2 <= new_length){
		this->reserve(new_length);
	}

	// 문자열 사이에 넣기
	for (int i = this->length-1; i >= loc; i--) this->content[str.length+i] = this->content[i];
	for (int i = 0; i < str.length; i++) this->content[loc+i] = str.content[i];
	this->length = new_length;

	return *this;
}

//MyString& MyString::insert(int loc, const char* str) {
//	return this->insert(loc, MyString(str));
//}
//
//MyString& MyString::insert(int loc, const char c) {
//	return this->insert(loc, MyString(c));
//}

MyString& MyString::erase(int loc, int num) {
	// loc이 범위를 넘어가면 수행안함
	if (num <= 0 || loc < 0 || this->length < loc) return *this;
	if (num > this->length - loc) num = this->length - loc;
	// 지우기
	for (int i = loc + num; i < this->length; i++) this->content[i - num] = this->content[i];
	this->length -= num;
	return *this;
}

int MyString::find(int find_from, const MyString& str) const {
	if (str.length == 0) return -1;

	int i, j;
	for (i = find_from; i <= this->length - str.length; i++) {
		for (j = 0; j < str.length; j++) {
			if (this->content[i + j] != str.content[j]) break;
		}
		if (j == str.length) return i;
	}
	return -1;
}

//int MyString::find(int find_from, const char* str) const {
//	return this->find(find_from, MyString(str));
//}
//
//int MyString::find(int find_from, char c) const {
//	return this->find(find_from, MyString(c));
//}

int MyString::compare(const MyString& str) const {
	for (int i = 0; i < std::min(this->length, str.length); i++) {
		if (this->content[i] > str.content[i]) return 1;
		else if (this->content[i] < str.content[i]) return -1;
	}
	if (this->length > str.length) return 1;
	else if (this->length < str.length) return -1;
	return 0;
}

//int MyString::compare(const char* str) const {
//	return this->compare(MyString(str));
//}
//
//
//int MyString::compare(const char c) const {
//	return this->compare(MyString(c));
//}

bool MyString::operator==(const MyString& str) const {
	return !this->compare(str);
}





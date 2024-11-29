#pragma once

class MyString {
private:
	char* content; // 문자배열 포인터
	int length; // 현재 문자열의 길이
	int capacity; // 최대 문자열 수용량
public:
	MyString() = default;
	MyString(char c);
	MyString(const char* str);
	//MyString(const MyString&) = default;
	MyString(const MyString& str);
	~MyString();

	int get_length() const;
	int get_capacity() const;
	void print() const;
	char at(int i) const;

	MyString& assign(const MyString& str);
	//MyString& assign(const char* str);
	MyString& reserve(int size);
	MyString& insert(int loc, const MyString& str);
	//MyString& insert(int loc, const char* str);
	//MyString& insert(int loc, const char c);
	MyString& erase(int loc, int num);

	int find(int find_from, const MyString& str) const;
	//int find(int find_from, const char* str) const;
	//int find(int find_from, char c) const;

	int compare(const MyString& str) const;
	//int compare(const char* str) const;
	//int compare(const char c) const;

	bool operator==(const MyString& str) const;
};
#pragma once

class MyString {
private:
	char* content; // ���ڹ迭 ������
	int length; // ���� ���ڿ��� ����
	int capacity; // �ִ� ���ڿ� ���뷮
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
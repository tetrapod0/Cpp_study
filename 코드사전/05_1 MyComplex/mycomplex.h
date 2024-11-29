#pragma once

#include <string>

class MyComplex {
private:
	double real, img;

public:
	MyComplex(double real, double img);
	MyComplex(const char* str0);
	MyComplex(const MyComplex& c);
	~MyComplex();

	//MyComplex operator+(const MyComplex& c) const;
	MyComplex operator-(const MyComplex& c) const;
	MyComplex operator*(const MyComplex& c) const;
	MyComplex operator/(const MyComplex& c) const;
	MyComplex& operator=(const MyComplex& c); //��� ����Ʈ ���Կ����ڵ� ����

	MyComplex& operator+=(const MyComplex& c);
	MyComplex& operator-=(const MyComplex& c);
	MyComplex& operator*=(const MyComplex& c);
	MyComplex& operator/=(const MyComplex& c);

	void println() const;

	friend MyComplex operator+(const MyComplex& a, const MyComplex& b);
	friend std::ostream& operator<<(std::ostream& os, const MyComplex& c);
};

MyComplex operator+(const MyComplex& a, const MyComplex& b);

std::ostream& operator<<(std::ostream& os, const MyComplex& c);

#include <iostream>
#include <set>
#include <string>
#include "mytool.h"

template <typename T>
//void print_set(std::set<T>& s) {
void print_set(const T& s) {
	std::cout << "[ ";
	//for (typename std::set<T>::iterator itr = s.begin(); itr != s.end(); ++itr) {
	//	std::cout << *itr << " ";
	//}
	for (const auto& elem : s) print(elem, " ", 0);
	std::cout << " ]" << std::endl;
}

class Todo {
private:
	int priority;
	std::string job_desc;
public:
	Todo(int priority, std::string job_desc) {
		this->priority = priority;
		this->job_desc = job_desc;
	}

	bool operator<(const Todo& t) const { // 중요도가 같으면 set에서 중복처리함
		if (this->priority == t.priority) return this->job_desc < t.job_desc;
		return this->priority < t.priority;
	}
	friend class TodoCmp;
	friend std::ostream& operator<<(std::ostream& o, const Todo& td);
};

std::ostream& operator<<(std::ostream& o, const Todo& td) {
	o << "[ 중요도: " << td.priority << "] " << td.job_desc;
	return o;
}

class TodoCmp { // Todo 클래스 안에 따로 operator<를 정의 하고 싶지 않다면 
public:
	bool operator()(const Todo& t1, const Todo& t2) const {
		if (t1.priority == t2.priority) return t1.job_desc < t2.job_desc;
		return t1.priority < t2.priority;
	}
};


int main()
{
	std::set<int> s; // 트리구조
	s.insert(20);
	s.insert(10);
	s.insert(30);
	s.insert(40);
	s.insert(40);
	s.insert(50);
	//print(s[0]); 안됨

	print("순서대로 정렬되서 나온다");
	print_set(s);

	print("20이 s의 원소인가요?", 0);
	auto itr = s.find(20);
	//없으면 끝을 가리키나봄
	if (itr != s.end()) print("Yes");
	else print("No");

	print("25가 s의 원소인가요?", 0);
	itr = s.find(25);
	if (itr != s.end()) print("Yes");
	else print("No");

	print("--------------------------------");

	//std::set<Todo> todos;
	std::set<Todo, TodoCmp> todos;// Todo 클래스 안에 따로 operator<를 정의 하고 싶지 않다면
	todos.insert(Todo(1, "농구"));
	todos.insert(Todo(2, "수학"));
	todos.insert(Todo(1, "코딩"));
	todos.insert(Todo(3, "친구"));
	todos.insert(Todo(2, "영화"));

	print_set(todos);

	print("----");
	print("수학 끝!");
	todos.erase(todos.find(Todo(2, "수학")));
	print_set(todos);
}

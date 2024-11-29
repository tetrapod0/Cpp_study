
//#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
#include "mytool.h"

template <typename K>
void print_unordered_set(const std::unordered_set<K>& m) {
    for (const auto& elem : m) print(elem);
}

//template <typename K>
//void is_exist(const std::unordered_set<K>&s, const K key) {
template <typename T, typename K>
void is_exist(const T& s, const K key) {
    auto itr = s.find(key);
    if (itr != s.end()) print(key, "가 존재!");
    else print(key, "가 없다");
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

    bool operator==(const Todo& t) const {
        return this->priority == t.priority && this->job_desc == t.job_desc;
    }

    friend std::ostream& operator<<(std::ostream& o, const Todo& t);
    friend struct std::hash<Todo>;
};

std::ostream& operator<<(std::ostream& o, const Todo& t) {
    o << "[중요도 : " << t.priority << " ] " << t.job_desc;
    return o;
}

namespace std {
    template <>
    struct hash<Todo> {
        size_t operator()(const Todo& t) const {
            hash<string> hash_func;
            return t.priority ^ (hash_func(t.job_desc));
        }
    };
}


int main()
{
    std::unordered_set<std::string> s; // 내가 아는 (hash) set
    s.insert("hi");
    s.insert("my");
    s.insert("name");
    s.insert("is");
    s.insert("c++");

    print_unordered_set(s);
    print("------");

    is_exist(s, std::string("c++"));
    is_exist(s, "c");
    print();

    print("'hi'를 삭제");
    //s.erase(s.find("hi"));
    s.erase("hi");
    is_exist(s, "hi");

    print("-------------------------");

    std::unordered_set<Todo> todos;
    todos.insert(Todo(1, "농구 하기"));
    todos.insert(Todo(2, "수학 숙제 하기"));
    todos.insert(Todo(1, "프로그래밍 프로젝트"));
    todos.insert(Todo(3, "친구 만나기"));
    todos.insert(Todo(2, "영화 보기"));
    print_unordered_set(todos);
    print("---------");
}
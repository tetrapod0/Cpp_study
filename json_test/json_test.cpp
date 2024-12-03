#include <iostream>
#include <fstream>
#include "json.hpp"
#include "mytool.h"

// https://github.com/nlohmann/json
using namespace my;
using json = nlohmann::json;



// a simple struct to model a person
namespace ns {
    struct person {
        std::string name;
        std::string address;
        int age;
        bool operator==(const person& p) {
            return this->name == p.name && this->address == p.address && this->age == p.age;
        }
    };

    void to_json(json& j, const person& p) {
        j = json{ {"name", p.name}, {"address", p.address}, {"age", p.age} };
    }

    void from_json(const json& j, person& p) {
        j.at("name").get_to(p.name);
        j.at("address").get_to(p.address);
        j.at("age").get_to(p.age);
    }

}


int main()
{
    // create an empty structure (null)
    json j;
    //j['a'] = 'a';
    //j[123] = 'a';
    j["a"] = 'a';
    j["pi"] = 3.141;
    j["happy"] = true;
    j["name"] = "Niels";
    j["nothing"] = nullptr;
    // test1
    print("-----------test1");
    // 되도록이면 get을 써라.
    print(j["name"]); // "Niels" 따옴표까지
    print(j["name"].template get<std::string>()); // Niels
    print(j["name"].get<std::string>()); // Niels
    print();

    // add an object inside the object
    j["answer"]["everything"] = 42;

    // add an array that is stored as std::vector (using an initializer list)
    j["list"] = { 1, 0, 2 };

    // add another object (using an initializer list of pairs)
    j["object"] = { {"currency", "USD"}, {"value", 42.99}};

    // instead, you could also write (which looks very similar to the JSON above)
    json j2 = {
      {"pi", 3.141},
      {"happy", true},
      {"name", "Niels"},
      {"nothing", nullptr},
      {"answer", {
        {"everything", 42}
      }},
      {"list", {1, 0, 2}},
      {"object", {
        {"currency", "USD"},
        {"value", 42.99}
      }}
    };

    json j3 = json::array();
    j3[3] = 123;
    j3.push_back("22");
    // test2
    print("-----------test2");
    print(j3); // [null, null, null, 123, "22"]
    print();


    // ways to express the empty object {}
    json empty_object_implicit = json({}); // {}
    json empty_object_explicit = json::object(); // {}
    // test3
    print("-----------test3");
    print(empty_object_implicit);
    print(empty_object_explicit);
    print();

    json j5 = {}; // null
    json j6 = json(); // null
    // test4
    print("-----------test4");
    print(j5, j6);
    print();

    // a way to express an _array_ of key/value pairs [["currency", "USD"], ["value", 42.99]]
    json array_not_object = json::array({ {"currency", "USD"}, {"value", 42.99} }); // [["currency", "USD"], ["value", 42.99]]
    json j4 = { {"currency", "USD"}, {"value", 42.99} }; // {"currency": "USD", "value": 42.99}
    // test5
    print("-----------test5");
    print(array_not_object);
    print(j4);
    print();

    // parse explicitly
    auto j7 = json::parse(R"({"happy": true, "pi": 3.141})");
    // test6
    print("-----------test6");
    print(j7);
    print();

    // explicit conversion to string
    std::string s = j7.dump();    // {"happy":true,"pi":3.141}
    // test7
    print("-----------test7");
    print(s);
    print(j7.dump(4)); // pretty
    print();

    // test8
    print("-----------test8");
    // retrieve the string value
    json j_string = "this is a string";
    print(j_string); // "this is a string"
    auto cpp_string = j_string.template get<std::string>();
    print(cpp_string); // this is a string
    std::string cpp_string2;
    j_string.get_to(cpp_string2);
    print(cpp_string2); // this is a string
    print();

    // test9
    print("-----------test9");
    // retrieve the serialized value (explicit JSON serialization)
    std::string serialized_string = j_string.dump();
    print(serialized_string); // "this is a string"
    print("\"this is a string\"");
    print();

    // test10
    print("-----------test10");
    std::ofstream o("test.json", std::ios::out);
    //o << j2 << std::endl;
    //o << std::setw(4) << j2 << std::endl;
    o << j2.dump(2) << std::endl;

    std::ifstream i("test.json", std::ios::in);
    json j8;
    i >> j8;
    print(j8.dump(2));

    json j9;
    std::ofstream o2("str.json", std::ios::out);
    o2 << json("test str") << std::endl;
    std::ifstream i2("str.json", std::ios::in);
    i2 >> j9;
    print(j9);
    print();

    // test11
    print("-----------test11");
    for (json::iterator it = j8.begin(); it != j8.end(); ++it) {
        std::cout << *it << '\n';
    }
    for (json::iterator it = array_not_object.begin(); it != array_not_object.end(); ++it) {
        std::cout << *it << '\n';
    }
    // the same code as range for
    for (auto& el : j8.items()) {
        std::cout << el.key() << " : " << el.value() << "\n";
    }
    // even easier with structured bindings (C++17)
    for (auto& [key, value] : j8.items()) {
        std::cout << key << " : " << value << "\n";
    }
    print();

    // test12
    print("-----------test12");
    for (auto& element : j8) {
        std::cout << element << '\n';
    }
    print();

    // test13
    print("-----------test13");
    print(j8.at("pi"), j8["pi"], j8["ssss"]); // 3.14, 3.14 null
    print(j8);
    print(array_not_object.at(1), array_not_object[1]);
    print();

    // test14
    print("-----------test14");
    //json j10;
    //json j10 = json::array();
    json j10 = { 1, 2, 3, 4 };
    //json j10 = json::object();
    //json j10 = true;
    //json j10 = 123;
    //json j10 = "123";
    print(j10);
    print("j10.is_null()", j10.is_null());
    print("j10.is_boolean()", j10.is_boolean());
    print("j10.is_number()", j10.is_number());
    print("j10.is_object()", j10.is_object());
    print("j10.is_array()", j10.is_array());
    print("j10.is_string()", j10.is_string());
    print();
    j10[2] = std::map<std::string, int>{ {"one", 1}, {"two", 2}, {"three", 3} };
    print(j10);
    //j10.insert(2, 12);

    // test15
    print("-----------test15");

    // create a person
    ns::person pp{ "Ned Flanders", "744 Evergreen Terrace", 60 };

    // conversion: person -> json
    json j11 = pp;

    std::cout << j11 << std::endl;
    // {"address":"744 Evergreen Terrace","age":60,"name":"Ned Flanders"}

    // conversion: json -> person
    auto p2 = j11.template get<ns::person>();

    // that's it
    assert(pp == p2);
    print();


    // test13
    print("-----------test13");
    print();
}

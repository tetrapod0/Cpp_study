// 04_1 animal.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
# include "test.h"
using namespace test_namespace;


int main()
{
    std::cout << "Hello World!\n";
    test();

    // 자동 할당 방식 // stack
    //Animal animal1(12, 33); // 암시적 방법
    Animal animal1 = Animal(12, 33); // 명시적 방법
    animal1.increase_food(123).increase_food(123);
    animal1.view_stat();

    // 동적 할당 방식 // heap
    Animal* animal2 = new Animal(12, 33);
    animal2->increase_food(22).increase_food(22);
    animal2->view_stat();
    delete animal2;  // 동적 할당 해제

    Animal animal3 = *(new Animal(12, 33)); // 이렇게하면 힙메모리 누수 // 힙에서 스택으로 객체복사

    Animal animal_list[3]; // 기본 생성자가 있어야됨.
    animal_list[0] = Animal(5, 5);
    animal_list[1] = Animal(5, 5);
    animal_list[2] = Animal(5, 5);

    //Animal animal_list[3] = { // 기본 생성자 없어도됨.
    //    Animal(5,5),
    //    Animal(5,5),
    //    Animal(5,5),
    //};

    Animal* animal_list2 = new Animal[3]; // 기본 생성자가 있어야됨.
    animal_list2[0] = Animal(5, 5);
    animal_list2[1] = Animal(5, 5);
    animal_list2[2] = Animal(5, 5);

    std::cout << "복사생성자 테스트" << std::endl;

    Animal animal4 = Animal(animal1); // 복사 생성자 호출1
    Animal animal5(animal1); // 복사 생성자 호출2
    Animal animal6 = animal1; // 복사 생성자 호출3
    Animal animal7; // 위와는 완전히 다른 문장
    animal7 = animal1; // 걍 대입한거 // ????? 잘 복사 되는데?

    std::cout << "animal1 : " << std::endl;
    animal1.view_stat();
    std::cout << "animal4 : " << std::endl;
    animal4.view_stat();
    std::cout << "animal5 : " << std::endl;
    animal5.view_stat();
    std::cout << "animal6 : " << std::endl;
    animal6.view_stat();
    std::cout << "animal7 : " << std::endl;
    animal7.view_stat();

    animal1.increase_food(999);
    std::cout << std::endl << std::endl << std::endl;


    std::cout << "animal1 : " << std::endl;
    animal1.view_stat();
    std::cout << "animal4 : " << std::endl;
    animal4.view_stat();
    std::cout << "animal5 : " << std::endl;
    animal5.view_stat();
    std::cout << "animal6 : " << std::endl;
    animal6.view_stat();
    std::cout << "animal7 : " << std::endl;
    animal7.view_stat();
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

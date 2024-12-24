#include <windows.h>
#include <iostream>
#include <string>
#include <filesystem>
#include "json.hpp"
#include <fstream>

namespace fs = std::filesystem;
using json = nlohmann::json;

// std::string -> std::wstring 변환
std::wstring StringToWString(const std::string& str) {
    // ANSI 문자열을 wchar_t로 변환
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0) - 1;
    std::wstring wstr(size_needed, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size_needed);
    return wstr;
}

// std::wstring -> std::string 변환
std::string WStringToString(const std::wstring& wstr) {
    // wchar_t 문자열을 UTF-8로 변환
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL) - 1;
    std::string str(size_needed, '\0');
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], size_needed, NULL, NULL);
    return str;
}

std::string ANSIToUTF8(const std::string& ansiStr) {
    // ANSI 문자열을 UTF-8로 변환
    int size_needed = MultiByteToWideChar(CP_ACP, 0, ansiStr.c_str(), -1, NULL, 0) - 1; // 
    std::wstring wstr(size_needed, L'\0');
    MultiByteToWideChar(CP_ACP, 0, ansiStr.c_str(), -1, &wstr[0], size_needed);

    // wchar_t를 UTF-8로 변환
    size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], -1, NULL, 0, NULL, NULL) - 1;
    std::string utf8Str(size_needed, '\0');
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], -1, &utf8Str[0], size_needed, NULL, NULL);

    return utf8Str;
}

std::string UTF8ToANSI(const std::string& utf8Str) {
    // UTF-8 문자열을 wchar_t로 변환
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, NULL, 0) - 1;
    std::wstring wstr(size_needed, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, &wstr[0], size_needed);

    // wchar_t를 ANSI로 변환
    size_needed = WideCharToMultiByte(CP_ACP, 0, &wstr[0], -1, NULL, 0, NULL, NULL) - 1;
    std::string ansiStr(size_needed, '\0');
    WideCharToMultiByte(CP_ACP, 0, &wstr[0], -1, &ansiStr[0], size_needed, NULL, NULL);

    return ansiStr;
}

std::wstring ANSIToWString(const std::string& ansiStr) {
    // ANSI 문자열을 UTF-16로 변환
    int size_needed = MultiByteToWideChar(CP_ACP, 0, ansiStr.c_str(), -1, NULL, 0) - 1; // 
    std::wstring wstr(size_needed, L'\0');
    MultiByteToWideChar(CP_ACP, 0, ansiStr.c_str(), -1, &wstr[0], size_needed);
    return wstr;
}

std::string WStringToANSI(const std::wstring& wstr) {
    // wchar_t를 ANSI로 변환
    int size_needed = WideCharToMultiByte(CP_ACP, 0, &wstr[0], -1, NULL, 0, NULL, NULL) - 1;
    std::string ansiStr(size_needed, '\0');
    WideCharToMultiByte(CP_ACP, 0, &wstr[0], -1, &ansiStr[0], size_needed, NULL, NULL);
    return ansiStr;
}



int main() {
    std::string str2 = u8"Hello";
    std::cout << "UTF8 test length: " << str2.length() << std::endl;

    // std::string -> std::wstring
    std::string str = "Hello, World! 안녕하세요";
    //std::string str = "Hello";
    std::cout << "ANSI length: " << str.length() << std::endl;
    str = ANSIToUTF8(str);
    std::cout << "UTF8 length: " << str.length() << std::endl;
    std::wstring wstr = StringToWString(str);
    std::cout << "UTF16 length: " << wstr.length() << std::endl;
    //std::wcout << L"std::wstring: " << wstr << std::endl;

    // std::wstring -> std::string
    std::string convertedStr = WStringToString(wstr);
    std::cout << "UTF8 length: " << convertedStr.length() << std::endl;
    convertedStr = UTF8ToANSI(convertedStr);
    std::cout << "ANSI length: " << convertedStr.length() << std::endl;
    std::cout << "std::string: " << convertedStr << std::endl;



    try {

    }
    catch (const std::runtime_error& e) {
        // runtime_error 예외 처리
        std::cerr << "Caught a runtime_error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        // 모든 표준 예외 처리 (fallback)
        std::cerr << "Caught a standard exception: " << e.what() << std::endl;
    }
    catch (...) {
        // 알 수 없는 예외 처리
        std::cerr << "Caught an unknown exception!" << std::endl;
    }


    std::cout << "--------------------" << std::endl;
    std::wstring wstr123 = L"한글";
    std::string ansi_str = WStringToANSI(wstr123);
    std::cout << ansi_str << std::endl;
    wstr123 = ANSIToWString(ansi_str);
    //MessageBox(NULL, wstr123.c_str(), L"msg box", MB_OK);


    json data1 = u8"test한글";
    std::ofstream o("./test.json", std::ios::out);
    o << data1; //.dump(2);
    o.close();


    std::ifstream i("./test.json", std::ios::in);
    json data;
    i >> data;
    i.close();

    std::string jstr = data.get<std::string>();
    std::cout << jstr << std::endl;


    fs::path p = "한글?";
    std::string pstr = p.string();
    std::cout << pstr << std::endl;
    //MessageBox(NULL, p.wstring().c_str(), L"msg box", MB_OK);


    fs::path ppp = fs::current_path() / "ddd";
    ppp.append("aaa");
    std::cout << ppp << std::endl;

    return 0;
}

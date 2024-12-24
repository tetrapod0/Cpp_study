#include "pch.h"
#include "tool.h"

namespace tool {
    std::wstring UTF8ToUTF16(const std::string& str) {
        // UTF-8 문자열을 wchar_t로 변환
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0) - 1;
        std::wstring wstr(size_needed, L'\0');
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size_needed);
        return wstr;
    }

    std::string UTF16ToUTF8(const std::wstring& wstr) {
        // wchar_t 문자열을 UTF-8로 변환
        int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL) - 1;
        std::string str(size_needed, '\0');
        WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], size_needed, NULL, NULL);
        return str;
    }

    std::string ANSIToUTF8(const std::string& ansiStr) {
        // ANSI 문자열을 UTF-8로 변환
        int size_needed = MultiByteToWideChar(CP_ACP, 0, ansiStr.c_str(), -1, NULL, 0) - 1;
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

    std::wstring ANSIToUTF16(const std::string& ansiStr) {
        // ANSI 문자열을 UTF-16로 변환
        int size_needed = MultiByteToWideChar(CP_ACP, 0, ansiStr.c_str(), -1, NULL, 0) - 1; // 
        std::wstring wstr(size_needed, L'\0');
        MultiByteToWideChar(CP_ACP, 0, ansiStr.c_str(), -1, &wstr[0], size_needed);
        return wstr;
    }

    std::string UTF16ToANSI(const std::wstring& wstr) {
        // wchar_t를 ANSI로 변환
        int size_needed = WideCharToMultiByte(CP_ACP, 0, &wstr[0], -1, NULL, 0, NULL, NULL) - 1;
        std::string ansiStr(size_needed, '\0');
        WideCharToMultiByte(CP_ACP, 0, &wstr[0], -1, &ansiStr[0], size_needed, NULL, NULL);
        return ansiStr;
    }
}

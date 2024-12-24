#pragma once

#include <windows.h>
#include <string>

namespace tool {
    std::wstring UTF8ToUTF16(const std::string& str);
    std::string UTF16ToUTF8(const std::wstring& wstr);
    std::string ANSIToUTF8(const std::string& ansiStr);
    std::string UTF8ToANSI(const std::string& utf8Str);
    std::wstring ANSIToUTF16(const std::string& ansiStr);
    std::string UTF16ToANSI(const std::wstring& wstr);
}

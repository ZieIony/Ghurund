#include "pch.h"
#include "CppUnitTest.h"

#include "core/string/String.h"

#include <format>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace Ghurund::Core;

inline size_t find(const std::wstring& self, const std::wstring& str, size_t start = 0) {
    size_t strSize = str.size();
    for (size_t i = start; i <= self.size() - strSize; i++) {
        if (memcmp(&self[i], &str[0], strSize * sizeof(wchar_t)) == 0)
            return i;
    }
    return self.size();
}

inline Ghurund::Core::List<std::wstring> split(const std::wstring& self, const std::wstring& splitStr) {
    Ghurund::Core::List<std::wstring> list;
    size_t index = 0;
    size_t size = self.length();
    while (true) {
        size_t index2 = find(self, splitStr, index);
        if (index2 == size) {
            list.add(self.substr(index, size - index));
            return list;
        }
        list.add(self.substr(index, index2 - index));
        index = index2 + splitStr.length();
        if (index == size)
            return list;
    }
}

inline Array<std::wstring> split2(const std::wstring& self, const std::wstring& splitStr) {
    List<std::wstring> list;
    size_t index = 0;
    size_t strSize = splitStr.length();
    while (index < self.length()) {
        size_t nextIndex = find(self, splitStr, index);
        if (nextIndex == index) {
        } else if (nextIndex == self.size()) {
            list.add(self.substr(index, self.size() - index - 1));
            break;
        } else {
            list.add(self.substr(index, nextIndex - index));
        }
        index = nextIndex + strSize;
    }
    return list;
}

namespace PerformanceTest::Core {
    TEST_CLASS(StringTest) {
public:
    TEST_METHOD(split) {
        Timer timer;
        Ghurund::Core::WString ghString = L"dasfas8dasfas8fdsgfsdg8fdhfgbcv8sdewr8wedsfsdgds8fgdfghfbdfv8dsfserews8fdscvdsdv8dfgfregtr8hgfcvbdfvsde8ffsdfewsrtsetg8sdvxvdx8gffrghdrgtd8fdvxfvgdfgd8fgdfvf8";
        timer.tick();
        for (size_t i = 0; i < 1000; i++) {
            auto list = ghString.split(L"8");
        }
        timer.tick();
        uint64_t ghTime = timer.FrameTimeMs;
        
        std::wstring stdString = L"dasfas8dasfas8fdsgfsdg8fdhfgbcv8sdewr8wedsfsdgds8fgdfghfbdfv8dsfserews8fdscvdsdv8dfgfregtr8hgfcvbdfvsde8ffsdfewsrtsetg8sdvxvdx8gffrghdrgtd8fdvxfvgdfgd8fgdfvf8";
        timer.tick();
        for (size_t i = 0; i < 1000; i++) {
            auto list = ::split(stdString, L"8");
        }
        timer.tick();
        uint64_t stdTime = timer.FrameTimeMs;

        timer.tick();
        for (size_t i = 0; i < 1000; i++) {
            auto list = split2(stdString, L"8");
        }
        timer.tick();
        uint64_t mixedTime = timer.FrameTimeMs;

        Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(std::format(_T("Splitting time: Ghurund::Core::WString: {}ms, std::wstring: {}ms, mixed: {}ms."), ghTime, stdTime, mixedTime).c_str());
    }
    };
}


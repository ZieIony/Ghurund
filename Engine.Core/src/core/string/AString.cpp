#include "AString.h"

#include <Windows.h>

namespace Ghurund {
    Array<AString> AString::split(const char* d) const {
        List<AString> list;
        size_t index = 0;
        size_t strSize = strlen(d);
        while (index<Length) {
            size_t nextIndex = find(d, index);
            if (nextIndex == index) {
            } else if (nextIndex == size) {
                AString str = substring(index, size - index - 1);
                list.add(str);
                break;
            } else {
                AString str = substring(index, nextIndex - index);
                list.add(str);
            }
            index = nextIndex + strSize;
        }
        return list;
    }

    std::strong_ordering AString::operator<=>(const AString& string) const {
        int order = lstrcmpA(v, string.Data);
        if (order < 0) {
            return std::strong_ordering::less;
        } else if (order > 0) {
            return std::strong_ordering::greater;
        } else {
            return std::strong_ordering::equal;
        }
    }
}
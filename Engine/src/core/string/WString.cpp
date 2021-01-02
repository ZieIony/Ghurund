#include "WString.h"

namespace Ghurund {
    Array<WString> WString::split(const wchar_t* d) const {
        List<WString> list;
        size_t index = 0;
        size_t strSize = wcslen(d);
        while (index < Length) {
            size_t nextIndex = find(d, index);
            if (nextIndex == index) {
            } else if (nextIndex == size) {
                WString str = substring(index, size - index - 1);
                list.add(str);
                break;
            } else {
                WString str = substring(index, nextIndex - index);
                list.add(str);
            }
            index = nextIndex + strSize;
        }
        return list;
    }

}
#include "WString.h"

namespace Ghurund {
    void WString::add(const char e) {
        if (size + 1>capacity)
            resize(capacity + initial);

        char c[2];
        c[0] = e;
        c[1] = '\0';
        wchar_t retChar[2];
        size_t retVal;
        mbstowcs_s(&retVal, retChar, 1, c, 1);

        v[size - 1] = retChar[0];
        size++;
        v[size - 1] = 0;
        computeHash();
    }

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
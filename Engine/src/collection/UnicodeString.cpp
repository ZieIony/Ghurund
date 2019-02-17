#include "UnicodeString.h"

namespace Ghurund {
    void UnicodeString::add(const char e) {
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

    List<UnicodeString> UnicodeString::split(const wchar_t* d) const {
        List<UnicodeString> list;
        size_t index = 0;
        size_t strSize = wcslen(d);
        while (index < Length) {
            size_t nextIndex = find(d, index);
            if (nextIndex == index) {
            } else if (nextIndex == size) {
                UnicodeString str = subString(index, size - index - 1);
                list.add(str);
                break;
            } else {
                UnicodeString str = subString(index, nextIndex - index);
                list.add(str);
            }
            index = nextIndex + strSize;
        }
        return list;
    }

}
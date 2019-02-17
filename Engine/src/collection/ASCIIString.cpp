#include "ASCIIString.h"

namespace Ghurund {

    void ASCIIString::add(const wchar_t e) {
        if (size + 1>capacity)
            resize(capacity + initial);

        wchar_t c[2];
        c[0] = e;
        c[1] = '\0';
        char retChar[2];
        size_t retVal;
        wcstombs_s(&retVal, retChar, 1, c, 1);

        v[size - 1] = retChar[0];
        size++;
        v[size - 1] = 0;
        computeHash();
    }

    List<ASCIIString> ASCIIString::split(const char* d) const {
        List<ASCIIString> list;
        size_t index = 0;
        size_t strSize = strlen(d);
        while (index<Length) {
            size_t nextIndex = find(d, index);
            if (nextIndex == index) {
            } else if (nextIndex == size) {
                ASCIIString str = subString(index, size - index - 1);
                list.add(str);
                break;
            } else {
                ASCIIString str = subString(index, nextIndex - index);
                list.add(str);
            }
            index = nextIndex + strSize;
        }
        return list;
    }
}
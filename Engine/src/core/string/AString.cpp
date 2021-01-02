#include "AString.h"

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
}
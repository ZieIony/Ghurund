#pragma once

#include "GenericStringView.h"

namespace Ghurund {
    class AStringView:public GenericStringView<char> {
    public:
        using GenericStringView<char>::GenericStringView;

        inline AStringView substring(size_t start) const {
            return AStringView(v + start);
        }

        inline AStringView substring(size_t start, size_t length) const {
            return AStringView(v + start, length);
        }

        inline AStringView trim() const {
            size_t i, j, l = Length;
            for (i = 0; i < l && isspace(v[i]); i++);
            for (j = l; j > i && isspace(v[j]); j--);
            return AStringView(v + i, j - i);
        }
    };
}
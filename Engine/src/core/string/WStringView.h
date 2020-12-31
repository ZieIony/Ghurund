#pragma once

#include "GenericStringView.h"

namespace Ghurund {
    class WStringView:public GenericStringView<wchar_t> {
    public:
        using GenericStringView<wchar_t>::GenericStringView;

        inline WStringView substring(size_t start) const {
            return WStringView(v + start);
        }

        inline WStringView substring(size_t start, size_t length) const {
            return WStringView(v + start, length);
        }

        inline WStringView trim() const {
            size_t i, j, l = Length;
            for (i = 0; i < l && isspace(v[i]); i++);
            for (j = l; j > i && isspace(v[j]); j--);
            return WStringView(v + i, j - i);
        }
    };
}
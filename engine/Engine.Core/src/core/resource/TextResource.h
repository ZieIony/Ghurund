#pragma once

#include "Resource.h"

namespace Ghurund::Core {
    class TextResource:public Resource {
    private:
        AString text;

    public:
        inline AString& getText() {
            return text;
        }

        inline void setText(const AString& text) {
            this->text = text;
        }

        __declspec(property(get = getText, put = setText)) AString& Text;
    };
}
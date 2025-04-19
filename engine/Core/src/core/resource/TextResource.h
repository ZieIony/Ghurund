#pragma once

#include "Resource.h"

namespace Ghurund::Core {
    class TextResource:public Resource {
    private:
        AString text;

    public:
        virtual bool isValid() const override {
            return true;
        }

        inline AString& getText() {
            return text;
        }

        inline void setText(const AString& text) {
            this->text = text;
        }

        __declspec(property(get = getText, put = setText)) AString& Text;
    };
}
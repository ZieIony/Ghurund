#pragma once

#include "collection/String.h"

namespace Ghurund {
    class NamedObject {
    private:
        UnicodeString name;

    public:
        virtual ~NamedObject() = default;

        virtual void setName(const UnicodeString &name) {
            this->name = name;
        }
        
        virtual UnicodeString &getName() {
            return name;
        }

        __declspec(property(get = getName, put = setName)) UnicodeString &Name;
    };
}
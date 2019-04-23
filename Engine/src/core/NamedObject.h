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
        
        virtual const UnicodeString &getName() const {
            return name;
        }

        __declspec(property(get = getName, put = setName)) UnicodeString &Name;
    };
}
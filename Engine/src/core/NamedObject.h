#pragma once

#include "collection/String.h"

namespace Ghurund {
    class NamedObject {
    private:
        String name;

    public:
        virtual ~NamedObject() = default;

        virtual void setName(const String &name) {
            this->name = name;
        }
        
        virtual String &getName() {
            return name;
        }

        __declspec(property(get = getName, put = setName)) String &Name;
    };
}
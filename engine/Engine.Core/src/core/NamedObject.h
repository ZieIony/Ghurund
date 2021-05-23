#pragma once

#include "core/string/String.h"

namespace Ghurund {
    class NamedObject {
    private:
        WString name;

    public:
        virtual ~NamedObject() = 0 {};

        virtual void setName(const WString& name) {
            this->name = name;
        }

        virtual const WString& getName() const {
            return name;
        }

        __declspec(property(get = getName, put = setName)) const WString& Name;
    };
}
#pragma once

#include "core/string/WString.h"

namespace Ghurund {
    class NamedObject {
    private:
        WString name;

    public:
        virtual ~NamedObject() = default;

        virtual void setName(const WString& name) {
            this->name = name;
        }

        virtual const WString& getName() const {
            return name;
        }

        __declspec(property(get = getName, put = setName)) const WString& Name;
    };
}
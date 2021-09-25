#pragma once

#include "core/NamedObject.h"

#include <functional>

namespace Ghurund::Core {
    class Type;

    class BaseProperty:public NamedObject<char> {
    private:
        static const inline char* DEFAULT_GROUP = "default";

        const Type& type;
        const char* group;

    public:
        BaseProperty(
            const Type& type,
            const AString& name,
            const char* group = DEFAULT_GROUP
        ):NamedObject<char>(name), type(type), group(group) {}

        virtual ~BaseProperty() = 0 {}

        inline const Type& getType() const {
            return type;
        }

        __declspec(property(get = getType)) const Type& Type;
    };
}
#pragma once

#include "core/reflection/Type.h"

namespace Ghurund {
    class Object {
    public:
        virtual ~Object() {}   // gives a common destructor to all deriving classes

        virtual const Type &getType() const = 0;

        __declspec(property(get = getType)) Type &Type;
    };
}
#pragma once

#include "core/string/String.h"

namespace Ghurund::Core {
    class Type;

    class Object {
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        virtual ~Object() = 0 {}   // gives a common destructor to all deriving classes

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const {
            return TYPE;
        }

        __declspec(property(get = getType)) const Type &Type;

        virtual Object* clone() const {
            return nullptr;
        }

        virtual String toString() const;
    };
}
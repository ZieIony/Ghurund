#pragma once

#include "core/reflection/TypeBuilder.h"

namespace Ghurund {
    class Object {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Object);

    public:
        virtual ~Object() {}   // gives a common destructor to all deriving classes

        inline static const Ghurund::Type& TYPE = TypeBuilder<Object>(NAMESPACE_NAME, CLASS_NAME).withModifiers(TypeModifier::ABSTRACT);

        virtual const Ghurund::Type& getType() const {
            return TYPE;
        }

        __declspec(property(get = getType)) Type &Type;
    };
}
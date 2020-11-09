#pragma once

#include "core/reflection/TypeBuilder.h"

namespace Ghurund {
    class Object {
    private:
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Object))
                .withModifiers(TypeModifier::ABSTRACT);

            return TYPE;
        }

    public:
        virtual ~Object() {}   // gives a common destructor to all deriving classes

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const {
            return TYPE;
        }

        __declspec(property(get = getType)) const Type &Type;
    };
}
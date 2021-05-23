#pragma once

namespace Ghurund {
    class Type;

    class Object {
    protected:
        static const Ghurund::Type& GET_TYPE();

    public:
        virtual ~Object() = 0 {}   // gives a common destructor to all deriving classes

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const {
            return TYPE;
        }

        __declspec(property(get = getType)) const Type &Type;
    };
}
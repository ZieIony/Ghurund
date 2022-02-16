#pragma once

#include "core/string/String.h"
#include "core/Lazy.h"

namespace Ghurund::Core {
    class Type;

    class Object {
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const {
            return GET_TYPE();
        }

    public:
        virtual ~Object() = 0 {}   // gives a common destructor to all deriving classes

        static const Ghurund::Core::Type& GET_TYPE();

        inline const Ghurund::Core::Type& getType() const {
            return getTypeImpl();
        }

        __declspec(property(get = getType)) const Type& Type;

        /**
         * @brief Constructs a deep copy of this object.
         * @return Can be null if cloning is not supported.
        */
        virtual Object* clone() const {
            return nullptr;
        }

        virtual String toString() const;
    };

    /**
     * @brief Clones an object and casts it back to its type.
     * @tparam T
     * @param obj An object to clone.
     * @return A clone of the passed object. Can be null.
    */
    template<class T>
    inline T* clone(T& obj) {
        return (T*)obj.clone();
    }

    template<>
    String toString(const Object& obj);
}
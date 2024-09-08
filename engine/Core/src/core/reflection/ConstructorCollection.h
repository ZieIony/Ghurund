#pragma once

#include "Constructor.h"
#include "core/collection/Array.h"

namespace Ghurund::Core {
    class Type;

    inline bool operator==(const std::reference_wrapper<const Type>& obj, const std::reference_wrapper<const Type>& other) {
        return &obj.get() == &other.get();
    }

    class ConstructorCollection:public Array<std::reference_wrapper<const BaseConstructor>> {
    public:
        ConstructorCollection() {}

        ConstructorCollection(const ArrayCollection<std::reference_wrapper<const BaseConstructor>>& list):Array<std::reference_wrapper<const BaseConstructor>>(list) {}

        template<typename... Args>
        const BaseConstructor* findBySignature() const {
            Array<std::reference_wrapper<const Type>> parameters = { getType<Args>()... };
            for (const BaseConstructor& constructor : *this) {
                if (constructor.Parameters == parameters)
                    return &constructor;
            }
            return nullptr;
        }
    };
}
#pragma once

#include "Enum_templateDeclaration.h"

#include "core/object/Noncopyable.h"
#include "core/reflection/Type.h"
#include "core/string/String.h"

namespace Ghurund::Core {

    template<class Type, class Type2>
    class EnumCollection:public Noncopyable {
    private:
        mutable List<std::reference_wrapper<const Type2>> values;

        inline void add(const std::reference_wrapper<const Type2> value) const {
            values.add(value);
        }

    public:
        using iterator = List<std::reference_wrapper<const Type2>>::iterator;
        using const_iterator = List<std::reference_wrapper<const Type2>>::const_iterator;

        friend class Enum<Type, Type2>;
        friend typename Type2;

        inline const Type2& operator[](const size_t index) const {
            return values.get(index);
        }

        inline size_t getSize() const {
            return values.Size;
        }

        __declspec(property(get = getSize)) size_t Size;

        inline iterator begin() {
            return values.begin();
        }

        inline const_iterator begin() const {
            return ((const List<std::reference_wrapper<const Type2>>&)values).begin();
        }

        inline iterator end() {
            return values.end();
        }

        inline const_iterator end() const {
            return ((const List<std::reference_wrapper<const Type2>>&)values).end();
        }
    };
}

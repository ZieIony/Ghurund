#pragma once

#include "Common.h"

#include "core/allocation/Allocator.h"

namespace Ghurund::Core {
    __interface BaseConstructor {};

    template <class T>
    class BaseTypeConstructor:public BaseConstructor {};

    template <class T, typename... ArgsT>
    class Constructor:public BaseTypeConstructor<T> {
    public:
        T* invoke(ArgsT... args) const {
            return ghnew T(args...);
        }

        T* invoke(Allocator<size_t>& allocator, ArgsT... args) const {
            return new (allocator)T(args...);
        }
    };
}
#pragma once

#include <functional>

namespace Ghurund::Core {
    template<typename T>
    class Lazy {
    private:
        typedef T(*EvaluateFunction)();
        EvaluateFunction func;

        Lazy(const Lazy& other) = delete;
        Lazy(Lazy&& other) = delete;

        inline T getValue() {
            static T val = func();
            return val;
        }

        inline const T getValue() const {
            static T val = func();
            return val;
        }

    public:
        Lazy(EvaluateFunction func):func(func) {}

        operator T() {
            return getValue();
        }

        operator const T() const {
            return getValue();
        }
    };

}
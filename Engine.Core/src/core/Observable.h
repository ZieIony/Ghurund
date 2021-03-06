#pragma once

#include "PropertyHandler.h"
#include "core/collection/List.h"

namespace Ghurund {
    template<class Type>
    class Observable {
    private:
        List<ObservableHandler<Type>> listeners;
        Type value;

    public:
        Observable() {}

        Observable(Type& value):value(value) {}

        inline void add(std::function<void(const Type& args)> lambda) {
            listeners.add(lambda);
        }

        inline void add(const ObservableHandler<Type>& listener) {
            listeners.add(listener);
        }

        inline void remove(const ObservableHandler<Type>& listener) {
            listeners.remove(listener);
        }

        void clear() {
            listeners.clear();
        }

        inline operator Type&() {
            return value;
        }

        inline operator const Type&() const {
            return value;
        }

        inline Type& operator=(const Type& value) {
            this->value = value;
            for (auto& listener : listeners)
                listener(value);
        }
    };
}
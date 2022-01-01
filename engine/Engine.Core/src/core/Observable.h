#pragma once

#include "ObservableHandler.h"
#include "core/collection/List.h"

#include <functional>

namespace Ghurund::Core {
    template<class Type>
    class Observable {
    private:
        List<ObservableHandler<Type>> listeners;
        Type value;

    public:
        Observable() {}

        Observable(const Type& value):value(value) {}

        inline void add(std::function<void(const Type& args)> lambda) {
            listeners.add(lambda);
            lambda(value);
        }

        inline Observable<Type>& operator+=(const std::function<void(const Type& args)>& lambda) {
            listeners.add(lambda);
            lambda(value);
            return *this;
        }

        inline void add(const ObservableHandler<Type>& listener) {
            listeners.add(listener);
            listener(value);
        }

        inline Observable<Type>& operator+=(const ObservableHandler<Type>& listener) {
            listeners.add(listener);
            listener(value);
            return *this;
        }

        inline void remove(const ObservableHandler<Type>& listener) {
            listeners.remove(listener);
        }

        inline Observable<Type>& operator-=(const ObservableHandler<Type>& listener) {
            listeners.remove(listener);
            return *this;
        }

        void clear() {
            listeners.clear();
        }

        inline operator const Type&() {
            return value;
        }

        inline operator const Type&() const {
            return value;
        }

        inline const Type& getValue() {
            return value;
        }

        __declspec(property(get = getValue)) const Type& Value;

        inline Type& operator=(const Type& value) {
            if (this->value != value) {
                this->value = value;
                for (auto& listener : listeners)
                    listener(value);
            }
            return this->value;
        }

        /*inline Observable<Type>& operator=(const Observable<Type>& other) {
            //other.add()
            return *this;
        }*/
    };
}
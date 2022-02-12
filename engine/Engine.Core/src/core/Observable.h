#pragma once

#include "core/Object.h"
#include "ObservableHandler.h"
#include "core/collection/List.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

#include <functional>

namespace Ghurund::Core {
    template<class T>
    class Observable:public Object {
    private:
        List<ObservableHandler<T>> listeners;
        T value;
        ObservableHandler<T> chainHandler = [](const T&) {};
        Observable<T>* sourceObservable = nullptr;

    protected:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = Constructor<Observable<T>>();
            static const auto CONSTRUCTOR2 = Constructor<Observable<T>, const T&>();
            static const auto VALUE_PROPERTY = Property<Observable<T>, const T&>("Value", &getValue, &setValue);
        
            static const Ghurund::Core::Type TYPE = TypeBuilder<Observable<T>>(Ghurund::Core::NAMESPACE_NAME, GH_STRINGIFY(Observable))
                .withConstructor(CONSTRUCTOR)
                .withConstructor(CONSTRUCTOR2)
                .withSupertype(__super::GET_TYPE())
                .withProperty(VALUE_PROPERTY)
                .withTemplateParams({ Ghurund::Core::getType<T>() });

            return TYPE;
        }

    public:
        Observable():value(T()) {}

        Observable(const T& value):value(value) {}

        ~Observable() {
            if (sourceObservable)
                sourceObservable->remove(chainHandler);
        }

        inline void add(std::function<void(const T& args)> lambda) {
            listeners.add(lambda);
            lambda(value);
        }

        inline Observable<T>& operator+=(const std::function<void(const T& args)>& lambda) {
            listeners.add(lambda);
            lambda(value);
            return *this;
        }

        inline void add(const ObservableHandler<T>& handler) {
            listeners.add(handler);
            handler(value);
        }

        inline Observable<T>& operator+=(const ObservableHandler<T>& handler) {
            listeners.add(handler);
            handler(value);
            return *this;
        }

        inline void remove(const ObservableHandler<T>& listener) {
            listeners.remove(listener);
        }

        inline Observable<T>& operator-=(const ObservableHandler<T>& listener) {
            listeners.remove(listener);
            return *this;
        }

        void clear() {
            listeners.clear();
        }

        inline operator const T& () {
            return value;
        }

        inline operator const T& () const {
            return value;
        }

        inline T& getValue() {
            return value;
        }

        inline void setValue(const T& val) {
            if (this->value != value) {
                this->value = value;
                for (auto& listener : listeners)
                    listener(value);
            }
        }

        __declspec(property(get = getValue, put = setValue)) T& Value;

        inline T& operator=(const T& value) {
            Value = value;
            return this->value;
        }

        inline Observable<T>& operator=(nullptr_t) {
            if (sourceObservable) {
                sourceObservable->remove(chainHandler);
                sourceObservable = nullptr;
            }
            return *this;
        }

        inline Observable<T>& operator=(Observable<T>& other) {
            if (sourceObservable)
                sourceObservable->remove(chainHandler);
            sourceObservable = &other;
            chainHandler = ObservableHandler<T>([&](const T& val) {
                this->operator=(val);
            });
            other.add(chainHandler);
            return *this;
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const {
            return TYPE;
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
   };
}
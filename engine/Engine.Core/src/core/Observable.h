#pragma once

#include "ObservableHandler.h"
#include "core/Object.h"
#include "core/SharedPointer.h"
#include "core/collection/List.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Method.h"
#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

#include <functional>

namespace Ghurund::Core {
    template<class T>
    class Observable:public Object {
    private:
        List<SharedPointer<ObservableHandler<T>>> listeners;
        T value;

    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const {
            return GET_TYPE();
        }

    public:
        Observable():value(T()) {}

        Observable(const T& value):value(value) {}

        Observable(const Observable<T>& other) = delete;

        Observable(Observable<T>&& other) = delete;

        ~Observable() {
            for (auto& handler : listeners)
                handler->Owner = nullptr;
        }

        inline void add(std::function<void(const T& args)> lambda) {
            listeners.add(ghnew ObservableHandler(lambda));
            lambda(value);
        }

        inline Observable<T>& operator+=(const std::function<void(const T& args)>& lambda) {
            listeners.add(ghnew ObservableHandler(lambda));
            lambda(value);
            return *this;
        }

        inline void add(SharedPointer<ObservableHandler<T>> handler) {
            listeners.add(handler);
            handler->Owner = this;
            handler->invoke(value);
        }

        inline Observable<T>& operator+=(SharedPointer<ObservableHandler<T>> handler) {
            listeners.add(handler);
            handler->Owner = this;
            handler(value);
            return *this;
        }

        inline void remove(ObservableHandler<T>& listener) {
            listeners.remove(&listener);
            listener.Owner = nullptr;
        }

        inline Observable<T>& operator-=(ObservableHandler<T>& listener) {
            listeners.remove(&listener);
            listener.Owner = nullptr;
            return *this;
        }

        void clear() {
            for (auto& handler : listeners)
                handler->Owner = nullptr;
            listeners.clear();
        }

        inline operator const T& () const {
            return value;
        }

        inline const T& getValue() const {
            return value;
        }

        inline void setValue(const T& value) {
            if (this->value != value) {
                this->value = value;
                for (auto& listener : listeners)
                    listener->invoke(value);
            }
        }

        __declspec(property(get = getValue, put = setValue)) T& Value;

        inline T& operator=(const T& value) {
            Value = value;
            return this->value;
        }

        static const Ghurund::Core::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = Constructor<Observable<T>>();
            static const auto CONSTRUCTOR2 = Constructor<Observable<T>, const T&>();
            static const auto VALUE_PROPERTY = Property<Observable<T>, const T&>("Value", &getValue, &setValue);
            static const auto ADD_METHOD = Method<Observable<T>, void, SharedPointer<ObservableHandler<T>>>("add", (void (Observable<T>::*)(SharedPointer<ObservableHandler<T>>)) & add);

            static const Ghurund::Core::Type TYPE = TypeBuilder<Observable<T>>(Ghurund::Core::NAMESPACE_NAME, GH_STRINGIFY(Observable))
                .withConstructor(CONSTRUCTOR)
                .withConstructor(CONSTRUCTOR2)
                .withSupertype(__super::GET_TYPE())
                .withProperty(VALUE_PROPERTY)
                .withMethod(ADD_METHOD)
                .withTemplateParams<T>();

            return TYPE;
        }
    };
}
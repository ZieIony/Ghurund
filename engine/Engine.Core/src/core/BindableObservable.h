#pragma once

#include "Observable.h"

namespace Ghurund::Core {
    template<typename T>
    class BindableObservable:public Observable<T> {
    private:
        SharedPointer<ObservableHandler<T>> chainHandler;

    protected:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = Constructor<BindableObservable<T>>();
            static const auto CONSTRUCTOR2 = Constructor<BindableObservable<T>, const T&>();

            static const Ghurund::Core::Type TYPE = TypeBuilder<BindableObservable<T>>(Ghurund::Core::NAMESPACE_NAME, GH_STRINGIFY(BindableObservable))
                .withConstructor(CONSTRUCTOR)
                .withConstructor(CONSTRUCTOR2)
                .withSupertype(__super::GET_TYPE())
                .withTemplateParams<T>();

            return TYPE;
        }

    public:
        BindableObservable():Observable<T>(T()) {}

        BindableObservable(const T& value):Observable<T>(value) {}

        BindableObservable(const BindableObservable<T>& other) = delete;

        BindableObservable(BindableObservable<T>&& other) = delete;

        ~BindableObservable() {
            if (chainHandler != nullptr && chainHandler->Owner)
                chainHandler->Owner->remove(*chainHandler.get());
        }

        void bind(Observable<T>& observable) {
            if (chainHandler != nullptr && chainHandler->Owner)
                chainHandler->Owner->remove(*chainHandler.get());
            chainHandler.set(ghnew ObservableHandler<T>([&](const T& val) {
                Observable<T>::Value = val;
            }));
            observable.add(chainHandler);
        }

        void unbind() {
            if (chainHandler != nullptr && chainHandler->Owner)
                chainHandler->Owner->remove(*chainHandler.get());
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const {
            return TYPE;
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}
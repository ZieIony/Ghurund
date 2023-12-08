#pragma once

#include "core/Pointer.h"
#include "core/reflection/TypeBuilder.h"

#include <functional>

namespace Ghurund::Core {
    template<typename T>
    class Observable;

    template<class T>
    class ObservableHandler:public Pointer {
#pragma region reflection
protected:
    virtual const Ghurund::Core::Type& getTypeImpl() const override {
        return GET_TYPE();
    }

public:
    static const Ghurund::Core::Type& GET_TYPE() {
            static Ghurund::Core::Type type = TypeBuilder<ObservableHandler<T>>(Ghurund::Core::NAMESPACE_NAME, "ObservableHandler").withTemplateParams<T>();
            return type;
        }

    inline static const Ghurund::Core::Type& TYPE = ObservableHandler::GET_TYPE();
#pragma endregion

    private:
        std::function<void(const T& args)> lambda;
        Observable<T>* owner = nullptr;

    public:
        ObservableHandler() {}

        ObservableHandler(std::function<void(const T& args)> lambda) {
            this->lambda = lambda;
        }

        ObservableHandler(const ObservableHandler& handler) {
            lambda = handler.lambda;
        }

        ObservableHandler(ObservableHandler&& handler) noexcept {
            lambda = std::move(handler.lambda);
        }

        inline Observable<T>* getOwner() {
            return owner;
        }

        inline void setOwner(Observable<T>* owner) {
            this->owner = owner;
        }

        __declspec(property(get = getOwner, put = setOwner)) Observable<T>* Owner;

        inline void invoke(const T& args) const {
            lambda(args);
        }
    };

}
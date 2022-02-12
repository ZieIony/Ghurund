#pragma once

#include "Parameter.h"
#include "core/NamedObject.h"

#include <functional>

namespace Ghurund::Core {
    class Type;

    class BaseMethod:public NamedObject<char> {
    private:
        const Type& returnType;
        //List<Parameter> parameters;

    public:
        BaseMethod(const AString& name, const Type& returnType):NamedObject<char>(name), returnType(returnType) {}

        template<class T, typename ReturnT, typename... ArgsT>
        ReturnT invoke(T& obj, ArgsT... args);

        template<class T, typename... ArgsT>
        void invoke(T& obj, ArgsT... args);
    };

    template<class T, typename ReturnT, typename... ArgsT>
    class Method:public BaseMethod {
    private:
        std::function<ReturnT(T, ArgsT...)> func;

        ReturnT invokeImpl(T& obj, ArgsT... args) {
            return func(obj, args);
        }

    public:
        Method(const AString& name, const Type& returnType, std::function<ReturnT(T, ArgsT...)> func):BaseMethod(name, returnType), func(func) {}
    };

    template<class T, typename... ArgsT>
    class Method<T, void, ArgsT...>:public BaseMethod {
    private:
        std::function<void(T, ArgsT...)> func;

        void invokeImpl(T& obj, ArgsT... args) {
            func(obj, args);
        }

    public:
        Method(const AString& name, const Type& returnType, std::function<void(T, ArgsT...)> func):BaseMethod(name, returnType), func(func) {}
    };

    template<class T, typename ReturnT, typename... ArgsT>
    ReturnT BaseMethod::invoke(T& obj, ArgsT... args) {
        return ((Method<T, ReturnT, ArgsT...>*)this)->invokeImpl(*(T*)obj, args);
    }

    template<class T, typename... ArgsT>
    void BaseMethod::invoke(T& obj, ArgsT... args) {
        ((Method<T, void, ArgsT...>*)this)->invokeImpl(*(T*)obj, args);
    }
}
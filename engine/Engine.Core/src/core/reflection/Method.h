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
    };

    template<class T>
    class BaseTypeMethod:public BaseMethod {
    public:
        BaseTypeMethod(const AString& name, const Type& returnType):BaseMethod(name, returnType) {}
    };

    template<class T, typename ReturnT, typename... ArgsT>
    class Method:public BaseTypeMethod<T> {
    private:
        std::function<ReturnT(T, ArgsT...)> func;
    public:
        Method(const AString& name, const Type& returnType, std::function<ReturnT(T, ArgsT...)> func):BaseTypeMethod<T>(name, returnType), func(func) {}

        ReturnT invoke(T& obj, ArgsT... args) {
            return func(obj, args);
        }
    };

    template<class T, typename... ArgsT>
    class Method<T, void, ArgsT...>:public BaseTypeMethod<T> {
    private:
        std::function<void(T, ArgsT...)> func;
    public:
        Method(const AString& name, const Type& returnType, std::function<void(T, ArgsT...)> func):BaseTypeMethod<T>(name, returnType), func(func) {}

        void invoke(T& obj, ArgsT... args) {
            func(obj, args);
        }
    };
}
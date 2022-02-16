#pragma once

#include "core/NamedObject.h"
#include "core/collection/Array.h"
#include "core/Tuple.h"

#include <functional>

namespace Ghurund::Core {
    class Type;

    class BaseMethod:public NamedObject<char> {
    private:
        const Type& returnType;

    protected:
        const Array<std::reference_wrapper<const Type>> parameters;

        virtual void invokeRawInternal(void* obj, void* args, std::function<void(void*)> callback) const = 0;

    public:
        BaseMethod(const AString& name, const Type& returnType, const Array<std::reference_wrapper<const Type>> parameters)
            :NamedObject<char>(name), returnType(returnType), parameters(parameters) {}

        template<typename... ArgsT>
        void invokeRaw(void* obj, ArgsT&... args, std::function<void(void*)> callback = nullptr) const {
            auto tuple = Tuple(args...);
            invokeRawInternal(obj, (void*)&tuple, callback);
        }

        inline const Type& getReturnType() const {
            return returnType;
        }

        __declspec(property(get = getReturnType)) const Type& ReturnType;

        inline const Array<std::reference_wrapper<const Type>>& getParameters() const {
            return parameters;
        }

        __declspec(property(get = getParameters)) const Array<std::reference_wrapper<const Type>>& Parameters;
    };

    template<class T, typename ReturnT, typename... ArgsT>
    class Method:public BaseMethod {
    private:
        std::function<ReturnT(T, ArgsT...)> func;

        template <std::size_t... I>
        constexpr ReturnT callWithTuple(T& obj, Tuple<ArgsT...>&& t, std::index_sequence<I...>) const {
            return func(obj, get<I>(std::forward<Tuple<ArgsT...>>(t))...);
        }

        virtual void invokeRawInternal(void* obj, void* args, std::function<void(void*)> callback) const override {
            Tuple<ArgsT...>& t = *(Tuple<ArgsT...>*)args;
            auto indexSeq = std::make_index_sequence<std::tuple_size_v<std::tuple<ArgsT...>>>{};
            ReturnT result = callWithTuple(*(T*)obj, std::forward<Tuple<ArgsT...>>(t), indexSeq);
            if (callback)
                callback(&result);
        }

    public:
        Method(const AString& name, std::function<ReturnT(T, ArgsT...)> func)
            :BaseMethod(name, getType<ReturnT>(), { getType<ArgsT>()... }), func(func) {}

        void invoke(T& obj, ArgsT&&... args, std::function<void(ReturnT&)> callback = nullptr) const {
            ReturnT result = func(obj, std::forward(args)...);
            if (callback)
                callback(result);
        }
    };

    template<class T, typename... ArgsT>
    class Method<T, void, ArgsT...>:public BaseMethod {
    private:
        std::function<void(T&, ArgsT...)> func;

        template <std::size_t... I>
        constexpr void callWithTuple(T& obj, Tuple<ArgsT...>&& t, std::index_sequence<I...>) const {
            func(obj, get<I>(std::forward<Tuple<ArgsT...>>(t))...);
        }

        virtual void invokeRawInternal(void* obj, void* args, std::function<void(void*)> callback) const override {
            Tuple<ArgsT...>& t = *(Tuple<ArgsT...>*)args;
            auto indexSeq = std::make_index_sequence<std::tuple_size_v<std::tuple<ArgsT...>>>{};
            callWithTuple(*(T*)obj, std::forward<Tuple<ArgsT...>>(t), indexSeq);
        }

    public:
        Method(const AString& name, std::function<void(T&, ArgsT...)> func)
            :BaseMethod(name, getType<void>(), { getType<ArgsT>()... }), func(func) {}

        void invoke(T& obj, ArgsT&&... args) const {
            func(obj, std::forward(args)...);
        }
    };
}
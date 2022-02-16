#pragma once

#include "Common.h"
#include "TypeMember.h"
#include "core/allocation/Allocator.h"
#include "core/collection/Array.h"
#include "core/Tuple.h"
#include "core/Exceptions.h"
#include "core/logging/Formatter.h"

namespace Ghurund::Core {
    class Type;

    class BaseConstructor:public TypeMember {
    private:
        Array<std::reference_wrapper<const Type>> parameters;

        BaseConstructor(const BaseConstructor& other) = delete;
        BaseConstructor(BaseConstructor&& other) = delete;

    protected:
        virtual void* invokeRawInternal(void* args) const = 0;
        virtual void* invokeRawInternalWithAllocator(Allocator& allocator, void* args) const = 0;

    public:
        BaseConstructor(Array<std::reference_wrapper<const Type>> parameters):parameters(parameters) {}

        template<typename... ArgsT>
        void* invokeRaw(ArgsT&&... args) const {
            auto tuple = Tuple(args...);
            checkParameters<ArgsT...>(parameters);
            return invokeRawInternal((void*)&tuple);
        }

        template<>
        void* invokeRaw() const {
            Array<std::reference_wrapper<const Type>> currentParameters;
            if (currentParameters.Size != Parameters.Size)
                throw InvalidParamException(std::format("{} parameters expected, {} provided.\n", Parameters.Size, currentParameters.Size).c_str());
            return invokeRawInternal(nullptr);
        }

        template<typename... ArgsT>
        void* invokeRawWithAllocator(Allocator& allocator, ArgsT&&... args) const {
            auto tuple = std::make_tuple(args...);
            checkParameters<ArgsT...>(parameters);
            return invokeRawInternal(allocator, (void*)&tuple);
        }

        template<>
        void* invokeRawWithAllocator(Allocator& allocator) const {
            Array<std::reference_wrapper<const Type>> currentParameters;
            if (currentParameters.Size != Parameters.Size)
                throw InvalidParamException(std::format("{} parameters expected, {} provided.\n", Parameters.Size, currentParameters.Size).c_str());
            return invokeRawInternalWithAllocator(allocator, nullptr);
        }

        inline const Array<std::reference_wrapper<const Type>>& getParameters() const {
            return parameters;
        }

        __declspec(property(get = getParameters)) const Array<std::reference_wrapper<const Type>>& Parameters;
    };

    template <class T, typename... ArgsT>
    class Constructor:public BaseConstructor {
    protected:
        template <class TupleT, std::size_t... I>
        constexpr T* makeFromTuple(TupleT&& t, std::index_sequence<I...>) const {
            return ghnew T(get<I>(std::forward<TupleT>(t))...);
        }

        virtual void* invokeRawInternal(void* args) const override {
            Tuple<ArgsT...>& t = *(Tuple<ArgsT...>*)args;
            auto indexSeq = std::make_index_sequence<std::tuple_size_v<std::tuple<ArgsT...>>>{};
            return makeFromTuple(std::forward<Tuple<ArgsT...>>(t), indexSeq);
        }

        template <class AllocatorType, class TupleT, std::size_t... I>
        constexpr T* makeFromTupleWithAllocator(AllocatorType& allocator, TupleT&& t, std::index_sequence<I...>) const {
            return new (allocator) T(get<I>(std::forward<TupleT>(t))...);
        }

        virtual void* invokeRawInternalWithAllocator(Allocator& allocator, void* args) const override {
            Tuple<ArgsT...>& t = *(Tuple<ArgsT...>*)args;
            auto indexSeq = std::make_index_sequence<std::tuple_size_v<std::tuple<ArgsT...>>>{};
            return makeFromTupleWithAllocator(allocator, std::forward<Tuple<ArgsT...>>(t), indexSeq);
        }

    public:
        Constructor():BaseConstructor({ getType<ArgsT>()... }) {}

        T* invoke(ArgsT&&... args) const {
            return ghnew T(std::forward(args)...);
        }

        T* invokeWithAllocator(Allocator& allocator, ArgsT&&... args) const {
            return new (allocator)T(std::forward(args)...);
        }
    };


    template <class T>
    class Constructor<T>:public BaseConstructor {
    protected:
        virtual void* invokeRawInternal(void* args) const override {
            return ghnew T();
        }

        virtual void* invokeRawInternalWithAllocator(Allocator& allocator, void* args) const override {
            return new (allocator) T();
        }

    public:
        Constructor():BaseConstructor({}) {}

        T* invoke() const {
            return ghnew T();
        }

        T* invokeWithAllocator(Allocator& allocator) const {
            return new (allocator) T();
        }
    };
}
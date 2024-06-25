#pragma once

#include "core/Tuple.h"
#include "core/collection/Array.h"

#include <functional>

namespace Ghurund::Core {
    class Type;

    class BaseMethod {
    private:
        const Type& returnType;
        const AString name;

    protected:
        const Array<std::reference_wrapper<const Type>> parameters;

        virtual void invokeRawInternal(void* obj, void* args, std::function<void(void*)> callback) const = 0;

    public:
        BaseMethod(const AString& name, const Type& returnType, const Array<std::reference_wrapper<const Type>> parameters)
            :name(name), returnType(returnType), parameters(parameters) {}

        template<typename... ArgsT>
        void invokeRaw(void* obj, ArgsT&... args, std::function<void(void*)> callback = nullptr) const {
            auto tuple = Tuple(args...);
            invokeRawInternal(obj, (void*)&tuple, callback);
        }

        inline AString getName() const {
            return name;
        }

        __declspec(property(get = getName)) AString Name;

        inline const Type& getReturnType() const {
            return returnType;
        }

        __declspec(property(get = getReturnType)) const Type& ReturnType;

        inline const Array<std::reference_wrapper<const Type>>& getParameters() const {
            return parameters;
        }

        __declspec(property(get = getParameters)) const Array<std::reference_wrapper<const Type>>& Parameters;
    };
}
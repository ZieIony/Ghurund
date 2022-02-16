#pragma once

#include "Common.h"
#include "core/allocation/Allocator.h"
#include "core/collection/Array.h"
#include "core/Tuple.h"
#include "core/Exceptions.h"
#include "core/logging/Formatter.h"

namespace Ghurund::Core {
    class Type;

    class TypeMember {
    protected:
        void checkParameter(size_t index, const Type& expectedType, const Type& actualType) const;

    public:
        virtual ~TypeMember() {}

        template<typename... ArgsT>
        void checkParameters(const Array<std::reference_wrapper<const Type>>& parameters) const {
            Array<std::reference_wrapper<const Type>> currentParameters = { getType<ArgsT>()... };
            if (currentParameters.Size != parameters.Size)
                throw InvalidParamException(std::format("{} parameters expected, {} provided.\n", parameters.Size, currentParameters.Size).c_str());
            for (size_t i = 0; i < currentParameters.Size; i++) {
                auto& refWrapper = currentParameters[i];
                const Type& expectedType = parameters.get(i).get();
                const Type& actualType = refWrapper.get();
                checkParameter(i, expectedType, actualType);
            }
        }
    };
}
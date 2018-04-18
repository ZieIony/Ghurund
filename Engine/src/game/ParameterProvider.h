#pragma once

#include "ParameterManager.h"

namespace Ghurund {
    class ParameterProvider {
    public:
        virtual ~ParameterProvider() = default;

        virtual void initParameters(ParameterManager &parameterManager) = 0;

        virtual void fillParameters() = 0;
    };
}
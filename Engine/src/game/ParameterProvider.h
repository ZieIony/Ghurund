#pragma once

#include "ParameterManager.h"

namespace Ghurund {
    class ParameterProvider {
    protected:
        List<Parameter*> parameters;

    public:
        virtual ~ParameterProvider() = default;

        virtual void initParameters(ParameterManager &parameterManager) = 0;

        virtual void fillParameters() = 0;

        List<Parameter*> &getParameters() {
            return parameters;
        }

        __declspec(property(get = getParameters)) List<Parameter*> &Parameters;
    };
}
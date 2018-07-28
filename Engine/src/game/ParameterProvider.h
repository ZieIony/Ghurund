#pragma once

#include "ParameterManager.h"

namespace Ghurund {
    class ParameterProvider {
    protected:
        List<Parameter*> parameters;

    public:
        virtual ~ParameterProvider() = default;

        virtual void initParameters(ParameterManager &parameterManager) {}

        virtual void fillParameters() {}

        List<Parameter*> &getParameters() {
            return parameters;
        }

        __declspec(property(get = getParameters)) List<Parameter*> &Parameters;
    };
}
#pragma once

#include "Ghurund.h"
#include "Parameter.h"
#include "collection/String.h"
#include "core/CriticalSection.h"
#include "core/Object.h"
#include "graphics/Graphics.h"

namespace Ghurund {

    class ParameterManager: public Object {
    private:
        Map<ASCIIString, Parameter*> parameters;

    public:
        ParameterManager();

        ~ParameterManager();

        Map<ASCIIString, Parameter*>& getParameters() {
            return parameters;
        }

        __declspec(property(get = getParameters)) Map<ASCIIString, Parameter*>& Parameters;

        const static Ghurund::Type& TYPE;

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

    };
}
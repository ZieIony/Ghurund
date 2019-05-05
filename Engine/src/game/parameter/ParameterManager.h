#pragma once

#include "Ghurund.h"
#include "Parameter.h"
#include "collection/String.h"
#include "collection/PointerMap.h"
#include "core/Object.h"

namespace Ghurund {

    class ParameterManager: public Object {
    private:
        PointerMap<ASCIIString, Parameter*> parameters;

    public:
        ParameterManager();

        PointerMap<ASCIIString, Parameter*>& getParameters() {
            return parameters;
        }

        __declspec(property(get = getParameters)) PointerMap<ASCIIString, Parameter*>& Parameters;

        const static Ghurund::Type& TYPE;

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

    };
}
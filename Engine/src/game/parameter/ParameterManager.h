#pragma once

#include "Ghurund.h"
#include "Parameter.h"
#include "collection/String.h"
#include "collection/PointerList.h"
#include "core/Object.h"

namespace Ghurund {

    class ParameterManager: public Object {
    private:
        PointerList<Parameter*> parameters;

    public:
        ParameterManager();

        PointerList<Parameter*>& getParameters() {
            return parameters;
        }

        __declspec(property(get = getParameters)) PointerList<Parameter*>& Parameters;

        const static Ghurund::Type& TYPE;

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

    };
}
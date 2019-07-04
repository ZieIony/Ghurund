#pragma once

#include "Parameter.h"
#include "collection/String.h"
#include "collection/PointerList.h"
#include "core/Object.h"

namespace Ghurund {

    class ResourceContext;

    class ParameterManager: public Object {
    private:
        PointerList<Parameter*> parameters;

    public:
        ParameterManager();

        void initDefaultTextures(ResourceContext& context);

        PointerList<Parameter*>& getParameters() {
            return parameters;
        }

        __declspec(property(get = getParameters)) PointerList<Parameter*>& Parameters;

        Parameter* getParameter(const ASCIIString& name) {
            for (Parameter* p : Parameters) {
                if (p != nullptr && strcmp(p->ConstantName, name)==0)
                    return p;
            }

            return nullptr;
        }

        const static Ghurund::Type& TYPE;

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

    };
}
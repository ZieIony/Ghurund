#pragma once

#include "Parameter.h"
#include "core/string/String.h"
#include "core/collection/PointerList.h"
#include "core/Object.h"

namespace Ghurund {

    class ResourceContext;

    class ParameterManager: public Object {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(ParameterManager);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<ParameterManager>();
		
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

		inline static const Ghurund::Type& TYPE = TypeBuilder<ParameterManager>(NAMESPACE_NAME, CLASS_NAME).withConstructor(CONSTRUCTOR);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

    };
}
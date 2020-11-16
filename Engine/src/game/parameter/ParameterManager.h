#pragma once

#include "Parameter.h"
#include "core/string/String.h"
#include "core/collection/PointerList.h"
#include "core/Object.h"

namespace Ghurund {

    class ResourceContext;

    class ParameterManager: public Object {
    private:
		PointerList<Parameter*> parameters;

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<ParameterManager>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ParameterManager))
                .withConstructor(CONSTRUCTOR);

            return TYPE;
        }

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

		inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

    };
}
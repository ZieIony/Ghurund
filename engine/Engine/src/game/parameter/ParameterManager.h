#pragma once

#include "Parameter.h"
#include "core/string/String.h"
#include "core/collection/PointerList.h"
#include "core/Object.h"

namespace Ghurund {

    class Graphics;
    class CommandList;
    class ResourceManager;

    class ParameterManager: public Object {
    private:
		PointerList<Parameter*> parameters;

        static const Ghurund::Type& GET_TYPE();

    public:
        ParameterManager();

        void initDefaultTextures(ResourceManager& manager, Graphics& graphics, CommandList& commandList);

        PointerList<Parameter*>& getParameters() {
            return parameters;
        }

        __declspec(property(get = getParameters)) PointerList<Parameter*>& Parameters;

        Parameter* getParameter(const AString& name) {
            for (Parameter* p : Parameters) {
                if (p != nullptr && strcmp(p->ConstantName.Data, name.Data)==0)
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
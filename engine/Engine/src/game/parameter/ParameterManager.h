#pragma once

#include "game/parameter/Parameter.h"
#include "core/string/String.h"
#include "core/collection/PointerList.h"
#include "core/Object.h"

namespace Ghurund::Core {
    class ResourceManager;
}

namespace Ghurund::Core::DirectX {
    class Graphics;
    class CommandList;
}

namespace Ghurund {
    using namespace Ghurund::Core;
    using namespace Ghurund::Core::DirectX;

    class ParameterManager: public Object {
    private:
		PointerList<Parameter*> parameters;

        static const Ghurund::Core::Type& GET_TYPE();

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

		inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}
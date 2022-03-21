module;

#include "Ghurund.Engine.h"
#include "core/reflection/Type.h"

module Ghurund.Engine.Application.LayerList;

namespace Ghurund::Core {
    template<>
    const Type& getType<LayerList>() {
        static Type TYPE = Type(Ghurund::NAMESPACE_NAME, "LayerList", sizeof(LayerList));
        return TYPE;
    }
}
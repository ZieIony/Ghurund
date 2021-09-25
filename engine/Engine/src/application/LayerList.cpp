#include "ghpch.h"
#include "LayerList.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<LayerList>() {
        static Type TYPE = Type(Ghurund::NAMESPACE_NAME, "LayerList", sizeof(LayerList));
        return TYPE;
    }
}
#include "ghuidxpch.h"
#include "Shape.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::DirectX::Shape>() {
        static Type TYPE = Type(Ghurund::UI::DirectX::NAMESPACE_NAME, GH_STRINGIFY(Shape), sizeof(Ghurund::UI::DirectX::Shape));
        return TYPE;
    }
}

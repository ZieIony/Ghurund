#include "ghuidxpch.h"
#include "UIContext.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::DirectX::UIContext>() {
        static Type TYPE = Type(Ghurund::UI::DirectX::NAMESPACE_NAME, GH_STRINGIFY(UIContext), sizeof(Ghurund::UI::DirectX::UIContext));
        return TYPE;
    }
}
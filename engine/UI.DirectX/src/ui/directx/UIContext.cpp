#include "ghuidxpch.h"
#include "UIContext.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::DirectX::UiContext>() {
        static Type TYPE = Type(Ghurund::UI::DirectX::NAMESPACE_NAME, GH_STRINGIFY(UiContext), sizeof(Ghurund::UI::DirectX::UiContext));
        return TYPE;
    }
}
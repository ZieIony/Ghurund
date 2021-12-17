#include "ghuidxpch.h"
#include "UIContext.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Direct2D::UIContext>() {
        static Type TYPE = Type(Ghurund::UI::Direct2D::NAMESPACE_NAME, "UIContext", sizeof(Ghurund::UI::Direct2D::UIContext));
        return TYPE;
    }
}
#include "ghuioglpch.h"
#include "UIContext.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::OpenGL::UIContext>() {
        static Type TYPE = Type(Ghurund::UI::OpenGL::NAMESPACE_NAME, "UIContext", sizeof(Ghurund::UI::OpenGL::UIContext));
        return TYPE;
    }
}
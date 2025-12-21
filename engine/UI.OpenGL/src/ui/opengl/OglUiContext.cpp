#include "ghuioglpch.h"
#include "OglUiContext.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::OpenGL::OglUiContext>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::OpenGL::OglUiContext>();
        return TYPE;
    }
}

namespace Ghurund::UI::OpenGL {
    Resource* OglUiContext::makeControlMesh() {
        return nullptr;
    }
}
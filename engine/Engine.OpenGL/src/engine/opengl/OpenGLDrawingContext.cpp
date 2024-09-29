#include "gheoglpch.h"
#include "OpenGLDrawingContext.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::Engine::OpenGL::OpenGLDrawingContext>() {
        static Type TYPE = TypeBuilder<Ghurund::Engine::OpenGL::OpenGLDrawingContext>(Ghurund::Engine::OpenGL::NAMESPACE_NAME, GH_STRINGIFY(OpenGLDrawingContext));
        return TYPE;
    }
}
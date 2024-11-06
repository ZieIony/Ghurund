#include "gheoglpch.h"
#include "OpenGLDrawingContext.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::Engine::OpenGL::OpenGLDrawingContext>() {
        static const Type TYPE = TypeBuilder<Ghurund::Engine::OpenGL::OpenGLDrawingContext>();
        return TYPE;
    }
}
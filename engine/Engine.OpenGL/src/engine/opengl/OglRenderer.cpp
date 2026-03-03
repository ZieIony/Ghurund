#include "gheoglpch.h"

#include "OglRenderer.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"

#include <gl\glew.h>

namespace Ghurund::Engine::OpenGL {
    const Ghurund::Core::Type& OglRenderer::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<OglRenderer>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void OglRenderer::onInit() {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }
}

#include "gheoglpch.h"

#include "OGlRenderer.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"

#include <gl\glew.h>

namespace Ghurund::Engine::OpenGL {
    const Ghurund::Core::Type& OGlRenderer::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<OGlRenderer>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void OGlRenderer::init(ParameterManager& parameterManager) {
        this->parameterManager = &parameterManager;
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    void OGlRenderer::uninit() {
    }

    void OGlRenderer::clear(const Color* color) {
        if (color) {
            glClearColor(color->R, color->G, color->B, color->A);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        glClear(GL_DEPTH_BUFFER_BIT);
    }
}
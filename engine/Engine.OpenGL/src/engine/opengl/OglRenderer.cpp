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
}
#include "gheoglpch.h"

#include "Renderer.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"

#include <gl\glew.h>

namespace Ghurund::Engine::OpenGL {
    const Ghurund::Core::Type& Renderer::GET_TYPE() {
        static auto PROPERTY_STATISTICS = Property<Renderer, RenderingStatistics&>("Statistics", &getStatistics);

        static const Ghurund::Core::Type TYPE = TypeBuilder<Renderer>()
            .withProperty(PROPERTY_STATISTICS)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Renderer::init(ParameterManager& parameterManager) {
        this->parameterManager = &parameterManager;
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    void Renderer::uninit() {
    }

    void Renderer::clear(const Color* color) {
        if (color) {
            glClearColor(color->R, color->G, color->B, color->A);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        glClear(GL_DEPTH_BUFFER_BIT);
    }
}
#include "gheoglpch.h"
#include "OglShaderType.h"

#include <GL/glew.h>

namespace Ghurund::Engine::OpenGL {
    const OglShaderType OglShaderType::VERTEX = OglShaderType(OglShaderTypeEnum::VERTEX, "VERTEX", "Vertex", GL_VERTEX_SHADER);
    const OglShaderType OglShaderType::FRAGMENT = OglShaderType(OglShaderTypeEnum::FRAGMENT, "FRAGMENT", "Fragment", GL_FRAGMENT_SHADER);
}
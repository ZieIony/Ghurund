#pragma once

#include "OglShader.h"
#include <core/io/DirectoryPath.h>
#include <core/string/String.h>
#include "core/object/OwnedNotNull.h"

namespace Ghurund::Engine::OpenGL {
	using namespace Ghurund::Core;

	struct ShaderCompilationResult {
		Buffer data;
		AString logs;
		uint32_t errorCode;
	};

	class OglShaderCompiler {
	public:
		OglShaderProgram* compile(const AString& sourceCode, const OglShaderType& shaderType);

		OwnedNotNull<OglShader> build(SharedPointer<OglShaderProgram> vertexProgram, SharedPointer<OglShaderProgram> fragmentProgram) {
			OglShader* shader = ghnew OglShader();
			shader->init(vertexProgram, fragmentProgram);
			return shader;
		}
	};
}
#pragma once

#include "OglShaderType.h"

#include "GL/glew.h"

namespace Ghurund::Engine::OpenGL {
	using namespace Ghurund::Core;

	class OglShaderProgram {
	private:
		const OglShaderType& type;
		GLuint id;

		OglShaderProgram& operator=(const OglShaderProgram& other) = delete;

	public:
		OglShaderProgram(const OglShaderType& type, GLuint id):
			type(type), id(id) {
		}

		~OglShaderProgram() {
			glDeleteShader(id);
		}

		inline GLuint getId() const {
			return id;
		}

		__declspec(property(get = getId)) GLuint Id;

		const OglShaderType& getType() const {
			return type;
		}

		__declspec(property(get = getType)) OglShaderType& Type;
	};
}
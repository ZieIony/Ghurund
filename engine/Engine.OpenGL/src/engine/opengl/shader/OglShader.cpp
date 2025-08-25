#include "gheoglpch.h"
#include "OglShader.h"

namespace Ghurund::Engine::OpenGL {
	const Ghurund::Core::Type& OglShader::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<OglShader>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
	
	OglShader::OglShader() {
		id = glCreateProgram();
	}
	
	OglShader::~OglShader() {
		glDeleteProgram(id);
	}
	
	void OglShader::init(SharedPointer<OglShaderProgram> vertexProgram, SharedPointer<OglShaderProgram> fragmentProgram) {
		GLint Result = GL_FALSE;
		int InfoLogLength;

		// Link the program
		glAttachShader(id, vertexProgram->Id);
		glAttachShader(id, fragmentProgram->Id);
		glLinkProgram(id);

		// Check the program
		glGetProgramiv(id, GL_LINK_STATUS, &Result);
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			Buffer message(InfoLogLength + 1);
			glGetShaderInfoLog(id, InfoLogLength, nullptr, (char*)message.Data);
			throw CallFailedException((char*)message.Data);
		}

		glDetachShader(id, vertexProgram->Id);
		glDetachShader(id, fragmentProgram->Id);
	}
}
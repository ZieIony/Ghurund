#include "gheoglpch.h"
#include "OglShaderCompiler.h"

#include "OglShaderProgram.h"
#include "OglCompilationException.h"

namespace Ghurund::Engine::OpenGL {
	OglShaderProgram* OglShaderCompiler::compile(const AString& sourceCode, const OglShaderType& shaderType) {
		GLuint id = glCreateShader(shaderType.TypeCode);
		const char* data = sourceCode.Data;
		glShaderSource(id, 1, &data, nullptr);
		glCompileShader(id);

		int infoLogLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0) {
			Buffer message(infoLogLength + 1);
			glGetShaderInfoLog(id, infoLogLength, nullptr, (char*)message.Data);
			AString errorMessages = (char*)message.Data;
			auto text = std::format(_T("Error while compiling shader:\n%s\n"), errorMessages);
			Logger::log(LogType::ERR0R, text.c_str());
			throw OglCompilationException(errorMessages.Data);
		} else {
			return ghnew OglShaderProgram(shaderType, id);
		}
	}
}

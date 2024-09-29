#pragma once

#include "core/resource/Resource.h"
#include "core/io/File.h"
#include "core/Exceptions.h"
#include "core/Buffer.h"

#include "GL/glew.h"

using namespace Ghurund::Core;

class FragmentShaderProgram {
private:
	GLuint id;

public:
	FragmentShaderProgram() {
		id = glCreateShader(GL_FRAGMENT_SHADER);
	}

	~FragmentShaderProgram() {
		glDeleteShader(id);
	}

	void compile(const AString& source) {
		const char* data = source.Data;
		glShaderSource(id, 1, &data, nullptr);
		glCompileShader(id);

		int infoLogLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0) {
			Buffer message(infoLogLength + 1);
			glGetShaderInfoLog(id, infoLogLength, nullptr, (char*)message.Data);
			throw CallFailedException((char*)message.Data);
		}
	}

	inline GLuint getId() const {
		return id;
	}

	__declspec(property(get = getId)) GLuint Id;
};

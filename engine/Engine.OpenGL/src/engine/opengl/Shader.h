#pragma once

#include "core/resource/Resource.h"
#include "core/io/File.h"
#include "VertexShaderProgram.h"
#include "FragmentShaderProgram.h"

#include "GL/glew.h"

using namespace Ghurund::Core;

class Shader {
private:
	VertexShaderProgram vertexShader;
	FragmentShaderProgram fragmentShader;

	GLuint id;

public:
	Shader() {
		id = glCreateProgram();
	}

	~Shader() {
		glDeleteProgram(id);
	}

	void init(const FilePath& vertexShaderPath, const FilePath& fragmentShaderPath) {
		GLint Result = GL_FALSE;
		int InfoLogLength;

		Buffer vertexFileBuffer;
		File vertexFile(vertexShaderPath);
		vertexFile.read(vertexFileBuffer);
		Buffer fragmentFileBuffer;
		File fragmentFile(fragmentShaderPath);
		fragmentFile.read(fragmentFileBuffer);

		AString vertexData((const char*)vertexFileBuffer.Data, vertexFile.Size);
		vertexShader.compile(vertexData);
		AString fragmentData((const char*)fragmentFileBuffer.Data, fragmentFile.Size);
		fragmentShader.compile(fragmentData);

		// Link the program
		glAttachShader(id, vertexShader.Id);
		glAttachShader(id, fragmentShader.Id);
		glLinkProgram(id);

		// Check the program
		glGetProgramiv(id, GL_LINK_STATUS, &Result);
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			Buffer message(InfoLogLength + 1);
			glGetShaderInfoLog(id, InfoLogLength, nullptr, (char*)message.Data);
			throw CallFailedException((char*)message.Data);
		}

		glDetachShader(id, vertexShader.Id);
		glDetachShader(id, fragmentShader.Id);
	}

	void set() {
		glUseProgram(id);
	}

	inline GLuint getId() const {
		return id;
	}

	__declspec(property(get = getId)) GLuint Id;
};

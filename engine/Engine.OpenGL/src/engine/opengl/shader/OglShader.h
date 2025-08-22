#pragma once

#include "core/resource/Resource.h"
#include "core/io/File.h"
#include "OglShaderProgram.h"

#include "GL/glew.h"

using namespace Ghurund::Core;

namespace Ghurund::Engine::OpenGL {
	class OglShader:public Resource {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = OglShader::GET_TYPE();
#pragma endregion

	private:
		GLuint id;

	public:
		OglShader() {
			id = glCreateProgram();
		}

		~OglShader() {
			glDeleteProgram(id);
		}

		void init(SharedPointer<OglShaderProgram> vertexProgram, SharedPointer<OglShaderProgram> fragmentProgram) {
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

		void set() {
			glUseProgram(id);
		}

		inline GLuint getId() const {
			return id;
		}

		__declspec(property(get = getId)) GLuint Id;

#pragma region formats
	protected:
		virtual const Array<ResourceFormat>& getFormatsImpl() const override {
			return OglShader::FORMATS;
		}

	public:
		static const inline ResourceFormat FORMAT_SHADER = ResourceFormat(L"shader", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_GLSL = ResourceFormat(L"glsl", ResourceFormatOptions::CAN_LOAD);

		inline static const Array<ResourceFormat>& FORMATS = { FORMAT_SHADER, FORMAT_GLSL };

		static const inline uint32_t VERSION = 0;
#pragma endregion
	};
}
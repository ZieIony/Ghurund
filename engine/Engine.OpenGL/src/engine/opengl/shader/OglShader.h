#pragma once

#include "OglShaderProgram.h"

#include "core/io/File.h"
#include "engine/graphics/shader/Shader.h"

#include <gl/gl.h>

namespace Ghurund::Engine::OpenGL {
	using namespace Ghurund::Core;

	class OglShader:public Shader {
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
		OglShader();

		~OglShader();

		void init(const OglShaderProgram& vertexProgram, const OglShaderProgram& fragmentProgram);

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
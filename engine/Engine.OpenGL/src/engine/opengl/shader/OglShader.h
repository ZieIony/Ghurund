#pragma once

#include "core/resource/Resource.h"
#include "core/io/File.h"
#include "OglShaderProgram.h"

#include "gl/gl.h"

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
		OglShader();

		~OglShader();

		void init(SharedPointer<OglShaderProgram> vertexProgram, SharedPointer<OglShaderProgram> fragmentProgram);

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
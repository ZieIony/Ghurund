#pragma once

#include "core/enum/Enum.h"

#include <cstdint>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	enum class ShaderInputSemanticEnum:uint8_t {
		POSITION, NORMAL, TEXCOORD, TANGENT, COLOR, OBJECT_ID
	};

	class ShaderInputSemantic:public Enum<ShaderInputSemanticEnum, ShaderInputSemantic> {
	private:
		ShaderInputSemantic(ShaderInputSemanticEnum value, const char* name):Enum<ShaderInputSemanticEnum, ShaderInputSemantic>(value, name) {}

	public:
		static const ShaderInputSemantic POSITION, NORMAL, TEXCOORD, TANGENT, COLOR, OBJECT_ID;

		ShaderInputSemantic(const ShaderInputSemantic& other):Enum(other) {}

		ShaderInputSemantic(ShaderInputSemantic&& other) noexcept:Enum(other) {}
	};
}

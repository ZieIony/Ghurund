#pragma once

#include "ShaderType.h"

#include <exception>

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class EntrypointNotFoundException:public std::exception {
	public:
		const ShaderType& shaderType;

		EntrypointNotFoundException(const ShaderType& shaderType):shaderType(shaderType) {}
	};
}
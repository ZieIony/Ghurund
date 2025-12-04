#pragma once

#include "engine/directx/shader/DxShaderType.h"

#include <exception>

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class DxEntrypointNotFoundException:public std::exception {
	public:
		const DxShaderType& shaderType;

		DxEntrypointNotFoundException(const DxShaderType& shaderType):shaderType(shaderType) {}
	};
}
#pragma once

#include "DxShaderType.h"
#include "engine/graphics/shader/ShaderSource.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	struct DxShaderProgramSourceCode:public ShaderProgramSourceCode {
		DxShaderType shaderType;
		AString entryPoint;
		AString sourceName;

		DxShaderProgramSourceCode(
			DxShaderType shaderType,
			const AString& sourceCode,
			const AString& sourceName,
			const AString& entryPoint = AString()
		):ShaderProgramSourceCode(sourceCode),
			shaderType(shaderType),
			entryPoint(entryPoint.IsEmpty ? shaderType.EntryPoint : entryPoint),
			sourceName(sourceName) {
#ifdef _DEBUG
			_ASSERTE(sourceName.Length < sourceCode.Length);
			_ASSERTE(entryPoint.Length < sourceCode.Length);
#endif
		}
	};
}

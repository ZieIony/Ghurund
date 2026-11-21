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

		virtual uint64_t getDataSize() const override {
			return __super::getDataSize() + sizeof(*this) - sizeof(ShaderProgramSourceCode);
		}
	};

	struct DxVertexShaderProgramSourceCode:public DxShaderProgramSourceCode {
		VertexShaderSettings settings;

		DxVertexShaderProgramSourceCode(
			const AString& sourceCode,
			const AString& sourceName,
			const VertexShaderSettings& settings,
			const AString& entryPoint = AString()
		):DxShaderProgramSourceCode(DxShaderType::VERTEX, sourceCode, sourceName, entryPoint), settings(settings) {
		}

		virtual uint64_t getDataSize() const override {
			return __super::getDataSize() + sizeof(*this) - sizeof(DxShaderProgramSourceCode);
		}
	};

	struct DxPixelShaderProgramSourceCode:public DxShaderProgramSourceCode {
		PixelShaderSettings settings;

		DxPixelShaderProgramSourceCode(
			const AString& sourceCode,
			const AString& sourceName,
			const PixelShaderSettings& settings,
			const AString& entryPoint = AString()
		):DxShaderProgramSourceCode(DxShaderType::PIXEL, sourceCode, sourceName, entryPoint), settings(settings) {
		}

		virtual uint64_t getDataSize() const override {
			return __super::getDataSize() + sizeof(*this) - sizeof(DxShaderProgramSourceCode);
		}
	};
}

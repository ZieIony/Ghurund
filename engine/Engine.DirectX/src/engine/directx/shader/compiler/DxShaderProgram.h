#pragma once

#include "core/Buffer.h"
#include <core/string/String.h>
#include "engine/directx/shader/DxShaderType.h"
#include "DxShaderProgram.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class DxShaderProgram {
	private:
		const DxShaderType& type;
		Buffer byteCode;
		AString entryPoint;

	public:
		DxShaderProgram(const DxShaderType& type, Buffer& byteCode, const AString& entryPoint):
			type(type), byteCode(byteCode), entryPoint(entryPoint) {
		}

		DxShaderProgram(DxShaderProgram&& other) noexcept:
			type(type), byteCode(std::move(other.byteCode)), entryPoint(std::move(other.entryPoint)) {
		}

		const AString& getEntryPoint() const {
			return entryPoint;
		}

		__declspec(property(get = getEntryPoint)) const AString& EntryPoint;

		const Buffer& getByteCode() const {
			return byteCode;
		}

		__declspec(property(get = getByteCode)) const Buffer& ByteCode;

		const DxShaderType& getType() const {
			return type;
		}

		__declspec(property(get = getType)) DxShaderType& Type;
	};
}
#pragma once

#include "core/Buffer.h"
#include "ShaderType.h"
#include <core/string/String.h>

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class ShaderProgram {
	private:
		const ShaderType& type;
		Buffer byteCode;
		AString entryPoint;

	public:
		ShaderProgram(const ShaderType& type, Buffer& byteCode, const AString& entryPoint):
			type(type), byteCode(byteCode), entryPoint(entryPoint) {
		}

		ShaderProgram(ShaderProgram&& other):
			type(std::move(type)), byteCode(std::move(other.byteCode)), entryPoint(std::move(other.entryPoint)) {
		}

		const AString& getEntryPoint() const {
			return entryPoint;
		}

		__declspec(property(get = getEntryPoint)) const AString& EntryPoint;


		const Buffer& getByteCode() const {
			return byteCode;
		}

		__declspec(property(get = getByteCode)) const Buffer& ByteCode;

		const ShaderType& getType() const {
			return type;
		}

		__declspec(property(get = getType)) ShaderType& Type;
	};

}
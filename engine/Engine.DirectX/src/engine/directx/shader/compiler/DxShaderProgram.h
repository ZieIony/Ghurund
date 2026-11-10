#pragma once

#include "core/Buffer.h"
#include "core/string/String.h"
#include "engine/directx/shader/DxShaderType.h"

#include <d3d12shader.h>
#include <wrl/client.h>

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;
	using namespace Microsoft::WRL;

	class DxShaderProgram {
	private:
		const DxShaderType& type;
		Buffer byteCode;
		AString entryPoint;
		ComPtr<ID3D12ShaderReflection> reflection;

	public:
		DxShaderProgram(const DxShaderType& type, Buffer& byteCode, const AString& entryPoint, ComPtr<ID3D12ShaderReflection> reflection):
			type(type), byteCode(byteCode), entryPoint(entryPoint), reflection(reflection) {
		}

		DxShaderProgram(DxShaderProgram&& other) noexcept:
			type(type), byteCode(std::move(other.byteCode)), entryPoint(std::move(other.entryPoint)), reflection(other.reflection) {
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

		inline ID3D12ShaderReflection* getReflection() const {
			return reflection.Get();
		}

		__declspec(property(get = getReflection)) ID3D12ShaderReflection* Reflection;
	};
}

#pragma once

#include "core/Enum.h"

#pragma warning(push, 0)
#include <d3d12.h>
#pragma warning(pop)

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;
	using namespace Microsoft::WRL;

	enum class DxShaderTypeEnum {
		VERTEX = 1, PIXEL = 2, GEOMETRY = 4, HULL = 8, D0MAIN = 16, COMPUTE = 32
	};

	class DxShaderType:public Enum<DxShaderTypeEnum, DxShaderType> {
	private:
		const AString typeName;
		const AString entryPoint;
		D3D12_SHADER_VISIBILITY visibility;

		DxShaderType(
			DxShaderTypeEnum value,
			const AString& name,
			const AString& typeName,
			const AString& entryPoint,
			D3D12_SHADER_VISIBILITY visibility
		):Enum(value, name), typeName(typeName), entryPoint(entryPoint), visibility(visibility) {
		}

	public:
		static const DxShaderType VERTEX, PIXEL, GEOMETRY, HULL, D0MAIN, COMPUTE;

		const AString& getTypeName() const {
			return typeName;
		}

		__declspec(property(get = getTypeName)) const AString& TypeName;

		const AString& getEntryPoint() const {
			return entryPoint;
		}

		__declspec(property(get = getEntryPoint)) const AString& EntryPoint;

		D3D12_SHADER_VISIBILITY getVisibility() const {
			return visibility;
		}

		__declspec(property(get = getVisibility)) D3D12_SHADER_VISIBILITY Visibility;
	};
}
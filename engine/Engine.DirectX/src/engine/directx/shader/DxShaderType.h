#pragma once

#include "core/Enum.h"

#pragma warning(push, 0)
#include <d3d12.h>
#pragma warning(pop)

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	enum class DxShaderTypeEnum {
		VERTEX = 1, PIXEL = 2, GEOMETRY = 4, HULL = 8, D0MAIN = 16, COMPUTE = 32
	};

	class DxShaderType:public Enum<DxShaderTypeEnum, DxShaderType> {
	private:
		AString typeName;
		AString entryPoint;
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

		DxShaderType(
			const DxShaderType& other
		):Enum(other),
			typeName(other.typeName),
			entryPoint(other.entryPoint),
			visibility(other.visibility) {
		}

		DxShaderType(
			DxShaderType&& other
		) noexcept:Enum(other),
			typeName(std::move(other.typeName)),
			entryPoint(std::move(other.entryPoint)),
			visibility(other.visibility) {
		}

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

		DxShaderType& operator=(const DxShaderType& other) {
			if (this == &other)
				return *this;
			__super::operator=(other);
			typeName = other.typeName;
			entryPoint = other.entryPoint;
			visibility = other.visibility;
			return *this;
		}

		DxShaderType& operator=(DxShaderType&& other) noexcept {
			if (this == &other)
				return *this;
			typeName = std::move(other.typeName);
			entryPoint = std::move(other.entryPoint);
			visibility = other.visibility;
			return *this;
		}
	};
}

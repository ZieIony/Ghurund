#pragma once

#include "core/Enum.h"

namespace Ghurund::Engine::OpenGL {
	using namespace Ghurund::Core;

	enum class OglShaderTypeEnum {
		VERTEX = 1, FRAGMENT = 2
	};

	class OglShaderType:public Enum<OglShaderTypeEnum, OglShaderType> {
	private:
		const AString typeName;
		const uint16_t typeCode;

		OglShaderType(
			OglShaderTypeEnum value,
			const AString& name,
			const AString& typeName,
			uint16_t typeCode
		):Enum(value, name), typeName(typeName), typeCode(typeCode) {
		}

	public:
		static const OglShaderType VERTEX, FRAGMENT;

		const AString& getTypeName() const {
			return typeName;
		}

		__declspec(property(get = getTypeName)) const AString& TypeName;

		uint16_t getTypeCode() const {
			return typeCode;
		}

		__declspec(property(get = getTypeCode)) uint16_t TypeCode;
	};
}
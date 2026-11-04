#pragma once

#include "core/DataParsing.h"

namespace Ghurund::Engine {
	enum class MaterialVariantType {
		DEPTH, UNLIT, LIT, NORMALS, TANGENTS, TEXCOORDS, NUM_VARIANTS
	};
}

namespace Ghurund::Core {
	template<>
	inline Ghurund::Engine::MaterialVariantType parse(const WString& text) {
		if (text == L"depth") {
			return Ghurund::Engine::MaterialVariantType::DEPTH;
		} else if (text == L"unlit") {
			return Ghurund::Engine::MaterialVariantType::UNLIT;
		} else if (text == L"lit") {
			return Ghurund::Engine::MaterialVariantType::LIT;
		} else if (text == L"normals") {
			return Ghurund::Engine::MaterialVariantType::NORMALS;
		} else if (text == L"tangents") {
			return Ghurund::Engine::MaterialVariantType::TANGENTS;
		} else if (text == L"texCoords") {
			return Ghurund::Engine::MaterialVariantType::TEXCOORDS;
		} else {
			throw std::invalid_argument("text does not contain a MaterialVariantType");
		}
	};
}

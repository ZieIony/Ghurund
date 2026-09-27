#pragma once

#include "InputType.h"

#include "engine/graphics/CubeMap/ICubeMap.h"

namespace Ghurund::Engine {
	class CubeMapConstant {
	private:
		const ICubeMap* value = nullptr;

	public:
		const AString name;
		const uint32_t bindSlot;

		CubeMapConstant(const AString& name, uint32_t bindSlot):name(name), bindSlot(bindSlot) {}

		~CubeMapConstant() {
			if (value)
				value->release();
		}

		inline const ICubeMap* getValue() {
			return value;
		}

		inline void setValue(const ICubeMap* value) {
			setPointer(this->value, value);
		}

		__declspec(property(get = getValue, put = setValue)) const ICubeMap* Value;
	};
}

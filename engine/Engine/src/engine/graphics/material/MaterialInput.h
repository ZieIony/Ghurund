#pragma once

#include "core/string/String.h"
#include "engine/graphics/shader/InputType.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class MaterialInput:public Object {
	protected:
		bool isEmpty;

	public:
		MaterialInput(bool isEmpty):isEmpty(isEmpty) {}

		MaterialInput(const MaterialInput& other):isEmpty(other.isEmpty) {}

		MaterialInput(MaterialInput&& other) noexcept:isEmpty(other.isEmpty) {}

		inline bool getIsEmpty() const {
			return isEmpty;
		}

		__declspec(property(get = getIsEmpty)) bool IsEmpty;

		virtual const AString& getName() const = 0;

		__declspec(property(get = getName)) const AString& Name;

		virtual InputType getType() const = 0;

		__declspec(property(get = getType)) InputType Type;
	};
}
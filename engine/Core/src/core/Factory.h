#pragma once

#include "core/object/OwnedNotNull.h"

namespace Ghurund::Core {
	template<typename T>
	class Factory {
	public:
		virtual ~Factory() = 0 {}

		virtual OwnedNotNull<T> make() const = 0;
	};
}
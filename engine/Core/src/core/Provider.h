#pragma once

#include "core/object/Noncopyable.h"

namespace Ghurund::Core {
	template<typename Type>
	class Provider:public Noncopyable {
	public:
		virtual Type get() = 0;
	};
}
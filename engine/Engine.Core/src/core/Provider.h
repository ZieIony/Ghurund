#pragma once

namespace Ghurund::Core {
	template<typename Type>
	class Provider {
	public:
		virtual ~Provider() = 0 {}

		virtual Type get() = 0;
	};
}
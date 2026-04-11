#pragma once

namespace Ghurund::Core {
	template<typename T>
	class DefaultDeleter {
	public:
		inline void operator()(T* ptr) {
			delete ptr;
		}
	};
}

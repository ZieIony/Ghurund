#pragma once

#include <memory>

namespace Ghurund::Core {
	template<typename T>
	class Factory {
	public:
		virtual ~Factory() = 0 {}

		virtual std::unique_ptr<T> make() const = 0;
	};
}
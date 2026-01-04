#pragma once

#include "core/object/RefCountedObject.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class ConstantBuffer: public RefCountedObject {
	private:
	public:
		virtual ~ConstantBuffer() = 0 {}

		virtual size_t getSize() const = 0;

		__declspec(property(get = getSize)) size_t Size;

		virtual void setValue(const void* value, size_t size, size_t offset) = 0;
	};
}
#pragma once

#include "core/allocation/Allocator.h"

namespace Ghurund {
	class Object;

	__interface BaseConstructor {
		Object* newInstance() const;
		Object* newInstance(Allocator& allocator) const;
	};

	template <class T>
	class NoArgsConstructor :public BaseConstructor {
	public:
		virtual T* newInstance() const override {
			return ghnew T();
		}

		virtual T* newInstance(Allocator& allocator) const override {
			return new (allocator)T();
		}
	};
}
#pragma once

#include "Resource.h"

#include "core/collection/Bag.h"
#include "core/object/IntrusivePointer.h"
#include "core/object/NotNull.h"

#include <coroutine>

namespace Ghurund::Core {
	class ResourceAwaiter {
	private:
		Bag<ResourceAwaiter>& resourceAwaiters;
		std::coroutine_handle<> handle;
		IntrusivePointer<Resource> resource;

	public:
		ResourceAwaiter(
			Bag<ResourceAwaiter>& resourceAwaiters,
			NotNull<Resource> resource
		):resourceAwaiters(resourceAwaiters), resource(IntrusivePointer(resource.get())) {}

		ResourceAwaiter(
			const ResourceAwaiter& other
		):resourceAwaiters(other.resourceAwaiters), resource(other.resource) {}

		bool await_ready() const {
			return false;
		}

		bool await_suspend(std::coroutine_handle<> handle) {
			this->handle = handle;
			resourceAwaiters.add(*this);
			return true;
		}

		void await_resume() const {}

		Resource* getResource() const {
			return resource.get();
		}
	};
}

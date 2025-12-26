#pragma once

#include "Resource.h"
#include "core/object/IntrusivePointer.h"
#include "core/collection/Map.h"
#include "core/threading/CriticalSection.h"

namespace Ghurund::Core {
	class ResourceCollection {
	private:
		Map<WString, IntrusivePointer<Resource>> resources;
		CriticalSection section;

	public:
		Resource* get(const WString& path);

		void add(const WString& path, Resource& resource);

		void remove(const WString& path);

		void clear();
	};
}
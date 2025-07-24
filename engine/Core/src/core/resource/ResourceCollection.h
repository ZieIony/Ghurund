#pragma once

#include "Resource.h"
#include "ResourcePath.h"
#include "core/object/IntrusivePointer.h"
#include "core/collection/Map.h"
#include "core/threading/CriticalSection.h"

namespace Ghurund::Core {
	class ResourceCollection {
	private:
		Map<ResourcePath, IntrusivePointer<Resource>> resources;
		CriticalSection section;

	public:
		Resource* get(const ResourcePath& path);

		void add(const ResourcePath& path, Resource& resource);

		void remove(const ResourcePath& path);

		void clear();
	};
}
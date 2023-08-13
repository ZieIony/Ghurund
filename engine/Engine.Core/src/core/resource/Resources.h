#pragma once

#include "Resource.h"
#include "ResourcePath.h"
#include "core/SharedPointer.h"

namespace Ghurund::Core {
	class Resources {
	private:
		Map<ResourcePath, SharedPointer<Resource>> resources;
		CriticalSection section;

	public:
		Resource* get(const ResourcePath& path);

		void add(const ResourcePath& path, Resource& resource);

		void remove(const ResourcePath& path);

		void clear();
	};
}
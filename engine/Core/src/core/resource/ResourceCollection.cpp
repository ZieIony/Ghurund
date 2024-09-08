#include "ghcpch.h"
#include "ResourceCollection.h"

namespace Ghurund::Core {

	Resource* ResourceCollection::get(const ResourcePath& path) {
		SectionLock lock(section);
		auto iterator = resources.find(path);
		if (iterator != resources.end())
			return resources.get(path).get();
		return nullptr;
	}

	void ResourceCollection::add(const ResourcePath& path, Resource& resource) {
		SectionLock lock(section);
		resource.addReference();
		resources.put(path, IntrusivePointer(&resource));
	}

	void ResourceCollection::remove(const ResourcePath& path) {
		SectionLock lock(section);
		resources.remove(path);
	}

	void ResourceCollection::clear() {
		SectionLock lock(section);
		resources.clear();
	}
}
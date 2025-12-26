#include "ghcpch.h"
#include "ResourceCollection.h"

namespace Ghurund::Core {

	Resource* ResourceCollection::get(const WString& key) {
		SectionLock lock(section);
		auto iterator = resources.find(key);
		if (iterator != resources.end())
			return resources.get(key).get();
		return nullptr;
	}

	void ResourceCollection::add(const WString& key, Resource& resource) {
		SectionLock lock(section);
		resource.addReference();
		resources.put(key, IntrusivePointer(&resource));
	}

	void ResourceCollection::remove(const WString& key) {
		SectionLock lock(section);
		resources.remove(key);
	}

	void ResourceCollection::clear() {
		SectionLock lock(section);
		resources.clear();
	}
}
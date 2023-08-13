#include "ghcpch.h"
#include "Resources.h"

namespace Ghurund::Core {

	Resource* Resources::get(const ResourcePath& path) {
		SectionLock lock(section);
		size_t index = resources.indexOfKey(path);
		if (index != resources.Size)
			return resources.getValue(index).get();
		return nullptr;
	}

	void Resources::add(const ResourcePath& path, Resource& resource) {
		SectionLock lock(section);
		resource.addReference();
		resources.set(path, SharedPointer(&resource));
	}

	void Resources::remove(const ResourcePath& path) {
		SectionLock lock(section);
		resources.remove(path);
	}

	void Resources::clear() {
		SectionLock lock(section);
		resources.clear();
	}
}
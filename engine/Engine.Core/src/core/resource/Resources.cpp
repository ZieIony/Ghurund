#include "ghcpch.h"
#include "Resources.h"

namespace Ghurund::Core {

	Resource* Resources::get(const ResourcePath& path) {
		SectionLock lock(section);
		auto iterator = resources.find(path);
		if (iterator != resources.end())
			return resources.get(path).get();
		return nullptr;
	}

	void Resources::add(const ResourcePath& path, Resource& resource) {
		SectionLock lock(section);
		resource.addReference();
		resources.put(path, SharedPointer(&resource));
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
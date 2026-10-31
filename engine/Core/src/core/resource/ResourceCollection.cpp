#include "ghcpch.h"
#include "ResourceCollection.h"

namespace Ghurund::Core {
	Resource* ResourceCollection::get(const WString& name) {
		std::unique_lock lock(mutex);
		auto iterator = resourcesByName.find(name);
		if (iterator != resourcesByName.end())
			return iterator->value.get();
		return nullptr;
	}

	Resource* ResourceCollection::get(const FilePath& path) {
		std::unique_lock lock(mutex);
		auto iterator = resourcesByPath.find(path);
		if (iterator != resourcesByPath.end())
			return iterator->value.get();
		return nullptr;
	}

	void ResourceCollection::put(NotNull<Resource> resource) {
		std::unique_lock lock(mutex);
		// don't accept resources without a usable id
		_ASSERTE(resource->Name != nullptr || resource->Path != nullptr);
		if (resource->Path) {
			_ASSERTE(!resourcesByPath.contains(*resource->Path));
			resource->addReference();
			resourcesByPath.put(*resource->Path, IntrusivePointer(resource.get()));
		} else if (resource->Name) {
			_ASSERTE(!resourcesByName.contains(*resource->Name));
			resource->addReference();
			resourcesByName.put(*resource->Name, IntrusivePointer(resource.get()));
		}
	}

	void ResourceCollection::remove(NotNull<Resource> resource) {
		std::unique_lock lock(mutex);
#ifdef _DEBUG
		// don't accept resources without a usable id
		_ASSERTE(resource->Name || resource->Path);
#endif
		if (resource->Path)
			resourcesByPath.remove(*resource->Path);
		if (resource->Name)
			resourcesByName.remove(*resource->Name);
	}

	void ResourceCollection::remove(const WString& name) {
		std::unique_lock lock(mutex);

		auto iterator = resourcesByName.find(name);
		if (iterator != resourcesByName.end()) {
			// TODO: implement iterator.erase() or replace with std::map
			resourcesByName.remove(name);
			if(iterator->value->Path)
				resourcesByPath.remove(*iterator->value->Path);
		}
	}

	void ResourceCollection::remove(const FilePath& path) {
		std::unique_lock lock(mutex);

		auto iterator = resourcesByPath.find(path);
		if (iterator != resourcesByPath.end()) {
			// TODO: implement iterator.erase() or replace with std::map
			resourcesByPath.remove(path);
			if (iterator->value->Name)
				resourcesByName.remove(*iterator->value->Name);
		}
	}

	void ResourceCollection::clear() {
		std::unique_lock lock(mutex);
		resourcesByName.clear();
		resourcesByPath.clear();
	}

#ifdef _DEBUG
	void ResourceCollection::validateResources() {
		std::unique_lock lock(mutex);
		for (auto& entry : resourcesByPath) {
			_ASSERTE(entry.value != nullptr);
			_ASSERTE(entry.value->Path != nullptr);
			_ASSERTE(entry.value->Type.isOrExtends(Resource::TYPE));
		}
	}

	void ResourceCollection::printResources() {
		std::unique_lock lock(mutex);
		for (auto& entry : resourcesByPath) {
			auto resource = entry.value.get();
			auto name = resource->Name ? *resource->Name : L"[null]";
			auto path = resource->Path ? resource->Path->toString() : L"[null]";
			auto state = [&] {
				if (resource->State == ResourceState::EMPTY) {
					return AString("e");
				}else if(resource->State == ResourceState::LOADED) {
					return AString("l");
				} else {
					return AString("i");
				}
			}();
			auto formatMem = [&](int s) {
				if (s < 1024) {
					return std::format(_T("{}B"), s);
				} else if (s < 1024 * 1024) {
					return std::format(_T("{}KB"), s / 1024);
				} else {
					return std::format(_T("{}MB"), s / 1024 / 1024);
				}
			};
			auto message = std::format(
				_T("type: {}, state: {}, size: s: {}, g: {}, refs: {}, name: \"{}\", path: \"{}\"\n"),
				resource->Type.Name,
				state,
				formatMem(resource->DataSize.system),
				formatMem(resource->DataSize.graphical),
				resource->ReferenceCount,
				name,
				path
			);
			Logger::print(LogType::INFO, message.c_str());
		}
	}
#endif
}

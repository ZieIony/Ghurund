#include "ghcpch.h"
#include "ResourceCollection.h"

namespace Ghurund::Core {
	Resource* ResourceCollection::get(const FilePath& path) {
		std::unique_lock lock(mutex);
		auto iterator = resources.find(path);
		if (iterator != resources.end())
			return iterator->value.get();
		return nullptr;
	}

	void ResourceCollection::put(NotNull<Resource> resource) {
		std::unique_lock lock(mutex);
		// don't accept resources without a usable id
		_ASSERTE(resource->Path != nullptr);
		_ASSERTE(!resources.contains(*resource->Path));
		resource->addReference();
		resources.put(*resource->Path, IntrusivePointer(resource.get()));
	}

	void ResourceCollection::remove(NotNull<Resource> resource) {
		std::unique_lock lock(mutex);
#ifdef _DEBUG
		// don't accept resources without a usable id
		_ASSERTE(resource->Path);
#endif
		resources.remove(*resource->Path);
	}

	void ResourceCollection::remove(const FilePath& path) {
		std::unique_lock lock(mutex);

		auto iterator = resources.find(path);
		if (iterator != resources.end()) {
			// TODO: implement iterator.erase() or replace with std::map
			resources.remove(path);
		}
	}

	void ResourceCollection::clear() {
		std::unique_lock lock(mutex);
		resources.clear();
	}

#ifdef _DEBUG
	void ResourceCollection::validateResources() {
		std::unique_lock lock(mutex);
		for (auto& entry : resources) {
			_ASSERTE(entry.value != nullptr);
			_ASSERTE(entry.value->Path != nullptr);
			_ASSERTE(entry.value->Type.isOrExtends(Resource::TYPE));
		}
	}

	void ResourceCollection::printResources() {
		std::unique_lock lock(mutex);
		for (auto& entry : resources) {
			auto resource = entry.value.get();
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
				_T("type: {}, state: {}, size: s: {}, g: {}, refs: {}, path: \"{}\"\n"),
				resource->Type.Name,
				state,
				formatMem(resource->DataSize.system),
				formatMem(resource->DataSize.graphical),
				resource->ReferenceCount,
				path
			);
			Logger::print(LogType::INFO, message.c_str());
		}
	}
#endif
}

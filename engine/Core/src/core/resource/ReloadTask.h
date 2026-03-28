#pragma once

#include "Resource.h"

#include "core/loading/BaseLoader.h"

namespace Ghurund::Core {
	class ReloadTask {
	private:
		ResourceManager& resourceManager;
		BaseLoader& loader;
		Resource& resource;
		LoadOption loadOption;

	public:
		ReloadTask(ResourceManager& resourceManager, BaseLoader& loader, Resource& resource, LoadOption loadOption)
			:resourceManager(resourceManager), loader(loader), resource(resource), loadOption(loadOption) {
		}

		Resource& getResource() {
			return resource;
		}

		__declspec(property(get = getResource)) Resource& Resource;

		void execute() {
			//loader.load(resourceManager, stream, resource, loadOption);
		}
	};
}

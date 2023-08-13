#pragma once

#include "LayoutProvider.h"
#include "core/resource/ResourceManager.h"
#include "ui/control/Control.h"

namespace Ghurund::UI {
	class FileLayoutProvider:public LayoutProvider {
	private:
		Ghurund::Core::ResourceManager& resourceManager;
		ResourcePath path;

	public:
		FileLayoutProvider(
			Ghurund::Core::ResourceManager& resourceManager,
			const ResourcePath& path
		): resourceManager(resourceManager), path(path) {}

		virtual SharedPointer<Control> get() override {
			return SharedPointer<Control>(resourceManager.load<Control>(path, DirectoryPath(), nullptr, LoadOption::DONT_CACHE));
		}
	};
}
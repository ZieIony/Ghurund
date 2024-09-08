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

		virtual IntrusivePointer<Control> get() override {
			return IntrusivePointer<Control>(resourceManager.load<Control>(path, DirectoryPath(), ResourceFormat::AUTO, LoadOption::DONT_CACHE));
		}
	};
}
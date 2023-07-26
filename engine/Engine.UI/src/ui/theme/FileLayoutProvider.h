#pragma once

#include "LayoutProvider.h"
#include "core/resource/ResourceManager.h"
#include "ui/control/Control.h"

namespace Ghurund::UI {
	class FileLayoutProvider:public LayoutProvider {
	private:
		Ghurund::Core::ResourceManager& resourceManager;
		FilePath filePath;

	public:
		FileLayoutProvider(
			Ghurund::Core::ResourceManager& resourceManager,
			const FilePath& filePath
		): resourceManager(resourceManager), filePath(filePath) {}

		virtual Control* get() override {
			return resourceManager.load<Control>(filePath, nullptr, LoadOption::DONT_CACHE);
		}
	};
}
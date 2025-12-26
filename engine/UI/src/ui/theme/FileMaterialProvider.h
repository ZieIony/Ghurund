#pragma once

#include "MaterialProvider.h"

#include "core/resource/ResourceManager.h"

namespace Ghurund::UI {
	using namespace Ghurund::Engine;

	class FileMaterialProvider:public MaterialProvider {
	private:
		ResourceManager& resourceManager;
		FilePath resourcePath;
		IntrusivePointer<Material> cached;

	public:
		FileMaterialProvider(
			ResourceManager& resourceManager,
			const FilePath& resourcePath
		): resourceManager(resourceManager), resourcePath(resourcePath) {
		}

		virtual IntrusivePointer<Material> get() override {
			if (cached != nullptr)
				return IntrusivePointer<Material>((Material*)cached->clone());
			cached = IntrusivePointer<Material>(resourceManager.load<Material>(resourcePath));
			return cached;
		}
	};
}
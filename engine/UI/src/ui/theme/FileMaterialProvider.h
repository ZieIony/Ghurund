#pragma once

#include "MaterialProvider.h"

#include "core/resource/ResourceManager.h"

namespace Ghurund::UI {
	using namespace Ghurund::Engine;

	class FileMaterialProvider:public MaterialProvider {
	private:
		ResourceManager& resourceManager;
		ResourcePath resourcePath;
		IntrusivePointer<IMaterial> cached;

	public:
		FileMaterialProvider(
			ResourceManager& resourceManager,
			const ResourcePath& resourcePath
		): resourceManager(resourceManager), resourcePath(resourcePath) {
		}

		virtual IntrusivePointer<IMaterial> get() override {
			if (cached != nullptr)
				return IntrusivePointer<IMaterial>((IMaterial*)cached->clone());
			cached = IntrusivePointer<IMaterial>(resourceManager.load<IMaterial>(resourcePath));
			return cached;
		}
	};
}
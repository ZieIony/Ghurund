#pragma once

#include "MaterialProvider.h"

#include "core/resource/ResourceManager.h"

namespace Ghurund::UI {
	using namespace Ghurund::Engine;

	class FileMaterialProvider:public UIMaterialProvider {
	private:
		ResourceManager& resourceManager;
		FilePath resourcePath;
		IntrusivePointer<UIMaterial> cached;

	public:
		FileMaterialProvider(
			ResourceManager& resourceManager,
			const FilePath& resourcePath
		): resourceManager(resourceManager), resourcePath(resourcePath) {
		}

		virtual UIMaterial* get() override {
			if (cached != nullptr)
				return (UIMaterial*)cached->clone();
			auto coroutine = resourceManager.load<UIMaterial>(resourcePath);
			coroutine.resume();
			cached = coroutine.Result;
			return cached.get();
		}
	};
}
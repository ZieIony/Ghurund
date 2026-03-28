#pragma once

#include "UIMaterial.h"

#include "engine/graphics/material/MaterialLoader.h"

namespace Ghurund::UI {

	class UIMaterialLoader:public MaterialLoader {
	protected:
		virtual const Ghurund::Core::Type& getResourceType() const override {
			return UIMaterial::TYPE;
		}

		virtual void onLoadParameter(Material& material, const DirectoryPath& workingDir, MaterialInput& input, const AString& value) override;

	public:
		UIMaterialLoader(
			ResourceManager& resourceManager,
			IGPUMemoryManager& memoryManager
		):MaterialLoader(resourceManager, memoryManager) {
		}
	};
}

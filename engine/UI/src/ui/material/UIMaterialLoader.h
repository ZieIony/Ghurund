#pragma once

#include "UIMaterial.h"

#include "engine/graphics/material/MaterialLoader.h"
#include "engine/graphics/texture/ITextureFactory.h"

namespace Ghurund::UI {

	class UIMaterialLoader:public MaterialLoader {
	protected:
		virtual UIMaterial* makeMaterial() override;

		virtual void onLoadParameter(Material& material, const DirectoryPath& workingDir, MaterialInput& input, const AString& value) override;

	public:
		UIMaterialLoader(
			ResourceManager& resourceManager,
			ITextureFactory& textureFactory,
			IGPUMemoryManager& memoryManager
		):MaterialLoader(resourceManager, textureFactory, memoryManager) {
		}
	};
}
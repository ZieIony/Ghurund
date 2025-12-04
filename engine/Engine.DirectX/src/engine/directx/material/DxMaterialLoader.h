#pragma once

#include "engine/graphics/material/MaterialLoader.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class DxMaterialLoader:public MaterialLoader {
	protected:
        virtual Resource* loadInternal(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

        virtual void saveInternal(
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat& format,
            SaveOption options
        ) const override;

    public:
        DxMaterialLoader(
            ResourceManager& resourceManager,
            IMaterialFactory& materialFactory,
            ITextureFactory& textureFactory
        ):MaterialLoader(resourceManager, materialFactory, textureFactory) {
        }
    };
}
#pragma once

#include "engine/graphics/material/MaterialLoader.h"
#include <engine/directx/shader/DxShaderLoader.h>

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class DxMaterialLoader:public MaterialLoader {
	private:
        DxShaderLoader& shaderLoader;

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
        DxMaterialLoader(DxShaderLoader& shaderLoader):shaderLoader(shaderLoader) {}
	};
}
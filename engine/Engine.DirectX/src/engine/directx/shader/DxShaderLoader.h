#pragma once

#include "DxShader.h"
#include "DxShaderCompiler.h"
#include "core/resource/Loader.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class DxShaderLoader:public Loader {
	private:
        DxShaderCompiler* compiler;

		DxShader* loadShd(NotNull<MemoryInputStream> stream);
		DxShader* loadHlsl(NotNull<MemoryInputStream> stream);

    public:
        DxShaderLoader(NotNull<DxShaderCompiler> compiler):compiler(&compiler) {}

        virtual Resource* loadInternal(
            NotNull<MemoryInputStream> stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

        virtual void saveInternal(
            NotNull<MemoryOutputStream> stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat& format,
            SaveOption options
        ) const override;
	};
}
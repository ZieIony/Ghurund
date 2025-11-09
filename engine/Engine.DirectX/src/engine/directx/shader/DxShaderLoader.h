#pragma once

#include "DxShader.h"
#include "DxShaderCompiler.h"
#include "core/resource/Loader.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class DxShaderLoader:public Loader {
	private:
        DxShaderCompiler& compiler;

		DxShader* loadShd(MemoryInputStream& stream);
		DxShader* loadHlsl(MemoryInputStream& stream);

    public:
        DxShaderLoader(DxShaderCompiler& compiler):compiler(compiler) {}

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
	};
}
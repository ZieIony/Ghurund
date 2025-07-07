#pragma once

#include "Shader.h"
#include "ShaderCompiler.h"
#include "core/resource/Loader.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class ShaderLoader:public Loader {
	private:
        ShaderCompiler& compiler;

		Shader* loadShd(MemoryInputStream& stream);
		Shader* loadHlsl(MemoryInputStream& stream);

    public:
        ShaderLoader(ShaderCompiler& compiler):compiler(compiler) {}

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
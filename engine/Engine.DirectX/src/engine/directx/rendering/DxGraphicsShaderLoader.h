#pragma once

#include "core/loading/Loader.h"
#include "engine/directx/shader/compiler/DxShaderCompiler.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class DxGraphicsShaderLoader:public Loader<DxGraphicsShader> {
	private:
        ResourceManager& resourceManager;
        DxShaderCompiler& compiler;

        void loadFromSource(NotNull<ShaderSource> sourceCode, const DirectoryPath& workingDir, DxGraphicsShader& shader);
        void loadHlslFormat(const AString& sourceCode, const DirectoryPath& workingDir, DxGraphicsShader& shader);
        void loadXmlFormat(DxGraphicsShader& resource, const XMLElement& xml, const DirectoryPath& workingDir);

    protected:
        virtual CoroutineTask<void> loadInternal(
            DxGraphicsShader& resource,
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOptions options
        ) override;

        virtual CoroutineTask<void> loadInternal(
            DxGraphicsShader& resource,
            const XMLElement& xml,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOptions options
        ) override;

        virtual void saveInternal(
            DxGraphicsShader& resource,
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            SaveOptions options
        ) const override;

    public:
        List<DirectoryPath> includeDirs;

        DxGraphicsShaderLoader(ResourceManager& resourceManager, DxShaderCompiler& compiler):resourceManager(resourceManager), compiler(compiler) {}
	};
}

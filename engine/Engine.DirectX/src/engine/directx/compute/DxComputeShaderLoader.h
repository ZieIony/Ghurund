#pragma once

#include "core/loading/Loader.h"
#include "engine/directx/shader/compiler/DxShaderCompiler.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class DxComputeShaderLoader:public Loader<DxComputeShader> {
	private:
        ResourceManager& resourceManager;
        DxShaderCompiler& compiler;

        void loadFromSource(NotNull<ShaderSource> sourceCode, const DirectoryPath& workingDir, DxComputeShader& shader);
        void loadHlslFormat(const AString& sourceCode, const DirectoryPath& workingDir, DxComputeShader& shader);
        void loadXmlFormat(DxComputeShader& resource, const XMLElement& xml, const DirectoryPath& workingDir);

    protected:
        virtual CoroutineTask<void> loadInternal(
            DxComputeShader& resource,
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOptions options
        ) override;

        virtual CoroutineTask<void> loadInternal(
            DxComputeShader& resource,
            const XMLElement& xml,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOptions options
        ) override;

        virtual void saveInternal(
            DxComputeShader& resource,
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            SaveOptions options
        ) const override;

    public:
        List<DirectoryPath> includeDirs;

        DxComputeShaderLoader(ResourceManager& resourceManager, DxShaderCompiler& compiler):resourceManager(resourceManager), compiler(compiler) {}
	};
}

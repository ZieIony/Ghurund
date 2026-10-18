#pragma once

#include "core/loading/Loader.h"
#include "engine/directx/shader/compiler/DxShaderCompiler.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class DxGraphicsShaderLoader:public Loader<DxGraphicsShader> {
	private:
        ResourceManager& resourceManager;
        DxShaderCompiler& compiler;

        void initialize(DxGraphicsShader& shader, const DirectoryPath& workingDir);
        void loadHlslFormat(DxGraphicsShader& shader, const AString& sourceCode, const DirectoryPath& workingDir);
        void loadXmlFormat(DxGraphicsShader& shader, const XMLElement& xml, const DirectoryPath& workingDir);

    protected:
        virtual CoroutineTask<void> load_internal(
            DxGraphicsShader& resource,
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOptions options
        ) override;

        virtual CoroutineTask<void> load_internal(
            DxGraphicsShader& resource,
            const XMLElement& xml,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOptions options
        ) override;

        virtual void save_internal(
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

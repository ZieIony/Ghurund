#pragma once

#include "DxShader.h"

#include "core/loading/Loader.h"
#include "core/xml/XMLDocument.h"
#include "compiler/DxShaderCompiler.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

    struct DxShaderProgramSourceCode:public ShaderProgramSourceCode {
        DxShaderType type = DxShaderType::VERTEX;
        AString entryPoint;

        DxShaderProgramSourceCode(
            DxShaderType type,
            const AString& entryPoint,
            const AString& sourceCode
        ):ShaderProgramSourceCode(sourceCode), type(type), entryPoint(entryPoint) {}
    };

	class DxShaderLoader:public Loader<DxShader> {
	private:
        ResourceManager& resourceManager;
        DxShaderCompiler& compiler;

        void loadFromSource(NotNull<ShaderSource> sourceCode, const DirectoryPath& workingDir, DxShader& shader);
        void loadFromHlsl(const AString& sourceCode, const DirectoryPath& workingDir, DxShader& shader);

    protected:
        virtual CoroutineTask<void> loadInternal(
            DxShader& resource,
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

        virtual CoroutineTask<void> loadInternal(
            DxShader& resource,
            const XMLElement& xml,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

        virtual void saveInternal(
            DxShader& resource,
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            SaveOption options
        ) const override;

    public:
        List<DirectoryPath> includeDirs;

        DxShaderLoader(ResourceManager& resourceManager, DxShaderCompiler& compiler):resourceManager(resourceManager), compiler(compiler) {}
	};
}
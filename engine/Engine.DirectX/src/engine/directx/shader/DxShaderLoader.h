#pragma once

#include "DxShader.h"

#include "core/loading/Loader.h"
#include "compiler/DxShaderCompiler.h"

#include <tinyxml2.h>

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

	class DxShaderLoader:public Loader {
	private:
        ResourceManager& resourceManager;
        DxShaderCompiler& compiler;

        DxShader* loadFromSource(NotNull<ShaderSource> sourceCode, const DirectoryPath& workingDir);
		DxShader* loadFromXml(const tinyxml2::XMLElement& xml, const DirectoryPath& workingDir);
		DxShader* loadFromHlsl(const AString& sourceCode, const DirectoryPath& workingDir);

    public:
        List<DirectoryPath> includeDirs;

        DxShaderLoader(ResourceManager& resourceManager, DxShaderCompiler& compiler):resourceManager(resourceManager), compiler(compiler) {}

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
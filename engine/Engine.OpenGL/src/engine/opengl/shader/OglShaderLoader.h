#pragma once

#include "OglShader.h"
#include "OglShaderCompiler.h"
#include "core/resource/Loader.h"

namespace tinyxml2 {
    class XMLElement;
}

namespace Ghurund::Engine::OpenGL {
	using namespace Ghurund::Core;

	class OglShaderLoader:public Loader {
	private:
        OglShaderCompiler& compiler;

        SharedPointer<OglShaderProgram> loadShaderProgramFromXml(
            const tinyxml2::XMLElement& xml,
            const DirectoryPath& workingDir,
            const OglShaderType& shaderType
        );

        OglShader* loadXml(
            const tinyxml2::XMLElement& xml,
            const DirectoryPath& workingDir
        );

    public:
        OglShaderLoader(OglShaderCompiler& compiler):compiler(compiler) {}

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
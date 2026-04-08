#pragma once

#include "OglShader.h"
#include "OglShaderCompiler.h"

#include "core/loading/Loader.h"

namespace Ghurund::Engine::OpenGL {
	using namespace Ghurund::Core;

	class OglShaderLoader:public Loader<OglShader> {
	private:
        OglShaderCompiler& compiler;

        SharedPointer<OglShaderProgram> loadShaderProgramFromXml(
            const XMLElement& xml,
            const DirectoryPath& workingDir,
            const OglShaderType& shaderType
        );

    public:
        OglShaderLoader(OglShaderCompiler& compiler):compiler(compiler) {}

        virtual CoroutineTask<void> loadInternal(
            OglShader& resource,
            const XMLElement& xml,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

        virtual void saveInternal(
            OglShader& resource,
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            SaveOption options
        ) const override;
	};
}

#include "ghedxpch.h"
#include "ShaderLoader.h"
#include "CompilerInclude.h"

namespace Ghurund::Engine::DirectX {
	Shader* ShaderLoader::loadShd(NotNull<MemoryInputStream> stream) {
		//readHeader(stream);

		/*if (stream.readBoolean()) {
			for (size_t i = 0; i < 6; i++) {
				if (stream.readBoolean()) {
					AString entryPoint = stream.readASCII();
					const CompilationTarget& target = CompilationTarget::fromValue(stream.readInt());
					unsigned int length = stream.readUInt32();
					Buffer byteCode = Buffer(stream.readBytes(length), length);
					programs[i] = ghnew ShaderProgram(ShaderType::values[i], byteCode, entryPoint, target);
				}
			}
		}

		if (stream.readBoolean())
			setSourceCode(stream.readASCII());

		supportsTransparency = stream.readBoolean();
		 Graphics& graphics = context.Graphics;
		 initConstants(context.ParameterManager);
		 if ((result = makeRootSignature()) != Status::OK)
			 return result;
		 if ((result = makePipelineState(supportsTransparency)) != Status::OK)
			 return result;*/

			 // return Status::OK;
		throw NotImplementedException();
	}

	Shader* ShaderLoader::loadHlsl(NotNull<MemoryInputStream> stream) {
		AString sourceCode((const char*)stream->Data, stream->Size);

		DirectoryPath workingDir;
		CompilerInclude include(workingDir, DirectoryPath(L"./shaders/"));
		List<SharedPointer<ShaderProgram>> programs;
		for (const ShaderType& shaderType : ShaderType::VALUES) {
			try {
				auto program = SharedPointer<ShaderProgram>(compiler.compile(sourceCode, shaderType, include));
				programs.add(program);
			} catch (...) {}
		}
		auto array = Array<SharedPointer<ShaderProgram>>(programs);
		auto shader = compiler.build(programs);
		//bool supportsTransparency = sourceCode.find("supportsTransparency") != sourceCode.Size;

		return &shader;
	}

	Resource* ShaderLoader::loadInternal(
		NotNull<MemoryInputStream> stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		try {
			return loadHlsl(stream);
		} catch (...) {
			throw InvalidFormatException();
		}
	}

	void ShaderLoader::saveInternal(
		NotNull<MemoryOutputStream> stream,
		const DirectoryPath& workingDir,
		Resource& resource,
		const ResourceFormat& format,
		SaveOption options
	) const {
		Shader& shader = castResource<Shader>(resource);

		writeHeader<Shader>(stream);

		//stream.writeASCII(shader.sourceCode);
	}
}

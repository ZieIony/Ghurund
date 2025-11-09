#include "ghedxpch.h"
#include "DxShaderLoader.h"
#include "CompilerInclude.h"

namespace Ghurund::Engine::DirectX {
	DxShader* DxShaderLoader::loadShd(MemoryInputStream& stream) {
		//readHeader(stream);

		/*if (stream.readBoolean()) {
			for (size_t i = 0; i < 6; i++) {
				if (stream.readBoolean()) {
					AString entryPoint = stream.readASCII();
					const CompilationTarget& target = CompilationTarget::fromValue(stream.readInt());
					unsigned int length = stream.readUInt32();
					Buffer byteCode = Buffer(stream.readBytes(length), length);
					programs[i] = ghnew DxShaderProgram(DxShaderType::values[i], byteCode, entryPoint, target);
				}
			}
		}

		if (stream.readBoolean())
			setSourceCode(stream.readASCII());

		isTransparencyEnabled = stream.readBoolean();
		 Graphics& graphics = context.Graphics;
		 initConstants(context.ParameterManager);
		 if ((result = makeRootSignature()) != Status::OK)
			 return result;
		 if ((result = makePipelineState(isTransparencyEnabled)) != Status::OK)
			 return result;*/

			 // return Status::OK;
		throw NotImplementedException();
	}

	DxShader* DxShaderLoader::loadHlsl(MemoryInputStream& stream) {
		AString sourceCode((const char*)stream.Data, stream.Size);

		DirectoryPath workingDir;
		// TODO: load any includes
		CompilerInclude include(workingDir, DirectoryPath(L"./resources/shaders/DirectX/"));
		List<SharedPointer<DxShaderProgram>> programs;
		for (const DxShaderType& shaderType : DxShaderType::VALUES) {
			try {
				auto program = SharedPointer<DxShaderProgram>(compiler.compile(sourceCode, shaderType, &include));
				programs.add(program);
			} catch (...) {}
		}
		auto array = Array<SharedPointer<DxShaderProgram>>(programs);
		bool isTransparencyEnabled = sourceCode.find("#define transparencyEnabled") != sourceCode.Size;
		auto shader = compiler.build(programs, isTransparencyEnabled);

		return shader.reset();
	}

	Resource* DxShaderLoader::loadInternal(
		MemoryInputStream& stream,
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

	void DxShaderLoader::saveInternal(
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		Resource& resource,
		const ResourceFormat& format,
		SaveOption options
	) const {
		DxShader& shader = castResource<DxShader>(resource);

		writeHeader<DxShader>(stream);

		//stream.writeASCII(shader.sourceCode);
	}
}

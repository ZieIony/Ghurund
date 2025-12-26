#include "ghedxpch.h"
#include "DxShaderLoader.h"

#include "compiler/CompilerInclude.h"
#include "compiler/DxShaderProgram.h"
#include "compiler/DxEntrypointNotFoundException.h"

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

	DxShader* DxShaderLoader::loadHlsl(MemoryInputStream& stream, const DirectoryPath& workingDir) {
		AString sourceCode((const char*)stream.Data, stream.Size);

		CompilerInclude include(resourceManager, workingDir, includeDirs);
		List<SharedPointer<DxShaderProgram>> programs;
		for (const DxShaderType& shaderType : DxShaderType::VALUES) {
			auto program = SharedPointer<DxShaderProgram>(compiler.compile(sourceCode, shaderType, &include));
			if (program == nullptr) {
				if (shaderType == DxShaderType::VERTEX) {
					Logger::log(LogType::ERR0R, _T("Vertex shader program is required.\n"));
					throw DxEntrypointNotFoundException(DxShaderType::VERTEX);
				} else if (shaderType == DxShaderType::PIXEL) {
					Logger::log(LogType::ERR0R, _T("Pixel shader program is required.\n"));
					throw DxEntrypointNotFoundException(DxShaderType::PIXEL);
				}
			} else {
				programs.add(program);
			}
		}
		auto array = Array<SharedPointer<DxShaderProgram>>(programs);
		bool isTransparencyEnabled = sourceCode.find("#define transparencyEnabled true") != sourceCode.Size;
		bool isDepthTestEnabled = sourceCode.find("#define depthTestEnabled false") == sourceCode.Size;
		D3D12_CULL_MODE cullMode = [&] {
			if (sourceCode.find("#define cullMode CULL_MODE_NONE") != sourceCode.Size) {
				return D3D12_CULL_MODE_NONE;
			} else if (sourceCode.find("#define cullMode CULL_MODE_FRONT") != sourceCode.Size) {
				return D3D12_CULL_MODE_FRONT;
			} else {
				return D3D12_CULL_MODE_BACK;
			}
		}();
		auto shader = compiler.build(programs, { isTransparencyEnabled, cullMode, isDepthTestEnabled });

		return shader.reset();
	}

	Resource* DxShaderLoader::loadInternal(
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		try {
			return loadHlsl(stream, workingDir);
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

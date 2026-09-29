#include "ghedxpch.h"
#include "DxComputeShaderLoader.h"

#include "engine/directx/shader/compiler/DxEntrypointNotFoundException.h"

namespace Ghurund::Engine::DirectX {
	CoroutineTask<void> DxComputeShaderLoader::loadInternal(
		DxComputeShader& resource,
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOptions options
	) {
		checkXmlRoot(xml, L"ComputeShader");
	
		auto shaderSource = makeIntrusive<ShaderSource>();
		//auto settingsElement = xml.findElement(L"Settings");
		auto samplersElement = xml.findElement(L"Samplers");
		if (samplersElement) {
			for (auto& samplerElement : samplersElement->children) {
				SamplerInfo sampler;
				auto samplerNameAttribute = samplerElement->findAttribute(L"name");
				if (samplerNameAttribute)
					sampler.name = convertText<wchar_t, char>(*samplerNameAttribute);
				auto samplerFilterAttribute = samplerElement->findAttribute(L"filter");
				if (samplerFilterAttribute) {
					auto filterValue = *samplerFilterAttribute;
					if (filterValue == L"point") {
						sampler.filter = TextureFilter::POINT;
					} else if (filterValue == L"linear") {
						sampler.filter = TextureFilter::LINEAR;
					} else if (filterValue == L"anisotropic") {
						sampler.filter = TextureFilter::ANISOTROPIC;
					}
				}
				shaderSource->samplers.add(sampler);
			}
		}
		auto programElement = xml.findElement(L"Program");
		if (!programElement) {
			Logger::logAndThrow<InvalidDataException>(_T("Missing required 'Program' node.\n"));
		}

		AString entryPoint = [&]->AString {
			auto entryPointAttribute = programElement->findAttribute(L"entryPoint");
			if (entryPointAttribute) {
				return convertText<wchar_t, char>(*entryPointAttribute);
			} else {
				return DxShaderType::COMPUTE.EntryPoint;
			}
		}();
		FilePath path = [&] {
			auto pathAttribute = programElement->findAttribute(L"path");
			if (pathAttribute) {
				return FilePath(*pathAttribute);
			} else {
				Logger::logAndThrow<InvalidDataException>(_T("Missing program path for compute program.\n"));
			}
		}();
		AString sourceCode = [&] {
			auto absolutePath = resourceManager.getAbsoluteOrLibPath(path, workingDir);
			auto buffer = resourceManager.resolveResource(absolutePath);
			return AString((const char*)buffer->Data, buffer->Size);
		}();
		AString sourceName = [&] {
			auto sourceNameAttribute = programElement->findAttribute(L"sourceName");
			if (sourceNameAttribute) {
				return convertText<wchar_t, char>(*sourceNameAttribute);
			} else {
				if (path.IsAbsolute || path.IsLibrary) {
					return convertText<wchar_t, char>(path.toString());
				} else if (resource.Path != nullptr) {
					if (resource.Path->IsAbsolute || resource.Path->IsLibrary) {
						auto absolutePath = resourceManager.getAbsoluteOrLibPath(path, resource.Path->Directory);
						return convertText<wchar_t, char>(absolutePath.toString());
					} else {
						auto absoluteResourcePath = resourceManager.getAbsoluteOrLibPath(*resource.Path, workingDir);
						auto absolutePath = resourceManager.getAbsoluteOrLibPath(path, absoluteResourcePath.Directory);
						return convertText<wchar_t, char>(absolutePath.toString());
					}
				} else {
					return AString("[unnamed shader]");
				}
			}
		}();
		shaderSource->programs.add(ghnew DxShaderProgramSourceCode(DxShaderType::COMPUTE, sourceCode, sourceName));
		loadFromSource(shaderSource.ref(), workingDir, resource);
		co_return;
	}

	void DxComputeShaderLoader::loadFromSource(NotNull<ShaderSource> shaderSource, const DirectoryPath& workingDir, DxComputeShader& shader) {
		DxShaderProgramSourceCode* computeShaderSource = (DxShaderProgramSourceCode*)shaderSource->programs[0];
		if(computeShaderSource->shaderType != DxShaderType::COMPUTE) {
			Logger::log(LogType::ERR0R, _T("Compute shader program is required.\n"));
			throw DxEntrypointNotFoundException(DxShaderType::COMPUTE);
		}
		CompilerInclude include(resourceManager, workingDir, includeDirs);
		auto computeProgram = SharedPointer<DxShaderProgram>(compiler.compile(*computeShaderSource, &include));
		compiler.build(shader, computeProgram.ref(), shaderSource->samplers);
		shader.validate();
	}

	void DxComputeShaderLoader::loadFromHlsl(const AString& sourceCode, const DirectoryPath& workingDir, DxComputeShader& shader) {
		auto shaderSource = makeIntrusive<ShaderSource>();

		AString entryPoint = DxShaderType::COMPUTE.EntryPoint;
		if (sourceCode.contains(entryPoint)) {
			// TODO: fix shader.Path name
			AString sourceName = shader.Path ? convertText<wchar_t, char>(shader.Path->toString()) : AString("[unnamed shader]");
			shaderSource->programs.add(ghnew DxShaderProgramSourceCode(DxShaderType::COMPUTE, sourceCode, sourceName));
		}

		loadFromSource(shaderSource.ref(), workingDir, shader);
	}

	CoroutineTask<void> DxComputeShaderLoader::loadInternal(
		DxComputeShader& resource,
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOptions options
	) {
		auto position = stream.Position;
		try {
			co_await loadFromXml(resource, stream, workingDir, format, options);
		} catch(...) {
			stream.Position = position;
			AString streamContents = stream.readASCII();
			loadFromHlsl(streamContents, workingDir, resource);
		}
	}

	void DxComputeShaderLoader::saveInternal(
		DxComputeShader& resource,
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		SaveOptions options
	) const {
		writeHeader<DxComputeShader>(stream);

		//stream.writeASCII(shader.sourceCode);
	}
}

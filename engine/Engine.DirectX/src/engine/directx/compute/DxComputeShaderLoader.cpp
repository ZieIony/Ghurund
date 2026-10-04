#include "ghedxpch.h"
#include "DxComputeShaderLoader.h"

#include "engine/directx/shader/compiler/DxEntrypointNotFoundException.h"

namespace Ghurund::Engine::DirectX {
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

	void DxComputeShaderLoader::loadHlslFormat(const AString& sourceCode, const DirectoryPath& workingDir, DxComputeShader& shader) {
		auto shaderSource = makeIntrusive<ShaderSource>();

		AString entryPoint = DxShaderType::COMPUTE.EntryPoint;
		if (sourceCode.contains(entryPoint)) {
			// TODO: fix shader.Path name
			AString sourceName = shader.Path ? convertText<wchar_t, char>(shader.Path->toString()) : AString("[unnamed shader]");
			shaderSource->programs.add(ghnew DxShaderProgramSourceCode(DxShaderType::COMPUTE, sourceCode, sourceName));
		}

		loadFromSource(shaderSource.ref(), workingDir, shader);
	}

	void DxComputeShaderLoader::loadXmlFormat(DxComputeShader& resource, const XMLElement& xml, const DirectoryPath& workingDir) {
		checkXmlRoot(xml, L"ComputeShader", DxComputeShader::FORMAT_XML);

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
		auto programElement = xml.requireElement(L"Program");

		AString entryPoint = [&]->AString {
			auto entryPointAttribute = programElement.findAttribute(L"entryPoint");
			if (entryPointAttribute) {
				return convertText<wchar_t, char>(*entryPointAttribute);
			} else {
				return DxShaderType::COMPUTE.EntryPoint;
			}
		}();
		FilePath path = FilePath(programElement.requireAttribute(L"path"));
		AString sourceCode = [&] {
			auto absolutePath = resourceManager.getAbsoluteOrLibPath(path, workingDir);
			auto buffer = resourceManager.resolveResource(absolutePath);
			return AString((const char*)buffer->Data, buffer->Size);
		}();
		AString sourceName = [&] {
			auto sourceNameAttribute = programElement.findAttribute(L"sourceName");
			if (sourceNameAttribute) {
				return convertText<wchar_t, char>(*sourceNameAttribute);
			} else {
				if (path.IsAbsolute || path.IsLibrary) {
					return convertText<wchar_t, char>(path.toString());
				} else if (resource.Path != nullptr) {
					if (resource.Path->IsAbsolute || resource.Path->IsLibrary) {
						auto absoluteOrLibPath = resourceManager.resolvePath(resourceManager.getAbsoluteOrLibPath(path, resource.Path->Directory));
						return convertText<wchar_t, char>(absoluteOrLibPath.toString());
					} else {
						auto absoluteOrLibResourcePath = resourceManager.getAbsoluteOrLibPath(*resource.Path, workingDir);
						auto absoluteOrLibPath = resourceManager.resolvePath(resourceManager.getAbsoluteOrLibPath(path, absoluteOrLibResourcePath.Directory));
						return convertText<wchar_t, char>(absoluteOrLibPath.toString());
					}
				} else {
					return AString("[unnamed shader]");
				}
			}
		}();
		shaderSource->programs.add(ghnew DxShaderProgramSourceCode(DxShaderType::COMPUTE, sourceCode, sourceName));
		loadFromSource(shaderSource.ref(), workingDir, resource);
	}

	CoroutineTask<void> DxComputeShaderLoader::loadInternal(
		DxComputeShader& resource,
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOptions options
	) {
		auto position = stream.Position;
		if (format == DxComputeShader::FORMAT_XML) {
			co_await loadFromXml(resource, stream, workingDir, format, options);
		} else if (format == DxComputeShader::FORMAT_HLSL) {
			AString streamContents = stream.readAString();
			loadHlslFormat(streamContents, workingDir, resource);
		} else if (format == ResourceFormat::AUTO) {
			try {
				co_await loadFromXml(resource, stream, workingDir, DxComputeShader::FORMAT_XML, options);
			} catch (...) {
				stream.Position = position;
				AString streamContents = stream.readAString();
				loadHlslFormat(streamContents, workingDir, resource);
			}
		}
	}

	CoroutineTask<void> DxComputeShaderLoader::loadInternal(
		DxComputeShader& resource,
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOptions options) {
		loadXmlFormat(resource, xml, workingDir);
		co_return;
	}

	void DxComputeShaderLoader::saveInternal(
		DxComputeShader& resource,
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		SaveOptions options
	) const {
		throw NotImplementedException();
		//writeHeader<DxComputeShader>(stream, format);

		//stream.writeASCII(shader.sourceCode);
	}
}

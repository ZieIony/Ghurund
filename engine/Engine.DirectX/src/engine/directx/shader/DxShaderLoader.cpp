#include "ghedxpch.h"
#include "DxShaderLoader.h"

#include "core/xml/XMLDocument.h"
#include "compiler/CompilerInclude.h"
#include "compiler/DxShaderProgram.h"
#include "compiler/DxEntrypointNotFoundException.h"

namespace Ghurund::Engine::DirectX {
	CoroutineTask<void> DxShaderLoader::loadInternal(
		DxShader& resource,
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOptions options
	) {
		checkXmlRoot(xml, L"Shader");
	
		auto shaderSource = makeIntrusive<ShaderSource>();
		auto settingsElementIndex = xml.children.find([](const SharedPointer<XMLElement>& element) { return element->name == L"Settings"; });
		if (settingsElementIndex != xml.children.Size) {
			auto& settingsElement = xml.children[settingsElementIndex];
			auto cullModeAttribute= settingsElement->findAttribute(L"cullMode");
			if (cullModeAttribute) {
				auto cullModeValue = *cullModeAttribute;
				if (cullModeValue == L"none") {
					shaderSource->settings.cullMode = D3D12_CULL_MODE::D3D12_CULL_MODE_NONE;
				} else if (cullModeValue == L"front") {
					shaderSource->settings.cullMode = D3D12_CULL_MODE::D3D12_CULL_MODE_FRONT;
				} else if (cullModeValue == L"back") {
					shaderSource->settings.cullMode = D3D12_CULL_MODE::D3D12_CULL_MODE_BACK;
				}
			}
			auto transparencyAttribute = settingsElement->findAttribute(L"isTransparencyEnabled");
			if (transparencyAttribute)
				shaderSource->settings.isTransparencyEnabled = *transparencyAttribute == L"true";
			auto depthTestAttribute = settingsElement->findAttribute(L"isDepthTestEnabled");
			if (depthTestAttribute)
				shaderSource->settings.isDepthTestEnabled = *depthTestAttribute == L"true";
			auto depthWriteAttribute = settingsElement->findAttribute(L"isDepthWriteEnabled");
			if (depthWriteAttribute)
				shaderSource->settings.isDepthWriteEnabled = *depthTestAttribute == L"true";
			auto depthFuncAttribute = settingsElement->findAttribute(L"depthFunc");
			if (depthFuncAttribute) {
				auto depthFuncValue = *depthFuncAttribute;
				if (depthFuncValue == L"never") {
					shaderSource->settings.depthFunc = D3D12_COMPARISON_FUNC_NEVER;
				} else if (depthFuncValue == L"always") {
					shaderSource->settings.depthFunc = D3D12_COMPARISON_FUNC_ALWAYS;
				} else if (depthFuncValue == L"less") {
					shaderSource->settings.depthFunc = D3D12_COMPARISON_FUNC_LESS;
				} else if (depthFuncValue == L"greater") {
					shaderSource->settings.depthFunc = D3D12_COMPARISON_FUNC_GREATER;
				}
			}
		}
		auto samplersElementIndex = xml.children.find([](const SharedPointer<XMLElement>& element) { return element->name == L"Samplers"; });
		if (samplersElementIndex != xml.children.Size) {
			auto& samplersElement = xml.children[samplersElementIndex];
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
		auto programsElementIndex = xml.children.find([](const SharedPointer<XMLElement>& element) { return element->name == L"Programs"; });
		if (programsElementIndex != xml.children.Size) {
			auto& programsElement = xml.children[programsElementIndex];
			for (auto& programElement : programsElement->children) {
				DxShaderType type = [&] {
					auto programTypeAttribute = programElement->findAttribute(L"type");
					if (programTypeAttribute) {
						auto programType = convertText<wchar_t, char>(*programTypeAttribute);
						try {
							return DxShaderType::fromName(programType.toUpperCase());
						} catch (std::invalid_argument e) {
							auto message = std::format("Invalid program type '{}'.", programType);
							throw InvalidDataException(message.c_str());
						}
					} else {
						throw InvalidDataException("Missing program type.");
					}
				}();
				AString entryPoint = [&]->AString {
					auto entryPointAttribute = programElement->findAttribute(L"entryPoint");
					if (entryPointAttribute) {
						return convertText<wchar_t, char>(*entryPointAttribute);
					} else {
						return type.EntryPoint;
					}
				}();
				FilePath path = [&] {
					auto pathAttribute = programElement->findAttribute(L"path");
					if (pathAttribute) {
						return FilePath(*pathAttribute);
					} else {
						auto message = std::format("Missing program path for program type '{}'.", type.Name);
						throw InvalidDataException(message.c_str());
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
				shaderSource->programs.add(ghnew DxShaderProgramSourceCode(type, sourceCode, sourceName));
			}
		}
		loadFromSource(shaderSource.ref(), workingDir, resource);
		co_return;
	}

	void DxShaderLoader::loadFromSource(NotNull<ShaderSource> shaderSource, const DirectoryPath& workingDir, DxShader& shader) {
		if (!shaderSource->programs.any([](auto& program) { return ((DxShaderProgramSourceCode*)program)->shaderType == DxShaderType::VERTEX; })) {
			Logger::log(LogType::ERR0R, _T("Vertex shader program is required.\n"));
			throw DxEntrypointNotFoundException(DxShaderType::VERTEX);
		}
		if (!shaderSource->programs.any([](auto& program) { return ((DxShaderProgramSourceCode*)program)->shaderType == DxShaderType::PIXEL; })) {
			Logger::log(LogType::ERR0R, _T("Pixel shader program is required.\n"));
			throw DxEntrypointNotFoundException(DxShaderType::PIXEL);
		}
		CompilerInclude include(resourceManager, workingDir, includeDirs);
		List<SharedPointer<DxShaderProgram>> programs;
		for (auto sourceCode : shaderSource->programs) {
			auto dxSourceCode = (DxShaderProgramSourceCode*)sourceCode;
			auto program = SharedPointer<DxShaderProgram>(compiler.compile(*dxSourceCode, &include));
			programs.add(program);
		}
		auto array = Array<SharedPointer<DxShaderProgram>>(programs);
		compiler.build(shader, programs, shaderSource->samplers, shaderSource->settings);
		shader.validate();
	}

	void DxShaderLoader::loadFromHlsl(const AString& sourceCode, const DirectoryPath& workingDir, DxShader& shader) {
		auto shaderSource = makeIntrusive<ShaderSource>();

		for (const DxShaderType& shaderType : DxShaderType::VALUES) {
			AString entryPoint = shaderType.getEntryPoint();
			if (sourceCode.contains(entryPoint)) {
				AString sourceName = shader.Path ? convertText<wchar_t, char>(shader.Path->toString()) : AString("[unnamed shader]");
				shaderSource->programs.add(ghnew DxShaderProgramSourceCode(shaderType, sourceCode, sourceName));
			}
		}

		loadFromSource(shaderSource.ref() , workingDir, shader);
	}

	CoroutineTask<void> DxShaderLoader::loadInternal(
		DxShader& resource,
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

	void DxShaderLoader::saveInternal(
		DxShader& resource,
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		SaveOptions options
	) const {
		writeHeader<DxShader>(stream);

		//stream.writeASCII(shader.sourceCode);
	}
}

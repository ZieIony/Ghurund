#include "ghedxpch.h"
#include "DxGraphicsShaderLoader.h"

#include "engine/directx/shader/compiler/DxEntrypointNotFoundException.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	void DxGraphicsShaderLoader::loadXmlFormat(
		DxGraphicsShader& shader,
		const XMLElement& xml,
		const DirectoryPath& workingDir
	) {
		checkXmlRoot(xml, L"GraphicsShader", DxGraphicsShader::FORMAT_XML);

		List<ShaderProgramSourceCode*> sources;
		VertexShaderSettings vsSettings;
		PixelShaderSettings psSettings;
		auto settingsElementIndex = xml.children.find([](const SharedPointer<XMLElement>& element) { return element->name == L"Settings"; });
		if (settingsElementIndex != xml.children.Size) {
			auto& settingsElement = xml.children[settingsElementIndex];
			auto cullModeAttribute = settingsElement->findAttribute(L"cullMode");
			if (cullModeAttribute)
				vsSettings.cullMode = parse<CullMode>(*cullModeAttribute);
			auto transparencyAttribute = settingsElement->findAttribute(L"isTransparencyEnabled");
			if (transparencyAttribute)
				psSettings.isTransparencyEnabled = *transparencyAttribute == L"true";
			auto depthTestAttribute = settingsElement->findAttribute(L"isDepthTestEnabled");
			if (depthTestAttribute)
				vsSettings.isDepthTestEnabled = *depthTestAttribute == L"true";
			auto depthWriteAttribute = settingsElement->findAttribute(L"isDepthWriteEnabled");
			if (depthWriteAttribute)
				vsSettings.isDepthWriteEnabled = *depthTestAttribute == L"true";
			auto depthFuncAttribute = settingsElement->findAttribute(L"depthFunc");
			if (depthFuncAttribute)
				vsSettings.depthFunc = parse<ComparisonFunc>(*depthFuncAttribute);
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
				FilePath path = FilePath(programElement->requireAttribute(L"path"));
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
						} else if (shader.Path != nullptr) {
							if (shader.Path->IsAbsolute || shader.Path->IsLibrary) {
								auto absoluteOrLibPath = resourceManager.resolvePath(resourceManager.getAbsoluteOrLibPath(path, shader.Path->Directory));
								return convertText<wchar_t, char>(absoluteOrLibPath.toString());
							} else {
								auto absoluteOrLibResourcePath = resourceManager.getAbsoluteOrLibPath(*shader.Path, workingDir);
								auto absoluteOrLibPath = resourceManager.resolvePath(resourceManager.getAbsoluteOrLibPath(path, absoluteOrLibResourcePath.Directory));
								return convertText<wchar_t, char>(absoluteOrLibPath.toString());
							}
						} else {
							return AString("[unnamed shader]");
						}
					}
				}();
				DxShaderProgramSourceCode* source = [&]->DxShaderProgramSourceCode* {
					if (type == DxShaderType::VERTEX) {
						return ghnew DxVertexShaderProgramSourceCode(sourceCode, sourceName, vsSettings);
					}else if (type == DxShaderType::PIXEL) {
						return ghnew DxPixelShaderProgramSourceCode(sourceCode, sourceName, psSettings);
					} else {
						return ghnew DxShaderProgramSourceCode(type, sourceCode, sourceName);
					}
				}();
				auto samplersElement = programElement->findElement(L"Samplers");
				if (samplersElement) {
					for (auto& samplerElement : samplersElement->children) {
						SamplerInfo sampler;
						auto samplerNameAttribute = samplerElement->findAttribute(L"name");
						if (samplerNameAttribute)
							sampler.name = convertText<wchar_t, char>(*samplerNameAttribute);
						auto samplerFilterAttribute = samplerElement->findAttribute(L"filter");
						if (samplerFilterAttribute)
							sampler.filter = parse<TextureFilter>(*samplerFilterAttribute);
						source->samplers.add(sampler);
					}
				}
				sources.add(source);
			}
		}

		shader.Sources = sources;
		initialize(shader, workingDir);
	}

	CoroutineTask<void> DxGraphicsShaderLoader::load_internal(
		DxGraphicsShader& resource,
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOptions options
	) {
		loadXmlFormat(resource, xml, workingDir);
		co_return;
	}

	void DxGraphicsShaderLoader::initialize(DxGraphicsShader& shader, const DirectoryPath& workingDir) {
		List<ShaderProgramSourceCode*> sources = shader.Sources;
		if (!shader.Sources.any([](auto& program) { return ((DxShaderProgramSourceCode*)program)->shaderType == DxShaderType::VERTEX; })) {
			auto index = fallback.get()->Sources.find([](auto& program) { return ((DxShaderProgramSourceCode*)program)->shaderType == DxShaderType::VERTEX; });
			if (index != fallback.get()->Sources.Size) {
				sources.add(fallback.get()->Sources[index]);
			} else {
				Logger::log(LogType::ERR0R, _T("Vertex shader program is required.\n"));
				throw DxEntrypointNotFoundException(DxShaderType::VERTEX);
			}
		}
		if (!shader.Sources.any([](auto& program) { return ((DxShaderProgramSourceCode*)program)->shaderType == DxShaderType::PIXEL; })) {
			auto index = fallback.get()->Sources.find([](auto& program) { return ((DxShaderProgramSourceCode*)program)->shaderType == DxShaderType::PIXEL; });
			if (index != fallback.get()->Sources.Size) {
				sources.add(fallback.get()->Sources[index]);
			} else {
				Logger::log(LogType::ERR0R, _T("Pixel shader program is required.\n"));
				throw DxEntrypointNotFoundException(DxShaderType::PIXEL);
			}
		}
		List<SharedPointer<DxShaderProgram>> programs;
		for (auto sourceCode : shader.Sources) {
			auto dxSourceCode = (DxShaderProgramSourceCode*)sourceCode;
			auto program = SharedPointer<DxShaderProgram>(compiler.compile(*dxSourceCode, workingDir, &includeDirs));
			if (program->Type == DxShaderType::VERTEX) {
				((DxVertexShaderProgram*)program.get())->settings = ((DxVertexShaderProgramSourceCode*)sourceCode)->settings;
			} else if (program->Type == DxShaderType::PIXEL) {
				((DxPixelShaderProgram*)program.get())->settings = ((DxPixelShaderProgramSourceCode*)sourceCode)->settings;
			}
			programs.add(program);
		}
		compiler.build(shader, programs);
	}

	void DxGraphicsShaderLoader::loadHlslFormat(DxGraphicsShader& shader, const AString& sourceCode, const DirectoryPath& workingDir) {
		List<ShaderProgramSourceCode*> sources;

		for (const DxShaderType& shaderType : DxShaderType::VALUES) {
			AString entryPoint = shaderType.getEntryPoint();
			if (sourceCode.contains(entryPoint)) {
				// TODO: fix shader.Path name
				AString sourceName = shader.Path ? convertText<wchar_t, char>(shader.Path->toString()) : AString("[unnamed shader]");
				sources.add(ghnew DxShaderProgramSourceCode(shaderType, sourceCode, sourceName));
			}
		}

		shader.Sources = sources;
		initialize(shader, workingDir);
	}

	CoroutineTask<void> DxGraphicsShaderLoader::load_internal(
		DxGraphicsShader& resource,
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOptions options
	) {
		auto position = stream.Position;
		if (format == DxGraphicsShader::FORMAT_XML) {
			co_await loadFromXml(resource, stream, workingDir, format, options);
		} else if (format == DxGraphicsShader::FORMAT_HLSL) {
			AString streamContents = stream.readAString();
			loadHlslFormat(resource, streamContents, workingDir);
		} else if (format == ResourceFormat::AUTO) {
			try {
				co_await loadFromXml(resource, stream, workingDir, DxGraphicsShader::FORMAT_XML, options);
			} catch (...) {
				stream.Position = position;
				AString streamContents = stream.readAString();
				loadHlslFormat(resource, streamContents, workingDir);
			}
		}
	}

	void DxGraphicsShaderLoader::save_internal(
		DxGraphicsShader& resource,
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		SaveOptions options
	) const {
		throw NotImplementedException();
		//writeHeader<DxGraphicsShader>(stream, format);

		//stream.writeASCII(shader.sourceCode);
	}
}

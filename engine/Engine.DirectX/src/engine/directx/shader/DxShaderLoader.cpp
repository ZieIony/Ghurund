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
		LoadOption options
	) {
		checkXmlRoot(xml, L"Shader");
	
		auto shaderSource = makeIntrusive<ShaderSource>();
		auto settingsElementIndex = xml.children.find([](const SharedPointer<XMLElement>& element) { return element->name == L"Settings"; });
		if (settingsElementIndex != xml.children.Size) {
			auto& settingsElement = xml.children[settingsElementIndex];
			auto cullModeAttributeIterator = settingsElement->attributes.find(L"cullMode");
			if (cullModeAttributeIterator != settingsElement->attributes.end()) {
				auto& cullModeValue = cullModeAttributeIterator->value;
				if (cullModeValue == L"none") {
					shaderSource->settings.cullMode = CullMode::NONE;
				} else if (cullModeValue == L"front") {
					shaderSource->settings.cullMode = CullMode::FRONT;
				} else if (cullModeValue == L"back") {
					shaderSource->settings.cullMode = CullMode::BACK;
				}
			}
			auto transparencyAttributeIterator = settingsElement->attributes.find(L"isTransparencyEnabled");
			if (transparencyAttributeIterator != settingsElement->attributes.end())
				shaderSource->settings.isTransparencyEnabled = transparencyAttributeIterator->value == L"true";
			auto depthTestAttributeIterator = settingsElement->attributes.find(L"isDepthTestEnabled");
			if (depthTestAttributeIterator != settingsElement->attributes.end())
				shaderSource->settings.isDepthTestEnabled = depthTestAttributeIterator->value == L"true";
		}
		auto samplersElementIndex = xml.children.find([](const SharedPointer<XMLElement>& element) { return element->name == L"Samplers"; });
		if (samplersElementIndex != xml.children.Size) {
			auto& samplersElement = xml.children[samplersElementIndex];
			for (auto& samplerElement : samplersElement->children) {
				SamplerInfo sampler;
				auto samplerNameAttributeIterator = samplerElement->attributes.find(L"name");
				if (samplerNameAttributeIterator != samplerElement->attributes.end())
					sampler.name = convertText<wchar_t, char>(samplerNameAttributeIterator->value);
				auto samplerFilterAttributeIterator = samplerElement->attributes.find(L"filter");
				if (samplerFilterAttributeIterator != samplerElement->attributes.end()) {
					auto& filterValue = samplerFilterAttributeIterator->value;
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
					auto programTypeAttributeIterator = programElement->attributes.find(L"type");
					if (programTypeAttributeIterator != programElement->attributes.end()) {
						auto programType = convertText<wchar_t, char>(programTypeAttributeIterator->value);
						try {
							return DxShaderType::fromName(programType.toUpperCase());
						} catch (InvalidParamException e) {
							auto message = std::format("Invalid program type '{}'.", programType);
							throw InvalidDataException(message.c_str());
						}
					} else {
						throw InvalidDataException("Missing program type.");
					}
				}();
				AString entryPoint = [&]->AString {
					auto entryPointAttributeIterator = programElement->attributes.find(L"entryPoint");
					if (entryPointAttributeIterator != programElement->attributes.end()) {
						return convertText<wchar_t, char>(entryPointAttributeIterator->value);
					} else {
						return type.EntryPoint;
					}
				}();
				AString sourceCode = [&] {
					auto pathAttributeIterator = programElement->attributes.find(L"path");
					if (pathAttributeIterator != programElement->attributes.end()) {
						auto path = FilePath(pathAttributeIterator->value);
						auto buffer = resourceManager.resolveResource(path, workingDir);
						return AString((const char*)buffer->Data, buffer->Size);
					} else {
						auto message = std::format("Missing program path for program type '{}'.", type.Name);
						throw InvalidDataException(message.c_str());
					}
				}();
				shaderSource->programs.add(ghnew DxShaderProgramSourceCode(type, entryPoint, sourceCode));
			}
		}
		loadFromSource(shaderSource.ref(), workingDir, resource);
		co_return;
	}

	void DxShaderLoader::loadFromSource(NotNull<ShaderSource> shaderSource, const DirectoryPath& workingDir, DxShader& shader) {
		if (!shaderSource->programs.any([](auto& program) { return ((DxShaderProgramSourceCode*)program)->type == DxShaderType::VERTEX; })) {
			Logger::log(LogType::ERR0R, _T("Vertex shader program is required.\n"));
			throw DxEntrypointNotFoundException(DxShaderType::VERTEX);
		}
		if (!shaderSource->programs.any([](auto& program) { return ((DxShaderProgramSourceCode*)program)->type == DxShaderType::PIXEL; })) {
			Logger::log(LogType::ERR0R, _T("Pixel shader program is required.\n"));
			throw DxEntrypointNotFoundException(DxShaderType::PIXEL);
		}
		CompilerInclude include(resourceManager, workingDir, includeDirs);
		List<SharedPointer<DxShaderProgram>> programs;
		for (auto sourceCode : shaderSource->programs) {
			auto dxSourceCode = (DxShaderProgramSourceCode*)sourceCode;
			auto program = SharedPointer<DxShaderProgram>(compiler.compile(dxSourceCode->sourceCode, dxSourceCode->entryPoint, dxSourceCode->type, &include));
			programs.add(program);
		}
		auto array = Array<SharedPointer<DxShaderProgram>>(programs);
		compiler.build(shader, programs, shaderSource->samplers, shaderSource->settings);
	}

	void DxShaderLoader::loadFromHlsl(const AString& sourceCode, const DirectoryPath& workingDir, DxShader& shader) {
		auto shaderSource = makeIntrusive<ShaderSource>();

		for (const DxShaderType& shaderType : DxShaderType::VALUES) {
			AString entryPoint = shaderType.getEntryPoint();
			if (sourceCode.contains(entryPoint))
				shaderSource->programs.add(ghnew DxShaderProgramSourceCode(shaderType, entryPoint, sourceCode));
		}

		loadFromSource(shaderSource.ref() , workingDir, shader);
	}

	CoroutineTask<void> DxShaderLoader::loadInternal(
		DxShader& resource,
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		auto position = stream.Position;
		try {
			co_await loadFromXml(resource, stream, workingDir, format, options);
		} catch(...) {
			stream.Position = position;
			AString streamContents = stream.readASCII();
			loadFromHlsl(streamContents, workingDir, resource);
		}
		co_return;
	}

	void DxShaderLoader::saveInternal(
		DxShader& resource,
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		SaveOption options
	) const {
		writeHeader<DxShader>(stream);

		//stream.writeASCII(shader.sourceCode);
	}
}

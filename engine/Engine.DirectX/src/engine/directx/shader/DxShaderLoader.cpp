#include "ghedxpch.h"
#include "DxShaderLoader.h"

#include "compiler/CompilerInclude.h"
#include "compiler/DxShaderProgram.h"
#include "compiler/DxEntrypointNotFoundException.h"
#include <tinyxml2.h>

namespace Ghurund::Engine::DirectX {
	DxShader* DxShaderLoader::loadFromXml(const tinyxml2::XMLElement& xml, const DirectoryPath& workingDir) {
		if (AString(xml.Name()) != "Shader")
			throw InvalidFormatException();

		auto shaderSource = makeIntrusive<ShaderSource>();
		auto settingsElement = xml.FirstChildElement("Settings");
		if (settingsElement) {
			auto cullModeAttribute = settingsElement->FindAttribute("cullMode");
			if (cullModeAttribute) {
				auto cullModeValue = AString(cullModeAttribute->Value());
				if (cullModeValue == "none") {
					shaderSource->settings.cullMode = CullMode::NONE;
				} else if (cullModeValue == "front") {
					shaderSource->settings.cullMode = CullMode::FRONT;
				} else if (cullModeValue == "back") {
					shaderSource->settings.cullMode = CullMode::BACK;
				}
			}
			auto transparencyAttribute = settingsElement->FindAttribute("isTransparencyEnabled");
			if (transparencyAttribute)
				shaderSource->settings.isTransparencyEnabled = transparencyAttribute->BoolValue();
			auto depthTestAttribute = settingsElement->FindAttribute("isDepthTestEnabled");
			if (depthTestAttribute)
				shaderSource->settings.isDepthTestEnabled = depthTestAttribute->BoolValue();
		}
		auto samplersElement = xml.FirstChildElement("Samplers");
		if (samplersElement) {
			auto samplerElement = samplersElement->FirstChildElement();
			while (samplerElement) {
				SamplerInfo sampler;
				auto samplerNameAttribute = samplerElement->FindAttribute("name");
				if (samplerNameAttribute)
					sampler.name = samplerNameAttribute->Value();
				auto samplerFilterAttribute = samplerElement->FindAttribute("filter");
				if (samplerFilterAttribute) {
					auto filterValue = AString(samplerFilterAttribute->Value());
					if (filterValue == "point") {
						sampler.filter = TextureFilter::POINT;
					} else if (filterValue == "linear") {
						sampler.filter = TextureFilter::LINEAR;
					} else if (filterValue == "anisotropic") {
						sampler.filter = TextureFilter::ANISOTROPIC;
					}
				}
				shaderSource->samplers.add(sampler);
				samplerElement = samplerElement->NextSiblingElement();
			}
		}
		auto programsElement = xml.FirstChildElement("Programs");
		if (programsElement) {
			auto programElement = programsElement->FirstChildElement();
			while (programElement) {
				DxShaderType type = [&] {
					auto programTypeAttribute = programElement->FindAttribute("type");
					if (programTypeAttribute) {
						auto programType = AString(programTypeAttribute->Value());
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
					auto entryPointAttribute = programElement->FindAttribute("entryPoint");
					if (entryPointAttribute) {
						return entryPointAttribute->Value();
					} else {
						return type.EntryPoint;
					}
				}();
				AString sourceCode = [&] {
					auto pathAttribute = programElement->FindAttribute("path");
					if (pathAttribute) {
						auto path = FilePath(convertText<char, wchar_t>(AString(pathAttribute->Value())));
						auto buffer = resourceManager.resolveResource(path, workingDir);
						return AString((const char*)buffer->Data, buffer->Size);
					} else {
						auto message = std::format("Missing program path for program type '{}'.", type.Name);
						throw InvalidDataException(message.c_str());
					}
				}();
				shaderSource->programs.add(ghnew DxShaderProgramSourceCode(type, entryPoint, sourceCode));
				programElement = programElement->NextSiblingElement();
			}
		}
		return loadFromSource(shaderSource.ref(), workingDir);
	}

	DxShader* DxShaderLoader::loadFromSource(NotNull<ShaderSource> shaderSource, const DirectoryPath& workingDir) {
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
		auto shader = compiler.build(programs, shaderSource->samplers, shaderSource->settings);

		return shader.reset();
	}

	DxShader* DxShaderLoader::loadFromHlsl(const AString& sourceCode, const DirectoryPath& workingDir) {
		auto shaderSource = makeIntrusive<ShaderSource>();

		for (const DxShaderType& shaderType : DxShaderType::VALUES) {
			AString entryPoint = shaderType.getEntryPoint();
			if (sourceCode.contains(entryPoint))
				shaderSource->programs.add(ghnew DxShaderProgramSourceCode(shaderType, entryPoint, sourceCode));
		}

		return loadFromSource(shaderSource.ref() , workingDir);
	}

	Resource* DxShaderLoader::loadInternal(
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		AString streamContents = stream.readASCII();
		tinyxml2::XMLDocument document;
		document.Parse(streamContents.Data);
		const tinyxml2::XMLElement* root = document.RootElement();
		if (root) {
			return loadFromXml(*root, workingDir);
		} else {
			return loadFromHlsl(streamContents, workingDir);
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

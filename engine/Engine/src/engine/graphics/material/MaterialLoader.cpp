#include "ghepch.h"
#include "MaterialLoader.h"

#include "core/Color.h"
#include "engine/graphics/cubemap/ICubeMap.h"
#include "CubeMapInput.h"

namespace Ghurund::Engine {
	CoroutineTask<void> MaterialLoader::onLoadParameter(Material& material, const DirectoryPath& workingDir, MaterialInput& input, const AString& value) {
		if (input.Type == InputType::TEXTURE) {
			TextureInput& textureInput = (TextureInput&)input;
			FilePath texturePath = FilePath(convertText<char, wchar_t>(value));
			auto texture = co_await resourceManager.load<ITexture>(texturePath, workingDir);
			textureInput.Value = texture.get();
		} else if (input.Type == InputType::CUBEMAP) {
			CubeMapInput& cubeMapInput = (CubeMapInput&)input;
			FilePath cubeMapPath = FilePath(convertText<char, wchar_t>(value));
			auto cubeMap = co_await resourceManager.load<ICubeMap>(cubeMapPath, workingDir);
			cubeMapInput.Value = cubeMap.get();
		} else if (input.Type == InputType::FLOAT4) {
			Float4Input& float4Input = (Float4Input&)input;
			// TODO: load theme attributes or do binding
			if (value.startsWith("#"))
				float4Input.Value = Color::parse(value).toFloat4();
		}
		co_return;
	}

	CoroutineTask<void> MaterialLoader::loadXmlFormat(
		Material& resource,
		const XMLElement& xml,
		const DirectoryPath& workingDir
	) {
		checkXmlRoot(xml, L"Material", Material::FORMAT_XML);

		WString shaderPathAttribute = xml.requireAttribute(L"shader");
		FilePath path = FilePath(shaderPathAttribute);
		auto shader = co_await resourceManager.load<GraphicsShader>(path, workingDir);
		resource.init(memoryManager);
		resource.Shader = shader.get();
		for (const auto& child : xml.children) {
			if (child->name == L"Parameter") {
				auto nameAttribute = child->findAttribute(L"name");
				auto valueAttribute = child->findAttribute(L"value");
				if (nameAttribute && valueAttribute) {
					AString name = convertText<wchar_t, char>(*nameAttribute);
					auto input = resource.getInputs().get(name);
					if (!input) {
						auto text = std::format(_T("Shader {} doesn't specify an input named '{}'\n"), path.toString(), convertText<char, tchar>(name));
						Logger::log(LogType::WARNING, text.c_str());
					} else {
						AString value = convertText<wchar_t, char>(*valueAttribute);
						co_await onLoadParameter(resource, workingDir, *input, value);
					}
				}
			}
		}
	}

	CoroutineTask<void> MaterialLoader::loadInternal(
		Material& resource,
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOptions options
	) {
		if (format == Material::FORMAT_XML) {
			co_await loadXmlFormat(resource, xml, workingDir);
		} else if (format == ResourceFormat::AUTO) {
			co_await loadXmlFormat(resource, xml, workingDir);
		}
	}

	void MaterialLoader::saveInternal(
		Material& resource,
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		SaveOptions options
	) const {
		//shaderLoader.save(stream, workingDir, *material.Shader, format, options);
	}
}

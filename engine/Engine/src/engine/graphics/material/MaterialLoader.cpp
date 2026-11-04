#include "ghepch.h"
#include "MaterialLoader.h"

#include "core/Color.h"
#include "engine/graphics/cubemap/ICubeMap.h"
#include "CubeMapInput.h"
#include <engine/graphics/rendering/GraphicsShader.h>

namespace Ghurund::Engine {
	CoroutineTask<void> MaterialLoader::onLoadParameter(Material& material, const DirectoryPath& workingDir, MaterialInput& input, const AString& value) {
		if (input.Type == ConstantType::TEXTURE) {
			TextureInput& textureInput = (TextureInput&)input;
			FilePath texturePath = FilePath(convertText<char, wchar_t>(value));
			auto texture = co_await resourceManager.load<ITexture>(texturePath, workingDir);
			textureInput.Value = texture.get();
		} else if (input.Type == ConstantType::CUBEMAP) {
			CubeMapInput& cubeMapInput = (CubeMapInput&)input;
			FilePath cubeMapPath = FilePath(convertText<char, wchar_t>(value));
			auto cubeMap = co_await resourceManager.load<ICubeMap>(cubeMapPath, workingDir);
			cubeMapInput.Value = cubeMap.get();
		} else if (input.Type == ConstantType::FLOAT4) {
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

		auto shadersElement = xml.requireElement(L"Shaders");
		for (auto& shaderElement : shadersElement.children) {
			WString shaderVariantAttribute = shaderElement->requireAttribute(L"variant");
			MaterialVariantType variant = parse<MaterialVariantType>(shaderVariantAttribute);
			WString shaderPathAttribute = shaderElement->requireAttribute(L"path");
			FilePath path = FilePath(shaderPathAttribute);
			auto shader = co_await resourceManager.load<GraphicsShader>(path, workingDir);
			for (const auto& child : shaderElement->children) {
				if (child->name == L"Parameter") {
					auto nameAttribute = child->findAttribute(L"name");
					auto valueAttribute = child->findAttribute(L"value");
					if (nameAttribute && valueAttribute) {
						AString name = convertText<wchar_t, char>(*nameAttribute);
						auto input = shader->Inputs.get(name);
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
			resource.setShader(variant, shader.get());
		}
		for (size_t i = 0; i < (size_t)MaterialVariantType::NUM_VARIANTS; i++) {
			if (resource.getShader((MaterialVariantType)i) == nullptr)
				resource.setShader((MaterialVariantType)i, defaultMaterial->getShader((MaterialVariantType)i));
		}
	}

	CoroutineTask<void> MaterialLoader::load_internal(
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

	void MaterialLoader::save_internal(
		Material& resource,
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		SaveOptions options
	) const {
		//shaderLoader.save(stream, workingDir, *material.Shader, format, options);
	}
}

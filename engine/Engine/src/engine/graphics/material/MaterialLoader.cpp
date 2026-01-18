#include "ghepch.h"
#include "MaterialLoader.h"

#include "core/image/Image.h"

#include <tinyxml2.h>

namespace Ghurund::Engine {
	Material* MaterialLoader::makeMaterial() {
		return ghnew Material(memoryManager);
	}

	void MaterialLoader::onLoadParameter(Material& material, const DirectoryPath& workingDir, MaterialInput& input, const AString& value) {
		if (input.Type == InputType::TEXTURE) {
			TextureInput& textureInput = (TextureInput&)input;
			FilePath texturePath = FilePath(convertText<char, wchar_t>(value));
			auto image = IntrusivePointer<Image>(resourceManager.load<Image>(texturePath, workingDir));
			auto texture = IntrusivePointer<ITexture>(textureFactory.makeTexture(image.ref()));
			textureInput.Value = texture.get();
		} else if (input.Type == InputType::FLOAT4) {
			Float4Input& float4Input = (Float4Input&)input;
			// TODO: load theme attributes or do binding
			if (value.startsWith("#"))
				float4Input.Value = Color::parse(value).toVector();
		}
	}

	Material* MaterialLoader::loadFromXml(const tinyxml2::XMLElement& xml, const DirectoryPath& workingDir) {
		AString s = xml.FindAttribute("shader")->Value();
		FilePath path = FilePath(convertText<char, wchar_t>(s));
		auto shader = IntrusivePointer<Shader>(resourceManager.load<Shader>(path, workingDir, ResourceFormat::AUTO, LoadOption::DONT_CACHE));
		auto material = IntrusivePointer<Material>(makeMaterial());
		material->Shader = shader.get();
		const tinyxml2::XMLElement* child = xml.FirstChildElement();
		while (child) {
			if (child->Name() == AString("Parameter")) {
				auto nameAttribute = child->FindAttribute("name");
				auto valueAttribute = child->FindAttribute("value");
				if (nameAttribute && valueAttribute) {
					AString name = nameAttribute->Value();
					auto input = material->getInputs().get(name);
					if (!input) {
						auto text = std::format(_T("Shader {} doesn't specify an input named '{}'\n"), path.toString(), convertText<char, tchar>(name));
						Logger::log(LogType::WARNING, text.c_str());
					} else {
						onLoadParameter(material.ref(), workingDir, *input, valueAttribute->Value());
					}
				}
			}
			child = child->NextSiblingElement();
		}
		material->addReference();
		return material.get();
	}

	Resource* MaterialLoader::loadInternal(
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		tinyxml2::XMLDocument doc;
		doc.Parse((const char*)stream.Data, stream.Size);
		tinyxml2::XMLElement* xml = doc.RootElement();
		if (AString("Material") != xml->Name())
			throw InvalidFormatException();

		return loadFromXml(*xml, workingDir);
	}

	void MaterialLoader::saveInternal(
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		Resource& resource,
		const ResourceFormat& format,
		SaveOption options
	) const {
		auto& material = castResource<Material>(resource);
		//shaderLoader.save(stream, workingDir, *material.Shader, format, options);
	}
}
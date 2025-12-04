#include "ghepch.h"
#include "MaterialLoader.h"

#include <engine/parameter/TextureParameter.h>
#include <engine/parameter/ValueParameter.h>

#include <tinyxml2.h>
#include <core/image/Image.h>

namespace Ghurund::Engine {

	IMaterial* MaterialLoader::loadFromXml(const tinyxml2::XMLElement& xml, const DirectoryPath& workingDir) {
		AString s = xml.FindAttribute("shader")->Value();
		s.replace(L'\\', L'/');
		ResourcePath path = ResourcePath::parse(convertText<char, wchar_t>(s));
		auto shader = IntrusivePointer<IShader>(resourceManager.load<IShader>(path, workingDir, ResourceFormat::AUTO, LoadOption::DONT_CACHE));
		auto material = IntrusivePointer<IMaterial>(materialFactory.makeMaterial(shader.get()));
		const tinyxml2::XMLElement* child = xml.FirstChildElement();
		while (child) {
			if (child->Name() == AString("Parameter")) {
				auto nameAttribute = child->FindAttribute("name");
				auto valueAttribute = child->FindAttribute("value");
				if (nameAttribute && valueAttribute) {
					auto parameter = material->Parameters.get(nameAttribute->Value());
					if (parameter->Type == TextureParameter::TYPE) {
						TextureParameter* typedParameter = (TextureParameter*)parameter;
						ResourcePath texturePath = ResourcePath::parse(convertText<char, wchar_t>(AString(valueAttribute->Value())));
						auto image = IntrusivePointer<Image>(resourceManager.load<Image>(texturePath, workingDir));
						auto texture = IntrusivePointer<ITexture>(textureFactory.makeTexture(image.ref()));
						typedParameter->Value = texture.get();
					} else if (parameter->Type == Float4Parameter::TYPE) {
						Float4Parameter* typedParameter = (Float4Parameter*)parameter;
						if (AString(valueAttribute->Value()).startsWith("#")) {
							typedParameter->Value = Color::parse(valueAttribute->Value()).toVector();
						}
					}
				}
			}
			child = child->NextSiblingElement();
		}
		material->addReference();
		return material.get();
	}
}
#include "ghuipch.h"
#include "MaterialPropertyLoader.h"

#include "core/resource/ResourceManager.h"
#include <engine/graphics/shader/IShader.h>
#include "engine/parameter/TextureParameter.h"
#include "engine/parameter/ValueParameter.h"

namespace Ghurund::UI {
	void MaterialPropertyLoader::loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const {
		AString s = text;
		s.replace(L'\\', L'/');
		ResourcePath path = ResourcePath::parse(convertText<char, wchar_t>(s));
		IntrusivePointer<IMaterial> material = IntrusivePointer<IMaterial>(resourceManager.load<IMaterial>(path, workingDir, ResourceFormat::AUTO, LoadOption::DONT_CACHE));
		IMaterial* m = material.get();
		property.setRaw(&obj, &m);
	}

	void MaterialPropertyLoader::loadElement(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) const {
		AString s = xml.FindAttribute("shader")->Value();
		s.replace(L'\\', L'/');
		ResourcePath path = ResourcePath::parse(convertText<char, wchar_t>(s));
		IntrusivePointer<IShader> shader = IntrusivePointer<IShader>(resourceManager.load<IShader>(path, workingDir, ResourceFormat::AUTO, LoadOption::DONT_CACHE));
		IntrusivePointer<IMaterial> material = IntrusivePointer<IMaterial>(materialFactory.makeMaterial(shader.get()));
		const tinyxml2::XMLElement* child = xml.FirstChildElement();
		while (child) {
			if (child->Name() != AString("Parameter"))
				continue;
			auto nameAttribute = child->FindAttribute("name");
			auto valueAttribute = child->FindAttribute("value");
			if (nameAttribute && valueAttribute) {
				auto parameter = material->Parameters.get(nameAttribute->Value());
				if (parameter->Type == TextureParameter::TYPE) {

				} else if(parameter->Type == Float4Parameter::TYPE){
					Float4Parameter* typedParameter = (Float4Parameter*)parameter;
					if (AString(valueAttribute->Value()).startsWith("#")) {
						typedParameter->Value = Color::parse(valueAttribute->Value()).toVector();
					}
				}
			}
			child = child->NextSiblingElement();
		}
		IMaterial* m = material.get();
		property.setRaw(&obj, &m);
	}
}
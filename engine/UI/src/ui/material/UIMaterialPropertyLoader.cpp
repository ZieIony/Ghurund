#include "ghuipch.h"
#include "UIMaterialPropertyLoader.h"

#include "core/resource/ResourceManager.h"

namespace Ghurund::UI {
	void UIMaterialPropertyLoader::loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const {
		AString s = text;
		std::unique_ptr<ThemedMaterial> themedMaterial;
		if (s.startsWith(THEME_MATERIAL)) {
			MaterialKey key = s.substring(lengthOf(THEME_MATERIAL));
			themedMaterial.reset(ghnew ThemedMaterial(key));
		} else {
			FilePath path = FilePath(convertText<char, wchar_t>(s));
			auto material = IntrusivePointer<UIMaterial>(resourceManager.load<UIMaterial>(path, workingDir, ResourceFormat::AUTO, LoadOption::DONT_CACHE));
			themedMaterial.reset(ghnew ThemedMaterial(material.get()));
		}
		property.setRaw(&obj, &themedMaterial);
	}

	void UIMaterialPropertyLoader::loadElement(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) const {
		auto material = IntrusivePointer<UIMaterial>((UIMaterial*)materialLoader.loadFromXml(xml, workingDir));
		std::unique_ptr<ThemedMaterial> themedMaterial = std::make_unique<ThemedMaterial>(material.get());
		property.setRaw(&obj, &themedMaterial);
	}
}
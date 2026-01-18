#include "ghuipch.h"
#include "UIMaterialPropertyLoader.h"

#include "core/resource/ResourceManager.h"

namespace Ghurund::UI {
	void UIMaterialPropertyLoader::loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const {
		AString s = text;
		FilePath path = FilePath(convertText<char, wchar_t>(s));
		auto material = IntrusivePointer<UIMaterial>(resourceManager.load<UIMaterial>(path, workingDir, ResourceFormat::AUTO, LoadOption::DONT_CACHE));
		UIMaterial* m = material.get();
		property.setRaw(&obj, &m);
	}

	void UIMaterialPropertyLoader::loadElement(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) const {
		auto material = IntrusivePointer<Material>(materialLoader.loadFromXml(xml, workingDir));
		Material* m = material.get();
		property.setRaw(&obj, &m);
	}
}
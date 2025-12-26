#include "ghuipch.h"
#include "MaterialPropertyLoader.h"

#include "core/resource/ResourceManager.h"

namespace Ghurund::UI {
	void MaterialPropertyLoader::loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const {
		AString s = text;
		FilePath path = FilePath(convertText<char, wchar_t>(s));
		IntrusivePointer<Material> material = IntrusivePointer<Material>(resourceManager.load<Material>(path, workingDir, ResourceFormat::AUTO, LoadOption::DONT_CACHE));
		Material* m = material.get();
		property.setRaw(&obj, &m);
	}

	void MaterialPropertyLoader::loadElement(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) const {
		auto material = IntrusivePointer<Material>(materialLoader.loadFromXml(xml, workingDir));
		Material* m = material.get();
		property.setRaw(&obj, &m);
	}
}
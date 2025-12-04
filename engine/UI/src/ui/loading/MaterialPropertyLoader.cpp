#include "ghuipch.h"
#include "MaterialPropertyLoader.h"

#include "core/resource/ResourceManager.h"

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
		auto material = IntrusivePointer<IMaterial>(materialLoader.loadFromXml(xml, workingDir));
		IMaterial* m = material.get();
		property.setRaw(&obj, &m);
	}
}
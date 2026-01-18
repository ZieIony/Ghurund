#include "ghuipch.h"
#include "UIMaterialLoader.h"

namespace Ghurund::UI {
	static inline const char* THEME_COLOR = "theme://color/";
	
	UIMaterial* UIMaterialLoader::makeMaterial() {
		return ghnew UIMaterial(memoryManager);
	}

	void UIMaterialLoader::onLoadParameter(Material& material, const DirectoryPath& workingDir, MaterialInput& input, const AString& value) {
		if (value.startsWith("theme://")) {
			UIMaterial& uiMaterial = (UIMaterial&)material;
			uiMaterial.themeParameters.add({ input.Name, value.substring(lengthOf(THEME_COLOR)), ThemeParameterType::COLOR });
		} else {
			__super::onLoadParameter(material, workingDir, input, value);
		}
	}
}
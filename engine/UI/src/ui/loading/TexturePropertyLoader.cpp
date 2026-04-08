#include "ghuipch.h"
#include "TexturePropertyLoader.h"

#include "ui/theme/Theme.h"

namespace Ghurund::UI {
	void TexturePropertyLoader::loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const {
		AString s = text;
		s.replace(L'\\', L'/');
		std::unique_ptr<ThemedTexture> themedTexture;
		if (s.startsWith(THEME_TEXTURE)) {
			TextureKey imageKey = s.substring(lengthOf(THEME_TEXTURE));
			themedTexture.reset(ghnew ThemedTexture(imageKey));
		} else {
			FilePath path = FilePath(convertText<char, wchar_t>(s));
			auto coroutine = resourceManager.load<ITexture>(path, workingDir);
			coroutine.resume();
			auto texture = coroutine.Result;
			themedTexture.reset(ghnew ThemedTexture(texture));
		}
		//if (!themedTexture)
			//themedTexture.reset(ghnew TextureValue(ghnew InvalidImageTexture()));
		property.setRaw(&obj, &themedTexture);
	}
}
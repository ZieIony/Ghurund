#include "ghuipch.h"
#include "TexturePropertyLoader.h"

#include "ui/style/TextureAttr.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {
	void TexturePropertyLoader::loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const {
		AString s = text;
		s.replace(L'\\', L'/');
		std::unique_ptr<TextureAttr> attr;
		if (s.startsWith(THEME_TEXTURE)) {
			TextureKey imageKey = s.substring(lengthOf(THEME_TEXTURE));
			attr.reset(ghnew TextureRef(imageKey));
		} else {
			FilePath path = FilePath(convertText<char, wchar_t>(s));
			auto image = IntrusivePointer<Image>(resourceManager.load<Image>(path, workingDir));
			ITexture* texture = textureFactory.makeTexture(image.ref());
			attr.reset(ghnew TextureValue(texture));
			texture->release();
		}
		//if (!attr)
			//attr.reset(ghnew TextureValue(ghnew InvalidImageTexture()));
		property.setRaw(&obj, &attr);
	}
}
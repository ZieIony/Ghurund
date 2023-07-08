#include "ghuipch.h"
#include "DrawablePropertyLoader.h"

#include "ui/drawable/InvalidImageDrawable.h"
#include "ui/style/DrawableAttr.h"
#include <ui/style/Theme.h>

namespace Ghurund::UI {
	void DrawablePropertyLoader::loadAttr(Object& obj, const BaseProperty& property, const AString& text) const {
		AString s = text;
		s.replace(L'\\', L'/');
		std::unique_ptr<DrawableAttr> attr;
		if (s.startsWith(THEME_DRAWABLE)) {
			DrawableKey imageKey = s.substring(lengthOf(THEME_DRAWABLE));
			attr.reset(ghnew DrawableRef(imageKey));
		} else {
			FilePath path = convertText<char, wchar_t>(s);
			ImageDrawable* drawable = drawableFactory.makeDrawable(path);
			attr.reset(ghnew DrawableValue(drawable));
			drawable->release();
		}
		if (!attr)
			attr.reset(ghnew DrawableValue(ghnew InvalidImageDrawable()));
		property.setRaw(&obj, &attr);
	}
}
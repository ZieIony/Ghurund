#include "ghuipch.h"
#include "DrawablePropertyLoader.h"

#include "ui/drawable/InvalidImageDrawable.h"

namespace Ghurund::UI {
    void DrawablePropertyLoader::loadAttr(Object& obj, const BaseProperty& property, const AString& text) const {
        AString s = text;
        s.replace(L'\\', L'/');
        ImageDrawable* drawable = [&]() {
            /*if (s.startsWith(THEME_IMAGE) && theme) {
            ImageKey imageKey = s.substring(lengthOf(THEME_IMAGE));
            if (theme->Images.containsKey(imageKey)) {
            ImageDrawable* drawable = (ImageDrawable*)theme->Images[imageKey]->clone();
            property.setRaw(&obj, &drawable);
            }
            } else {*/
            FilePath path = convertText<char, wchar_t>(s);
            return drawableFactory.makeDrawable(path);
            //}
        }();
        if (!drawable)
            drawable = ghnew InvalidImageDrawable();
        property.setRaw(&obj, &drawable);
        drawable->release();
    }
}
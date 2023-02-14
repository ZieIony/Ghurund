#pragma once

#include "PropertyLoader.h"
#include "ui/loading/ImageDrawableFactory.h"
#include "ui/drawable/InvalidImageDrawable.h"

namespace Ghurund::UI {
    class DrawablePropertyLoader:public PropertyLoader {
    private:
        static inline const char* THEME_IMAGE = "theme://image/";

        ImageDrawableFactory& drawableFactory;

    public:
        DrawablePropertyLoader(ImageDrawableFactory& drawableFactory):drawableFactory(drawableFactory) {}

        virtual const Type& getType() const override {
            return Ghurund::Core::getType<Drawable*>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const AString& text) const override {
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
    };
}
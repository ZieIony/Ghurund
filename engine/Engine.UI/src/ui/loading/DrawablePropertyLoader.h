#pragma once

#include "PropertyLoader.h"
#include "ui/loading/ImageDrawableFactory.h"

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

        virtual void loadAttr(Object& obj, const BaseProperty& property, const AString& text) const override;
    };
}
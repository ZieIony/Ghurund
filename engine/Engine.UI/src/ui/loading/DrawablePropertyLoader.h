#pragma once

#include "PropertyLoader.h"
#include "ui/loading/ImageDrawableFactory.h"
#include "ui/style/DrawableAttr.h"

namespace Ghurund::UI {
    class DrawablePropertyLoader:public PropertyLoader {
    private:
        static inline const char* THEME_DRAWABLE = "theme://drawable/";

        ImageDrawableFactory& drawableFactory;

    public:
        DrawablePropertyLoader(ImageDrawableFactory& drawableFactory):drawableFactory(drawableFactory) {}

        virtual const Type& getType() const override {
            return Ghurund::Core::getType<std::unique_ptr<Ghurund::UI::DrawableAttr>&>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const AString& text) const override;
    };
}
#pragma once

#include "PropertyLoader.h"
#include "ui/style/ColorAttr.h"

namespace Ghurund::UI {

    class ColorPropertyLoader:public PropertyLoader {
    private:
        static inline const char* THEME_COLOR = "theme://color/";

    public:
        virtual const Type& getType() const override {
            return Ghurund::Core::getType<const ColorAttr&>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const AString& text) const override {
            AString s = text;
            s = s.trim();
            s.replace('\\', '/');
            if (s.startsWith("#")) {
                ColorValue cv = ColorValue(Color::parse(s));
                property.setRaw(&obj, &cv);
            } else if (s.startsWith(THEME_COLOR)) {
                ColorRef cr = ColorRef(ColorKey(s.substring(lengthOf(THEME_COLOR))));
                property.setRaw(&obj, &cr);
            }
        }
    };

    class NullableColorPropertyLoader:public PropertyLoader {
    private:
        static inline const char* THEME_COLOR = "theme://color/";

    public:
        virtual const Type& getType() const override {
            return Ghurund::Core::getType<std::unique_ptr<ColorAttr>>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const AString& text) const override {
            AString s = text;
            s = s.trim();
            s.replace('\\', '/');
            if (s.startsWith("#")) {
                auto cv = std::make_unique<ColorValue>(Color::parse(s));
                property.setRaw(&obj, &cv);
            } else if (s.startsWith(THEME_COLOR)) {
                auto cr = std::make_unique<ColorRef>(ColorKey(s.substring(lengthOf(THEME_COLOR))));
                property.setRaw(&obj, &cr);
            }
        }
    };
}
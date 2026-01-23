#pragma once

#include "core/loading/PropertyLoader.h"
#include "ui/theme/ThemedValue.h"

namespace Ghurund::UI {

    class BaseColorPropertyLoader:public PropertyLoader {
    private:
        static inline const char* THEME_COLOR = "theme://color/";
 
    public:
        std::unique_ptr<ThemedColor> loadThemedColor(const AString& text) const {
            AString s = text;
            s = s.trim();
            s.replace('\\', '/');
            if (s.startsWith("#")) {
                return std::make_unique<ThemedColor>(Color::parse(s));
            } else if (s.startsWith(THEME_COLOR)) {
                return std::make_unique<ThemedColor>(ColorKey(s.substring(lengthOf(THEME_COLOR))));
            } else {
                return nullptr;
            }
        }
    };


    class ColorPropertyLoader:public BaseColorPropertyLoader {
	public:
		virtual const Type& getType() const override {
			return Ghurund::Core::getType<const ThemedColor&>();
		}

		virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override {
            auto color = loadThemedColor(text);
			if (color)
				property.setRaw(&obj, color.get());
		}
	};

	class NullableColorPropertyLoader:public BaseColorPropertyLoader {
    public:
        virtual const Type& getType() const override {
            return Ghurund::Core::getType<ThemedColor*>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override {
            auto color = loadThemedColor(text);
            property.setRaw(&obj, &color);
        }
    };
}
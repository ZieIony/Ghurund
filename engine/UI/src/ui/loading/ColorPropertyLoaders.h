#pragma once

#include "core/loading/PropertyLoader.h"
#include "ui/style/ColorAttr.h"

namespace Ghurund::UI {

    class ColorPropertyLoader:public PropertyLoader {
	public:
		virtual const Type& getType() const override {
			return Ghurund::Core::getType<const ColorAttr&>();
		}

		virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override {
			auto color = ColorAttr::load(text);
			if (color)
				property.setRaw(&obj, color.get());
		}
	};

	class NullableColorPropertyLoader:public PropertyLoader {
    public:
        virtual const Type& getType() const override {
            return Ghurund::Core::getType<std::unique_ptr<ColorAttr>>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override {
            auto color = ColorAttr::load(text);
            property.setRaw(&obj, &color);
        }
    };
}
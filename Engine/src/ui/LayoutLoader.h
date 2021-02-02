#pragma once

#include "core/io/FilePath.h"
#include "core/reflection/Type.h"
#include "core/string/AStringView.h"
#include "resource/ResourceContext.h"
#include "ui/control/Control.h"
#include "ui/Alignment.h"

#include <tinyxml2.h>

namespace Ghurund::UI {
    class TextStyle;
    class Theme;

    class LayoutLoader {
    private:
        Map<AString, Type*> types;
        Theme* theme;

    public:
        LayoutLoader();

        void registerClass(const Type& type) {
            if (type.extends(Control::TYPE))
                types.set(type.Name, (Type*)&type);
        }

        inline void setTheme(Theme* theme) {
            this->theme = theme;
        }

        inline Theme* getTheme() {
            return theme;
        }

        __declspec(property(get = getTheme, put = setTheme)) Theme* Theme;

        PointerList<Control*> load(ResourceContext& context, const Buffer& data);

        PointerList<Control*> load(ResourceContext& context, const FilePath& path) {
            File file(path);
            if (!file.Exists)
                return PointerList<Control*>();
            if (file.read() == Status::OK)
                return load(context, Buffer(file.Data, file.Size));
            return PointerList<Control*>();
        }

        PointerList<Control*> loadControls(ResourceContext& context, const tinyxml2::XMLElement& xml);

        Control* loadControl(ResourceContext& context, const tinyxml2::XMLElement& xml);

        Shape* loadShape(ResourceContext& context, const char* str);

        uint32_t loadColor(const char* str);

        BitmapImage* loadImage(ResourceContext& context, const char* str);
        
        WString loadText(const char* str);

        TextStyle* loadFont(ResourceContext& context, const char* str);

        Status loadAlignment(const tinyxml2::XMLElement& xml, Alignment* alignment);
    };
}
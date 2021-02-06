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
        ResourceContext* context;

    public:
        LayoutLoader();

        inline void init(Theme& theme, ResourceContext& context) {
            this->theme = &theme;
            this->context = &context;
        }

        void registerClass(const Type& type) {
            if (type.extends(Control::TYPE))
                types.set(type.Name, (Type*)&type);
        }

        inline Theme& getTheme() {
            return *theme;
        }

        __declspec(property(get = getTheme)) Theme& Theme;

        inline ResourceContext& getResourceContext() {
            return *context;
        }

        __declspec(property(get = getResourceContext)) ResourceContext& ResourceContext;

        Status load(const Buffer& data, PointerList<Control*>& output);

        Status load(const FilePath& path, PointerList<Control*>& output) {
            File file(path);
            if (!file.Exists)
                return Status::FILE_DOESNT_EXIST;
            Status result = file.read();
            if (result == Status::OK)
                return load(Buffer(file.Data, file.Size), output);
            return result;
        }

        PointerList<Control*> loadControls(const tinyxml2::XMLElement& xml);

        Control* loadControl(const tinyxml2::XMLElement& xml);

        Shape* loadShape(const char* str);

        uint32_t loadColor(const char* str);

        BitmapImage* loadImage(const char* str);
        
        WString loadText(const char* str);

        TextStyle* loadFont(const char* str);

        Status loadAlignment(const tinyxml2::XMLElement& xml, Alignment* alignment);
    };
}
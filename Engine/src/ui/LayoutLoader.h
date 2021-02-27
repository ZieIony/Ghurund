#pragma once

#include "core/collection/Stack.h"
#include "core/collection/PointerList.h"
#include "core/io/FilePath.h"
#include "core/reflection/Type.h"
#include "core/string/AStringView.h"
#include "resource/ResourceContext.h"
#include "ui/control/Control.h"
#include "ui/Alignment.h"

#include <tinyxml2.h>

namespace Ghurund{
    class Buffer;
}

namespace Ghurund::UI {
    class TextFormat;
    class Theme;
    class Shape;
    class BitmapImage;

    class LayoutLoader {
    private:
        Map<AString, const Type*> types;
        Theme* theme;
        ResourceContext* context;
        Stack<DirectoryPath> workingDir;

    public:
        static inline const char* FILE_PROTOCOL = "file://";
        static inline const char* THEME_PROTOCOL = "theme://";

        LayoutLoader();

        inline void init(Theme& theme, ResourceContext& context) {
            this->theme = &theme;
            this->context = &context;
        }

        void registerClass(const Type& type) {
            if (type.extends(Control::TYPE))
                types.set(type.Name, &type);
        }

        inline Theme& getTheme() {
            return *theme;
        }

        __declspec(property(get = getTheme)) Theme& Theme;

        inline ResourceContext& getResourceContext() {
            return *context;
        }

        __declspec(property(get = getResourceContext)) ResourceContext& ResourceContext;

        inline const DirectoryPath& getWorkingDirectory() {
            return workingDir.top();
        }

        inline void setWorkingDirectory(const DirectoryPath& path) {
            workingDir.clear();
            workingDir.push(path);
        }

        __declspec(property(get = getWorkingDirectory, put = setWorkingDirectory)) const DirectoryPath& WorkingDirectory;

        Status load(const Buffer& data, PointerList<Control*>& output);

        Status load(const FilePath& path, PointerList<Control*>& output);

        PointerList<Control*> loadControls(const tinyxml2::XMLElement& xml);

        Control* loadControl(const tinyxml2::XMLElement& xml);

        Shape* loadShape(const char* str);

        uint32_t loadColor(const char* str);

        BitmapImage* loadImage(const char* str);
        
        WString loadText(const char* str);

        TextFormat* loadTextFormat(const char* str);

        Status loadAlignment(const tinyxml2::XMLElement& xml, Alignment* alignment);

        WString getPath(const AString& path);
    };
}
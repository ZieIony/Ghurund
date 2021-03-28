#pragma once

#include "core/Buffer.h"
#include "core/collection/Stack.h"
#include "core/collection/PointerList.h"
#include "core/io/FilePath.h"
#include "core/reflection/Type.h"
#include "core/string/AStringView.h"
#include "ui/Alignment.h"
#include "ui/IResourceLoader.h"
#include "ui/control/Control.h"
#include "ui/drawable/ImageDrawable.h"

#include <tinyxml2.h>
#include <d2d1_3.h>

namespace Ghurund::UI {
    class TextFormat;
    class Theme;
    class Shape;

    class LayoutLoader {
    private:
        Map<AString, const Type*> types;
        Theme* theme = nullptr;
        ID2D1Factory6* d2dFactory = nullptr;
        Stack<DirectoryPath> workingDir;
        IResourceLoader* resourceLoader = nullptr;

    public:
        static inline const char* FILE_PROTOCOL = "file://";
        static inline const char* THEME_PROTOCOL = "theme://";

        LayoutLoader();

        virtual ~LayoutLoader() {}

        inline void init(Theme& theme, ID2D1Factory6& d2dFactory, IResourceLoader& resourceLoader) {
            this->theme = &theme;
            this->d2dFactory = &d2dFactory;
            this->resourceLoader = &resourceLoader;
        }

        void registerClass(const Type& type) {
            if (type.extends(Control::TYPE))
                types.set(type.Name, &type);
        }

        inline Theme& getTheme() {
            return *theme;
        }

        inline void setTheme(Theme& theme) {
            this->theme = &theme;
        }

        __declspec(property(get = getTheme, put = setTheme)) Theme& Theme;

        inline const DirectoryPath& getWorkingDirectory() {
            return workingDir.top();
        }

        inline void setWorkingDirectory(const DirectoryPath& path) {
            workingDir.clear();
            workingDir.push(path);
        }

        __declspec(property(get = getWorkingDirectory, put = setWorkingDirectory)) const DirectoryPath& WorkingDirectory;

        ImageDrawable* loadDrawable(const char* str);

        Status load(const Buffer& data, PointerList<Control*>& output);

        Status load(const FilePath& path, PointerList<Control*>& output);

        PointerList<Control*> loadControls(const tinyxml2::XMLElement& xml);

        Control* loadControl(const tinyxml2::XMLElement& xml);

        Shape* loadShape(const char* str);

        uint32_t loadColor(const char* str);

        WString loadText(const char* str);

        TextFormat* loadTextFormat(const char* str);

        Status loadAlignment(const tinyxml2::XMLElement& xml, Alignment* alignment);

        WString getPath(const AString& path);
    };
}
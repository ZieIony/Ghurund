#pragma once

#include "Layout.h"
#include "core/Buffer.h"
#include "core/collection/Stack.h"
#include "core/collection/PointerList.h"
#include "core/io/FilePath.h"
#include "core/reflection/Type.h"
#include "core/resource/Loader.h"
#include "core/resource/ResourceManager.h"
#include "core/string/AStringView.h"
#include "ui/Alignment.h"
#include "ui/control/Control.h"
#include "ui/drawable/ImageDrawable.h"

#include <tinyxml2.h>
#include <d2d1_3.h>

namespace Ghurund::UI {
    class TextFormat;
    class Theme;
    class Shape;

    class LayoutLoader:public Loader {
    private:
        ID2D1Factory6& d2dFactory;
        ResourceManager& resourceManager;
        Theme* theme = nullptr;
        Map<AString, const Type*> types;

    public:
        static inline const char* FILE_PROTOCOL = "file://";
        static inline const char* THEME_STYLE = "theme://style/";
        static inline const char* THEME_COLOR = "theme://color/";
        static inline const char* THEME_IMAGE = "theme://image/";
        static inline const char* THEME_TEXTFORMAT = "theme://textFormat/";

        LayoutLoader(ID2D1Factory6& d2dFactory, ResourceManager& resourceManager);

        virtual ~LayoutLoader() {}

        void registerClass(const Type& type) {
            if (type.extends(Control::TYPE))
                types.set(type.Name, &type);
        }

        inline Theme* getTheme() {
            return theme;
        }

        inline void setTheme(Theme* theme) {
            this->theme = theme;
        }

        __declspec(property(get = getTheme, put = setTheme)) Theme* Theme;

        inline ResourceManager& getResourceManager() {
            return resourceManager;
        }

        __declspec(property(get = getResourceManager)) ResourceManager& ResourceManager;

        ImageDrawable* loadDrawable(const char* str);

        virtual Status load(Ghurund::ResourceManager& manager, MemoryInputStream& stream, Resource& resource, const ResourceFormat* format = nullptr, LoadOption options = LoadOption::DEFAULT) override;

        virtual Status save(Ghurund::ResourceManager& manager, MemoryOutputStream& stream, Resource& resource, const ResourceFormat* format = nullptr, SaveOption options = SaveOption::DEFAULT) const override {
            return Status::NOT_IMPLEMENTED;
        }

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
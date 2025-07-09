#pragma once

#include "PropertyLoader.h"
#include "ui/style/LayoutAttr.h"

namespace Ghurund::Core {
    class ResourceManager;
}

namespace Ghurund::UI {
    class LayoutLoader;

    class LayoutPropertyLoader:public PropertyLoader {
    private:
        static inline const char* THEME_LAYOUT = "theme://layout/";

        // borrowed
        ResourceManager* resourceManager;
        // borrowed
        LayoutLoader* layoutLoader;

    public:
        LayoutPropertyLoader(NotNull<ResourceManager> resourceManager, NotNull<LayoutLoader> layoutLoader):resourceManager(&resourceManager), layoutLoader(&layoutLoader) {}

        virtual const Type& getType() const override {
            return Ghurund::Core::getType<std::unique_ptr<Ghurund::UI::LayoutAttr>>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override;

        virtual void loadChildren(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) const override;
    };
}
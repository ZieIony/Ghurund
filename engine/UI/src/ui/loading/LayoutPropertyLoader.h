#pragma once

#include "core/loading/PropertyLoader.h"
#include "ui/widget/Widget.h"

namespace Ghurund::Core {
    class ResourceManager;
}

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class LayoutLoader;

    class LayoutPropertyLoader:public PropertyLoader {
    private:
        static inline const char* THEME_LAYOUT = "theme://layout/";

        ResourceManager& resourceManager;
        LayoutLoader& layoutLoader;

    public:
        LayoutPropertyLoader(ResourceManager& resourceManager, LayoutLoader& layoutLoader):resourceManager(resourceManager), layoutLoader(layoutLoader) {}

        virtual const Type& getType() const override {
            return Ghurund::Core::getType<const ThemedLayout&>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override;

        virtual void loadChildren(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const XMLElement& xml) const override;
    };
}

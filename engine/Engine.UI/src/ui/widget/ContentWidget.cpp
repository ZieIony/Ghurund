#include "ghuipch.h"
#include "ContentWidget.h"

#include "ui/loading/LayoutLoader.h"
#include "ui/control/InvalidControl.h"

#include <tinyxml2.h>

namespace Ghurund::UI {
    void ContentWidget::load(LayoutLoader& loader, ResourceManager& resourceManager, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) {
        __super::load(loader, resourceManager, workingDir, xml);
        auto childElement = xml.FirstChildElement();
        while (childElement) {
            if (!AString(childElement->Name()).contains(".")) {
                SharedPointer<Control> control(loader.loadControl(workingDir, *childElement));
                if (control != nullptr) {
                    Content = control.get();
                } else {
                    Content = makeShared<InvalidControl>().get();
                }
                return;
            }
            childElement = childElement->NextSiblingElement();
        }
    }

    Ghurund::UI::Control* ContentWidget::find(const Ghurund::Core::AString& name) {
        if (this->Name && this->Name->operator==(name))
            return this;
        if (content != nullptr)
            return content->find(name);
        return nullptr;
    }

    Ghurund::UI::Control* ContentWidget::find(const Ghurund::Core::Type& type) {
        if (Type == type)
            return this;
        if (content != nullptr)
            return content->find(type);
        return nullptr;
    }

    const Ghurund::Core::Type& ContentWidget::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<ContentWidget>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(ContentWidget))
            .withModifiers(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
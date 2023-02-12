#include "ghuipch.h"
#include "ContentWidget.h"

#include "ui/loading/LayoutLoader.h"
#include "ui/control/InvalidControl.h"

#include <tinyxml2.h>

namespace Ghurund::UI {
    void ContentWidget::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        __super::load(loader, xml);
        container = (Ghurund::UI::ControlContainer*)ControlContainer::find("content");
        auto childElement = xml.FirstChildElement();
        while (childElement) {
            if (!AString(childElement->Name()).contains(".")) {
                SharedPointer<Control> control(loader.loadControl(*childElement));
                if (control != nullptr) {
                    content.Value = control;
                } else {
                    content.Value = SharedPointer<Control>(ghnew InvalidControl());
                }
                return;
            }
            childElement = childElement->NextSiblingElement();
        }
    }

    Ghurund::UI::Control* ContentWidget::find(const Ghurund::Core::AString& name, bool deep) const {
        if (content.Value != nullptr) {
            if (content.Value->Name && content.Value->Name->operator==(name))
                return content.Value.get();
            return content.Value->find(name, deep);
        }
        return nullptr;
    }

    Ghurund::UI::Control* ContentWidget::find(const Ghurund::Core::Type& type, bool deep) const {
        if (content.Value != nullptr) {
            if (content.Value->Type == type)
                return content.Value.get();
            return content.Value->find(type, deep);
        }
        return nullptr;
    }

    const Ghurund::Core::Type& ContentWidget::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<ContentWidget>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(ContentWidget))
            .withModifiers(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
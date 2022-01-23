#pragma once

#include "core/Observable.h"
#include "Widget.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class ContentWidget:public Widget {
    protected:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<ContentWidget>(NAMESPACE_NAME, GH_STRINGIFY(ContentWidget))
                .withModifiers(TypeModifier::ABSTRACT)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        virtual void bind() override {
            ControlContainer* container = (Ghurund::UI::ControlContainer*)ControlContainer::find("content");
            content += [&](Control* control) {
                container->Child = control;
            };
        }

        virtual void loadContent(Ghurund::UI::LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
            auto childElement = xml.FirstChildElement();
            while (childElement) {
                if (strcmp(childElement->Name(), std::format("{}.Content", Type.Name).c_str()) == 0) {
                    auto controls = loader.loadControls(*childElement);
                    if (!controls.Empty)
                        content = controls[0];
                } else if (!content) {
                    auto control = loader.loadControl(*childElement);
                    if (control) {
                        content = control;
                        control->release();
                    }
                }
                childElement = childElement->NextSiblingElement();
            }
        }

    public:
        Observable<Ghurund::UI::Control*> content;

        virtual Ghurund::UI::Control* find(const Ghurund::Core::AString& name) override {
            if (content)
                return content.Value->find(name);
            return nullptr;
        }

        virtual Ghurund::UI::Control* find(const Ghurund::Core::Type& type) override {
            if (content)
                return content.Value->find(type);
            return nullptr;
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };
}

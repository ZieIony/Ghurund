#pragma once

#include "core/Observable.h"
#include "Widget.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class ContentWidget:public Widget {
    private:
        ControlContainer* container = nullptr;

        virtual void loadContent(Ghurund::UI::LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
            auto childElement = xml.FirstChildElement();
            while (childElement) {
                if (strcmp(childElement->Name(), std::format("{}.Content", Type.Name).c_str()) == 0) {
                    auto controls = loader.loadControls(*childElement);
                    if (!controls.Empty) {
                        content = controls[0];
                        controls[0]->addReference();
                        return;
                    }
                } else {
                    auto control = loader.loadControl(*childElement);
                    if (control) {
                        content = control;
                        return;
                    }
                }
                childElement = childElement->NextSiblingElement();
            }
        }

    protected:
        virtual void bind() override {
            container = (Ghurund::UI::ControlContainer*)ControlContainer::find("content");
            content += [&](Control* control) {
                if (container)
                    container->Child = control;
            };
        }

    public:
        Observable<Ghurund::UI::Control*> content;

        virtual void load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override {
            __super::load(loader, xml);
            loadContent(loader, xml);
        }

        using Control::find;

        virtual Ghurund::UI::Control* find(const Ghurund::Core::AString& name, bool deep = true) override {
            if (content.Value)
                return content.Value->find(name, deep);
            return nullptr;
        }

        virtual Ghurund::UI::Control* find(const Ghurund::Core::Type& type, bool deep = true) override {
            if (content.Value)
                return content.Value->find(type, deep);
            return nullptr;
        }

        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<ContentWidget>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(ContentWidget))
                .withModifiers(TypeModifier::ABSTRACT)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}

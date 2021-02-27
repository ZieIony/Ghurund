#pragma once

#include "Widget.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
    template<class LayoutType>
    requires std::is_base_of<ContainerLayout, LayoutType>::value
        class ContainerWidget:public Widget<LayoutType> {
        private:
            ControlContainer* container = nullptr;

        protected:
            static const Ghurund::Type& GET_TYPE() {
                static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ContainerWidget))
                    .withModifiers(TypeModifier::ABSTRACT)
                    .withSupertype(__super::GET_TYPE());

                return TYPE;
            }

        public:
            ~ContainerWidget() = 0 {}

            inline void setContent(Control* control) {
                Widget<LayoutType>::Layout->Container->Child = control;
            }

            inline Control* getContent() {
                return Widget<LayoutType>::Layout->Container->Child;
            }

            __declspec(property(get = getContent, put = setContent)) Control* Content;

            virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override {
                Status result = __super::load(loader, xml);
                if (result != Status::OK)
                    return result;
                auto child = xml.FirstChildElement();
                if (Widget<LayoutType>::Layout->Container && child) {
                    Control* control = loader.loadControl(*child);
                    if (control) {
                        Content = control;
                        control->release();
                    }
                }
                return Status::OK;
            }

            inline static const Ghurund::Type& TYPE = GET_TYPE();

            virtual const Ghurund::Type& getType() const override {
                return TYPE;
            }
    };
}
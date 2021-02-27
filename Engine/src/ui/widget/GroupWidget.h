#pragma once

#include "Widget.h"

namespace Ghurund::UI {
    template<class LayoutType>
    requires std::is_base_of<GroupLayout, LayoutType>::value
        class GroupWidget:public Widget<LayoutType> {
        private:
            ControlGroup* container = nullptr;

        protected:
            static const Ghurund::Type& GET_TYPE() {
                static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(GroupWidget))
                    .withModifiers(TypeModifier::ABSTRACT)
                    .withSupertype(__super::GET_TYPE());

                return TYPE;
            }

            ~GroupWidget() = 0 {}

        public:
            inline void setContent(const std::initializer_list<Control*>& controls) {
                Widget<LayoutType>::Layout->Container->Children = controls;
            }

            inline ControlList& getContent() {
                return Widget<LayoutType>::Layout->Container->Children;
            }

            inline const ControlList& getContent() const {
                return Widget<LayoutType>::Layout->Container->Children;
            }

            __declspec(property(get = getContent, put = setContent)) ControlList& Content;

            virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override {
                Status result = __super::load(loader, xml);
                if (result != Status::OK)
                    return result;
                if (Widget<LayoutType>::Layout->Container && xml.FirstChildElement()) {
                    Widget<LayoutType>::Layout->Container->Children.clear();
                    Widget<LayoutType>::Layout->Container->Children.addAll(loader.loadControls(xml));
                }
                return Status::OK;
            }

            inline static const Ghurund::Type& TYPE = GET_TYPE();

            virtual const Ghurund::Type& getType() const override {
                return TYPE;
            }
    };
}
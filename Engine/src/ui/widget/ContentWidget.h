#pragma once

#include "Widget.h"

namespace Ghurund::UI {
    template<class LayoutType>
    requires std::is_base_of<WidgetLayout, LayoutType>::value
        class ContentWidget:public Widget<LayoutType> {
        private:
            ControlContainer* container = nullptr;

        protected:
            static const Ghurund::Type& GET_TYPE() {
                static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ContentWidget))
                    .withModifiers(TypeModifier::ABSTRACT)
                    .withSupertype(__super::GET_TYPE());

                return TYPE;
            }

            virtual void onLayoutChanged() override {
                container = (ControlContainer*)ControlContainer::find(_T("content"));
            }

        public:
            ContentWidget(LayoutType* layout = nullptr):Widget<LayoutType>(layout) {}

            ~ContentWidget() = 0 {}

            inline void setContent(Control* control) {
                container->Child = control;
            }

            inline Control* getContent() {
                return container->Child;
            }

            __declspec(property(get = getContent, put = setContent)) Control* Content;

            virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override {
                Status result = __super::load(loader, xml);
                if (result != Status::OK)
                    return result;
                if (container && xml.FirstChildElement())
                    Content = loader.loadControl(*xml.FirstChildElement());
                return Status::OK;
            }

            inline static const Ghurund::Type& TYPE = GET_TYPE();

            virtual const Ghurund::Type& getType() const override {
                return TYPE;
            }
    };
}
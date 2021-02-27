#pragma once

#include "Layout.h"
#include "core/reflection/TypeBuilder.h"
#include "ui/LayoutLoader.h"
#include "ui/style/Style.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    template<class LayoutType>
    requires std::is_base_of<WidgetLayout, LayoutType>::value
        class Widget:public ControlContainer {
        private:
            LayoutType* widgetLayout = nullptr;

            EventHandler<Control> stateHandler = [this](Control& control) {
                if (widgetLayout)
                    widgetLayout->onStateChanged(*this);
                return true;
            };

            EventHandler<Control> themeHandler = [this](Control& control) {
                if (widgetLayout)
                    widgetLayout->onThemeChanged(*this);
                return true;
            };

        protected:
            static const Ghurund::Type& GET_TYPE() {
                static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Widget))
                    .withModifiers(TypeModifier::ABSTRACT)
                    .withSupertype(__super::GET_TYPE());

                return TYPE;
            }

            virtual void onLayoutChanged() {}

        public:
            Widget() {
                StateChanged.add(stateHandler);
                ThemeChanged.add(themeHandler);
            }

            ~Widget() = 0 {
                delete widgetLayout;
                widgetLayout = nullptr;
            }

            inline LayoutType* getLayout() const {
                return widgetLayout;
            }

            inline void setLayout(std::unique_ptr<LayoutType> layout) {
                if (widgetLayout == layout.get())
                    return;
                if (widgetLayout) {
                    Child = nullptr;
                    delete widgetLayout;
                }
                widgetLayout = layout.release();
                if (widgetLayout)
                    Child = widgetLayout->Root;
                onLayoutChanged();
            }

            __declspec(property(get = getLayout, put = setLayout)) LayoutType* Layout;

            virtual void onMeasure(float parentWidth, float parentHeight) override {
                if (widgetLayout)
                    widgetLayout->Root->PreferredSize = preferredSize;
                __super::onMeasure(parentWidth, parentHeight);
            }

            virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override {
                Status result = Control::load(loader, xml);
                if (result != Status::OK)
                    return result;
                auto layoutAttr = xml.FindAttribute("layout");
                if (!layoutAttr && !loader.Theme.Layouts.contains(&Type))
                    return Status::INV_PARAM;

                AString s = layoutAttr ? layoutAttr->Value() : loader.Theme.Layouts.get(&Type);
                uint32_t value = 0;
                PointerList<Control*> controls;
                result = loader.load(loader.getPath(s), controls);
                if (result != Status::OK)
                    return result;
                if (!controls.Empty) {
                    Layout = std::unique_ptr<LayoutType>(ghnew LayoutType(controls[0]));
                    return Status::OK;
                }
                return Status::INV_PARAM;
            }

            inline static const Ghurund::Type& TYPE = GET_TYPE();

            virtual const Ghurund::Type& getType() const override {
                return TYPE;
            }
    };
}

#pragma once

#include "Layout.h"
#include "ui/Style.h"

namespace Ghurund::UI {
    template<class LayoutType>
    requires std::is_base_of<WidgetLayout, LayoutType>::value
        class Widget:public ControlContainer {
        private:
            LayoutType* widgetLayout = nullptr;

            static const Ghurund::Type& GET_TYPE() {
                static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Widget))
                    .withModifiers(TypeModifier::ABSTRACT)
                    .withSupertype(__super::TYPE);

                return TYPE;
            }

            EventHandler<Control> stateHandler = [this](Control& control) {
                if (widgetLayout) {
                    widgetLayout->onStateChanged(*this);
                    repaint();
                }
                return true;
            };

        public:
            Widget(LayoutType* layout) {
                OnStateChanged.add(stateHandler);
                widgetLayout = layout;
#ifdef _DEBUG
                if (widgetLayout->Root)
                    Logger::log(LogType::INFO, "widget layout for {} initialized in its constructor", Type.Name);
#endif
                widgetLayout->init();
                OnStateChanged();
                Child = widgetLayout->Root;
            }

            ~Widget() = 0 {
                delete widgetLayout;
            }

            inline LayoutType& getLayout() const {
                return *widgetLayout;
            }

            __declspec(property(get = getLayout)) LayoutType& Layout;

            virtual void onMeasure(float parentWidth, float parentHeight) override {
                widgetLayout->Root->PreferredSize = preferredSize;
                __super::onMeasure(parentWidth, parentHeight);
            }

            inline static const Ghurund::Type& TYPE = GET_TYPE();

            virtual const Ghurund::Type& getType() const override {
                return TYPE;
            }
    };
}

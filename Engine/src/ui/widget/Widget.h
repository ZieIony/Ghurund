#pragma once

#include "Layout.h"
#include "ui/Style.h"

namespace Ghurund::UI {
    template<class ControlType, class LayoutType>
    requires std::is_base_of<Layout, LayoutType>::value
        class Widget:public ControlContainer {
        private:
            LayoutType* widgetLayout = nullptr;
            StyleWithLayout<ControlType, LayoutType>* style = nullptr;

        protected:
            virtual void onStateChanged() override {
                if (style)
                    style->onStateChanged(*this);
                if (widgetLayout)
                    widgetLayout->onStateChanged(*this);
                repaint();
            }

        public:
            Widget(StyleWithLayout<ControlType, LayoutType>* style) {
                Style = style;
            }

            ~Widget() {
                delete widgetLayout;
                if (style)
                    style->release();
            }

            inline LayoutType& getLayout() const {
                return *widgetLayout;
            }

            __declspec(property(get = getLayout)) LayoutType& Layout;

            inline StyleWithLayout<ControlType, LayoutType>* getStyle() {
                return style;
            }

            inline void setStyle(StyleWithLayout<ControlType, LayoutType>* style) {
                setPointer(this->style, style);
                if (style) {
                    if (widgetLayout)
                        delete widgetLayout;
                    widgetLayout = style->makeLayout();
                    widgetLayout->init();
                    widgetLayout->onStateChanged(*this);
                    Child = widgetLayout->Root;
                    style->apply(*this);
                    style->onStateChanged(*this);
                }
            }

            __declspec(property(get = getStyle, put = setStyle)) StyleWithLayout<ControlType, LayoutType>* Style;

            virtual void onMeasure(float parentWidth, float parentHeight) override {
                widgetLayout->Root->PreferredSize = preferredSize;
                __super::onMeasure(parentWidth, parentHeight);
            }
    };

    template<class LayoutType>
    requires std::is_base_of<Layout, LayoutType>::value
        class Widget2:public ControlContainer {
        private:
            LayoutType* widgetLayout = nullptr;

        protected:
            virtual void onStateChanged() override {
                if (widgetLayout)
                    widgetLayout->onStateChanged(*this);
                repaint();
            }

        public:
            Widget2(LayoutType* layout) {
                Layout = layout;
            }

            ~Widget2() {
                delete widgetLayout;
            }

            inline LayoutType& getLayout() const {
                return *widgetLayout;
            }

            inline void setLayout(LayoutType* layout) {
                if (widgetLayout)
                    delete widgetLayout;
                widgetLayout = layout;
                widgetLayout->init();
                widgetLayout->onStateChanged(*this);
                Child = widgetLayout->Root;
            }

            __declspec(property(get = getLayout, put = setLayout)) LayoutType& Layout;

            virtual void onMeasure(float parentWidth, float parentHeight) override {
                widgetLayout->Root->PreferredSize = preferredSize;
                __super::onMeasure(parentWidth, parentHeight);
            }
    };
}

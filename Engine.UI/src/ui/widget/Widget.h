#pragma once

#include "Layout.h"
#include "core/string/TextConversionUtils.h"
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

        protected:
            static const Ghurund::Type& GET_TYPE() {
                static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Widget))
                    .withModifiers(TypeModifier::ABSTRACT)
                    .withSupertype(__super::GET_TYPE());

                return TYPE;
            }

            virtual void onLayoutChanged() {}

            virtual void onThemeChanged() override {
                if (!widgetLayout)
                    Layout = std::unique_ptr<LayoutType>(makeDefaultLayout());
                if (!style)
                    Style = makeDefaultStyle();
                __super::onThemeChanged();
            }

            virtual LayoutType* makeDefaultLayout() {
                if (!Theme || !Context)
                    return nullptr;
                PointerList<Control*> controls;
                size_t layoutIndex = Theme->Layouts.indexOfKey(&Type);
                if (layoutIndex == Theme->Layouts.Size)
                    return nullptr;
                FilePath layoutPath = toWideChar(Theme->Layouts.getValue(layoutIndex));
                if (Context->LayoutLoader.load(layoutPath, controls) == Status::OK)
                    return ghnew LayoutType(controls[0]);
                return nullptr;
            }

            virtual Ghurund::UI::Style* makeDefaultStyle() {
                if (!Theme || !Context)
                    return nullptr;
                PointerList<Control*> controls;
                size_t index = Theme->Styles.indexOfKey(StyleKey(Type.Name));
                if (index == Theme->Styles.Size)
                    return nullptr;
                return Theme->Styles.getValue(index);
            }

        public:
            ~Widget() = 0 {
                delete widgetLayout;
                widgetLayout = nullptr;
            }

            inline LayoutType* getLayout() const {
                return widgetLayout;
            }

            inline void setLayout(std::unique_ptr<LayoutType> layout) {
                if (widgetLayout) {
                    Child = nullptr;
                    delete widgetLayout;
                }
                widgetLayout = layout.release();
                if (widgetLayout)
                    Child = widgetLayout->Root;
                onLayoutChanged();
                dispatchStateChanged();
            }

            __declspec(property(get = getLayout, put = setLayout)) LayoutType* Layout;

            virtual void onMeasure(float parentWidth, float parentHeight) override {
                if (widgetLayout)
                    widgetLayout->Root->PreferredSize = preferredSize;
                __super::onMeasure(parentWidth, parentHeight);
            }

            virtual Control* find(const AString& name) {
                Control* baseFind = Control::find(name);
                if (baseFind)
                    return baseFind;
                if (Layout)
                    return Layout->find(name);
                return nullptr;
            }

            virtual Control* find(const Ghurund::Type& type) {
                Control* baseFind = Control::find(type);
                if (baseFind)
                    return baseFind;
                if (Layout)
                    return Layout->find(type);
                return nullptr;
            }

            virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override {
                Status result = Control::load(loader, xml);
                if (result != Status::OK)
                    return result;
                auto layoutAttr = xml.FindAttribute("layout");
                if (!layoutAttr && !loader.Theme.Layouts.containsKey(&Type))
                    return Status::INV_PARAM;

                AString s = layoutAttr ? layoutAttr->Value() : loader.Theme.Layouts.get(&Type);
                uint32_t value = 0;
                PointerList<Control*> controls;
                result = loader.load(loader.getPath(s), controls);
                if (result != Status::OK)
                    return result;
                if (!controls.Empty)
                    Layout = std::unique_ptr<LayoutType>(ghnew LayoutType(controls[0]));
                if (Layout)
                    return Layout->loadContent(loader, xml);
                return Status::INV_PARAM;
            }

            inline static const Ghurund::Type& TYPE = GET_TYPE();

            virtual const Ghurund::Type& getType() const override {
                return TYPE;
            }
    };

    template<class LayoutType, class DataType>
    requires std::is_base_of<BindingLayout<DataType>, LayoutType>::value
        class BindingWidget:public Widget<LayoutType> {
        protected:
            static const Ghurund::Type& GET_TYPE() {
                static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(BindingWidget))
                    .withModifiers(TypeModifier::ABSTRACT)
                    .withSupertype(__super::GET_TYPE());

                return TYPE;
            }

            virtual void onStateChanged() override {
                __super::onStateChanged();
                if (Widget<LayoutType>::Layout) {
                    Widget<LayoutType>::Layout->bind((DataType&)getData());
                    Widget<LayoutType>::Layout->Root->invalidate();
                }
            }

            virtual DataType& getData() {
                return (DataType&)*this;
            }

        public:
            inline static const Ghurund::Type& TYPE = GET_TYPE();

            virtual const Ghurund::Type& getType() const override {
                return TYPE;
            }
    };
}

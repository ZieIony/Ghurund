#pragma once

#include "LayoutBinding.h"
#include "core/Concepts.h"
#include "core/string/TextConversionUtils.h"
#include "core/reflection/TypeBuilder.h"
#include "ui/layout/LayoutLoader.h"
#include "ui/style/Style.h"
#include "ui/style/Theme.h"
#include "ui/control/InvalidControl.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    template<Derived<LayoutBinding> LayoutType>
    class Widget:public ControlContainer {
    private:
        LayoutType* widgetLayout = nullptr;

    protected:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<Widget>(NAMESPACE_NAME, GH_STRINGIFY(Widget))
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
            FilePath layoutPath = convertText<char, wchar_t>(Theme->Layouts.getValue(layoutIndex));
            SharedPointer<Ghurund::UI::Layout> layout = Context->ResourceManager.load<Ghurund::UI::Layout>(layoutPath, nullptr, nullptr, LoadOption::DONT_CACHE);
            if (layout && !layout->Controls.Empty)
                return ghnew LayoutType(layout->Controls[0]);
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

        virtual Control* find(const Ghurund::Core::Type& type) {
            Control* baseFind = Control::find(type);
            if (baseFind)
                return baseFind;
            if (Layout)
                return Layout->find(type);
            return nullptr;
        }

        using Control::find;

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override {
            Status result = Control::load(loader, xml);
            if (result != Status::OK)
                return result;

            SharedPointer<Control> control;
            AString layoutPath;
            auto layoutAttr = xml.FindAttribute("layout");
            if (layoutAttr) {
                layoutPath = layoutAttr->Value();
            } else if (loader.Theme) {
                size_t index = loader.Theme->Layouts.indexOfKey(&Type);
                if (index != loader.Theme->Layouts.Size)
                    layoutPath = loader.Theme->Layouts.getValue(index).Data;
            }

            [[unlikely]]
            if (layoutPath.Empty) {
                Logger::log(LogType::ERR0R, Status::INV_DATA, _T("Missing 'layout' attribute.\n"));
            } else {
                SharedPointer<Ghurund::UI::Layout> layout = loader.ResourceManager.load<Ghurund::UI::Layout>(convertText<char, wchar_t>(layoutPath), &Layout::FORMAT_XML, &result, LoadOption::DONT_CACHE);
                if (result == Status::OK) {
                    if (layout->Controls.Size == 1) {
                        control = layout->Controls[0];
                        control->addReference();
                    } else {
                        Logger::log(LogType::WARNING, Status::INV_DATA, _T("Layout '{}' has to contain exactly one child.\n"), layoutPath);
                    }
                } else {
                    Logger::log(LogType::WARNING, result, _T("Could not load layout '{}'.\n"), layoutPath);
                }
            }

            if (&control != nullptr) {
                Layout = std::unique_ptr<LayoutType>(ghnew LayoutType(control));
                return Layout->loadContent(loader, xml);
            } else {
                control = ghnew InvalidControl();
                Layout = std::unique_ptr<LayoutType>(ghnew LayoutType(control));
            }
            return Status::INV_PARAM;
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };

    template<typename Type, typename ItemType>
    concept BindingControl = Derived<Type, Control> && requires(Type control, ItemType & data) {
        control.bind(data);
    };

    template<typename Type, typename ItemType>
    concept BindingLayout = Derived<Type, LayoutBinding> && requires(Type layout, ItemType & data) {
        layout.bind(data);
    };

    template<class DataType, BindingLayout<DataType> LayoutType>
    class BindingWidget:public Widget<LayoutType> {
    private:
        DataType* data = nullptr;

    protected:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<BindingWidget>(NAMESPACE_NAME, GH_STRINGIFY(BindingWidget))
                .withModifiers(TypeModifier::ABSTRACT)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        virtual void onStateChanged() override {
            __super::onStateChanged();
            if (Widget<LayoutType>::Layout && data) {
                Widget<LayoutType>::Layout->bind(*data);
                Widget<LayoutType>::Layout->Root->invalidate();
            }
        }

    public:
        void bind(DataType& data) {
            this->data = &data;
            if (Widget<LayoutType>::Layout) {
                Widget<LayoutType>::Layout->bind(data);
                Widget<LayoutType>::Layout->Root->invalidate();
            }
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };
}

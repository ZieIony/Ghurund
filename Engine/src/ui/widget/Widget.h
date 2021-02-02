#pragma once

#include "Layout.h"
#include "core/string/TextConversionUtils.h"
#include "ui/LayoutLoader.h"
#include "ui/style/Style.h"

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

        public:
            Widget(LayoutType* layout = nullptr) {
                OnStateChanged.add(stateHandler);
                OnThemeChanged.add(themeHandler);
                Layout = layout;
            }

            ~Widget() = 0 {
                delete widgetLayout;
                widgetLayout = nullptr;
            }

            inline LayoutType* getLayout() const {
                return widgetLayout;
            }

            virtual void setLayout(LayoutType* layout) {
                if (widgetLayout) {
                    Child = nullptr;
                    delete widgetLayout;
                }
                widgetLayout = layout;
                if (widgetLayout) {
                    widgetLayout->init();
                    Child = widgetLayout->Root;
                }
            }

            __declspec(property(get = getLayout, put = setLayout)) LayoutType* Layout;

            virtual void onMeasure(float parentWidth, float parentHeight) override {
                if (widgetLayout)
                    widgetLayout->Root->PreferredSize = preferredSize;
                __super::onMeasure(parentWidth, parentHeight);
            }

            virtual Status load(LayoutLoader& loader, ResourceContext& context, const tinyxml2::XMLElement& xml) override {
                Status result = __super::load(loader, context, xml);
                if (result != Status::OK)
                    return result;
                auto layoutAttr = xml.FindAttribute("layout");
                if (layoutAttr) {
                    WString s = toWideChar(AString(layoutAttr->Value()));
                    uint32_t value = 0;
                    const wchar_t* themeProtocol = L"file://";
                    if (s.startsWith(themeProtocol)) {
                        WString layoutPath = s.substring(lengthOf(themeProtocol));
                        PointerList<Control*> controls = loader.load(context, layoutPath);
                        if (!controls.Empty)
                            Layout = ghnew LayoutType(controls[0]);
                    }
                }
                //auto styleAttr = xml.FindAttribute("style");
                //if (styleAttr)
                    //= loader.loadColor(styleAttr->Value());
                return Status::OK;
            }

            inline static const Ghurund::Type& TYPE = GET_TYPE();

            virtual const Ghurund::Type& getType() const override {
                return TYPE;
            }
    };
}

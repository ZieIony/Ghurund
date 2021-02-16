#pragma once

#include "Layout.h"
#include "core/string/TextConversionUtils.h"
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

            inline void setLayout(LayoutType* layout) {
                if (widgetLayout == layout)
                    return;
                if (widgetLayout) {
                    Child = nullptr;
                    delete widgetLayout;
                }
                widgetLayout = layout;
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
                if (layoutAttr) {
                    WString s = toWideChar(AString(layoutAttr->Value()));
                    uint32_t value = 0;
                    if (s.startsWith(LayoutLoader::FILE_PROTOCOL)) {
                        PointerList<Control*> controls;
                        Status result = loader.load(loader.getPath(s), controls);
                        if (result != Status::OK)
                            return result;
                        if (!controls.Empty) {
                            Layout = ghnew LayoutType(controls[0]);
                        } else {
                            return Status::INV_PARAM;
                        }
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

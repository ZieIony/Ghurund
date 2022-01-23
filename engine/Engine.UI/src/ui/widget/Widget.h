#pragma once

#include "core/Concepts.h"
#include "core/string/TextConversionUtils.h"
#include "core/reflection/TypeBuilder.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/style/Style.h"
#include "ui/style/Theme.h"
#include "ui/control/ControlContainer.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class Widget:public ControlContainer {
    private:
        AString layoutPath;

    protected:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<Widget>(NAMESPACE_NAME, GH_STRINGIFY(Widget))
                .withModifiers(TypeModifier::ABSTRACT)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        virtual void onThemeChanged() override {
            if (Context && !layoutPath.Empty) {
                SharedPointer<Control> control = Context->ResourceManager.load<Control>(convertText<char, wchar_t>(layoutPath), nullptr, LoadOption::DONT_CACHE);
                Child = control;
                bind();
            }
            if (!style) {
                size_t index = Theme->Styles.indexOfKey(StyleKey(Type.Name));
                if (index != Theme->Styles.Size)
                    Style = Theme->Styles.getValue(index);
            }
            __super::onThemeChanged();
        }

        virtual void bind() {}

        virtual void loadContent(Ghurund::UI::LayoutLoader& loader, const tinyxml2::XMLElement& xml) {}

    public:
        virtual void load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override {
            Control::load(loader, xml);

            SharedPointer<Control> control;
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
                Logger::log(LogType::WARNING, Status::INV_DATA, _T("Missing 'layout' attribute.\n"));
            } else {
                SharedPointer<Control> control = loader.ResourceManager.load<Control>(convertText<char, wchar_t>(layoutPath), nullptr, LoadOption::DONT_CACHE);
                Child = control;
                loadContent(loader, xml);
                bind();
            }
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };
}

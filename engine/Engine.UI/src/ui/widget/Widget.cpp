#include "ghuipch.h"
#include "Widget.h"

#include "core/string/TextConversionUtils.h"
#include "core/reflection/TypeBuilder.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/style/Style.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {

    const Ghurund::Core::Type& Widget::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Widget>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(Widget))
            .withModifiers(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Widget::onThemeChanged() {
        if (Context) {
            AString localPath = layoutPath;
            if (layoutPath.Empty) {
                size_t index = Theme->Layouts.indexOfKey(&Type);
                if (index != Theme->Layouts.Size)
                    localPath = Theme->Layouts.getValue(index).Data;
            }
            SharedPointer<Control> control(Context->ResourceManager.load<Control>(convertText<char, wchar_t>(localPath), nullptr, LoadOption::DONT_CACHE));
            Child = control.get();
            bind();
        }
        if (!style) {
            size_t index = Theme->Styles.indexOfKey(StyleKey(Type.Name));
            if (index != Theme->Styles.Size)
                Style = Theme->Styles.getValue(index);
        }
        __super::onThemeChanged();
    }

    void Widget::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        Control::load(loader, xml);

        SharedPointer<Control> control;
        auto layoutAttr = xml.FindAttribute("layout");
        if (layoutAttr) {
            layoutPath = layoutAttr->Value();
        }
    }
}

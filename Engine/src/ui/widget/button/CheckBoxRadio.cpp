#include "CheckBoxRadio.h"

#include "ui/control/ImageView.h"
#include "ui/widget/StateIndicator.h"

namespace Ghurund::UI {
    void CheckBoxRadioStyle::onStateChanged(Control& control) const {
        Ghurund::UI::Theme* theme = control.Theme;
        if (!theme)
            return;
        CheckBoxRadio& checkBoxRadio = (CheckBoxRadio&)control;
        CheckBoxLayout* layout = checkBoxRadio.Layout;
        if (!control.Enabled) {
            layout->Image->Image->Tint = theme->Colors[Theme::COLOR_DISABLED_ONBACKGROUND];
        } else if (layout->Selectable->Pressed) {
            if (layout->Selectable->Selected) {
                //imageView->Image->Tint = theme->getColorAccentDark();
                layout->Image->Image->Tint = theme->Colors[Theme::COLOR_ACCENT];
            } else {
                layout->Image->Image->Tint = theme->Colors[Theme::COLOR_PRIMARY_ONBACKGROUND];
            }
        } else if (layout->Selectable->Hovered || layout->Selectable->Focused) {
            if (layout->Selectable->Selected) {
                layout->Image->Image->Tint = theme->Colors[Theme::COLOR_ACCENT];
            } else {
                layout->Image->Image->Tint = theme->Colors[Theme::COLOR_SECONDARY_ONBACKGROUND];
            }
        } else {
            if (layout->Selectable->Selected) {
                layout->Image->Image->Tint = theme->Colors[Theme::COLOR_ACCENT];
            } else {
                layout->Image->Image->Tint = theme->Colors[Theme::COLOR_SECONDARY_ONBACKGROUND];
            }
        }
    }
    
    const Ghurund::Type& CheckBoxRadio::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<CheckBoxRadio>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(CheckBoxRadio))
            .withModifiers(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void CheckBoxRadio::onLayoutChanged() {
        __super::onLayoutChanged();
        if (Layout)
            Layout->Selectable->StateChanged.add(StateChanged);
    }

    Status CheckBoxRadio::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        Status result = __super::load(loader, xml);
        if (result != Status::OK)
            return result;
        auto checkedAttr = xml.FindAttribute("checked");
        if (checkedAttr)
            Checked = checkedAttr->BoolValue();
        return Status::OK;
    }
}

#include "SeparatorStyle.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    Separator::Separator(Style<Separator>* style) {
        colorView = ghnew ColorView();
        Child = colorView;
        style->apply(*this);
    }

    SeparatorStyle::SeparatorStyle(Theme& theme):Style<Separator>(theme) {}

    void SeparatorStyle::onStateChanged(Separator& separator) const {
        if (separator.Enabled) {
            separator.Color = theme.getColorControlNormal();
        } else {
            separator.Color = theme.getColorControlDisabled();
        }
    }

    void SeparatorStyle::apply(Separator& separator) const {
        __super::apply(separator);
        separator.Thickness = 1;
    }

    void HorizontalSeparatorStyle::apply(Separator& separator) const {
        __super::apply(separator);
        separator.PreferredSize.width = PreferredSize::Width::FILL;
        separator.PreferredSize.height = PreferredSize::Height::WRAP;
        separator.Padding.Vertical = 4;
        separator.Padding.Horizontal = 0;
    }

    void VerticalSeparatorStyle::apply(Separator& separator) const {
        __super::apply(separator);
        separator.PreferredSize.width = PreferredSize::Width::WRAP;
        separator.PreferredSize.height = PreferredSize::Height::FILL;
        separator.Padding.Vertical = 0;
        separator.Padding.Horizontal = 4;
    }
}
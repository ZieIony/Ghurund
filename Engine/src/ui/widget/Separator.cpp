#include "SeparatorStyle.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    Separator::Separator(Style2<Separator>* style) {
        colorView = ghnew ColorView();
        Child = colorView;
        style->apply(*this);
    }

    void SeparatorStyle::onStateChanged(Separator& separator) const {
        Theme* theme = separator.Theme;
        if (!theme)
            return;
        if (separator.Enabled) {
            separator.Color = theme->getColorControlNormal();
        } else {
            separator.Color = theme->getColorControlDisabled();
        }
    }

    void SeparatorStyle::onThemeChanged(Separator& separator) const {
        separator.Thickness = 1;
    }

    void HorizontalSeparatorStyle::onThemeChanged(Separator& separator) const {
        __super::onThemeChanged(separator);
        separator.PreferredSize.width = PreferredSize::Width::FILL;
        separator.PreferredSize.height = PreferredSize::Height::WRAP;
        separator.Padding.Vertical = 4;
        separator.Padding.Horizontal = 0;
    }

    void VerticalSeparatorStyle::onThemeChanged(Separator& separator) const {
        __super::onThemeChanged(separator);
        separator.PreferredSize.width = PreferredSize::Width::WRAP;
        separator.PreferredSize.height = PreferredSize::Height::FILL;
        separator.Padding.Vertical = 0;
        separator.Padding.Horizontal = 4;
    }
}
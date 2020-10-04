#include "Toolbar.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    Toolbar::Toolbar(Ghurund::UI::StyleWithLayout<Toolbar, ToolbarLayout>* style):Widget<Toolbar, ToolbarLayout>(style) {
        Layout.AdapterView->Items = ghnew ListItemSource<MenuItem*>(items);
    }

    ToolbarStyle::ToolbarStyle(Theme& theme): Ghurund::UI::StyleWithLayout<Toolbar, class ToolbarLayout>(theme), theme(theme) {}

    void ToolbarStyle::apply(Toolbar& toolbar) const {
        toolbar.PreferredSize.height = PreferredSize::Height::WRAP;
        ToolbarLayout& layout = (ToolbarLayout&)toolbar.Layout;
        layout.AdapterView->PreferredSize.height = PreferredSize::Height::WRAP;
        layout.AdapterView->LayoutManager = ghnew HorizontalLayoutManager<MenuItem*, Control>();
        layout.AdapterView->Adapters.add(ghnew ButtonToolbarAdapter(theme));
    }

    class ToolbarLayout* ToolbarStyle::makeLayout() const {
        return ghnew class ToolbarLayout();
    }

    ToolbarWithBackgroundStyle::ToolbarWithBackgroundStyle(Theme& theme):ToolbarStyle(theme) {}

    void ToolbarWithBackgroundStyle::apply(Toolbar& toolbar) const {
        toolbar.PreferredSize.height = PreferredSize::Height::WRAP;
        ToolbarWithBackgroundLayout& layout = (ToolbarWithBackgroundLayout&)toolbar.Layout;
        layout.BackgroundView->Color = theme.getColorBackground();
        layout.AdapterView->PreferredSize.height = PreferredSize::Height::WRAP;
        layout.AdapterView->LayoutManager = ghnew HorizontalLayoutManager<MenuItem*, Control>();
        layout.AdapterView->Adapters.add(ghnew ButtonToolbarAdapter(theme));
        layout.AdapterView->Adapters.add(ghnew SeparatorToolbarAdapter(theme));
    }

    void ToolbarWithBackgroundStyle::onStateChanged(Toolbar& toolbar) const {
        ToolbarWithBackgroundLayout& layout = ((ToolbarWithBackgroundLayout&)toolbar.Layout);
        layout.BackgroundView->Color = theme.getColorBackground();
    }

    ToolbarWithBackgroundLayout* ToolbarWithBackgroundStyle::makeLayout() const {
        return ghnew ToolbarWithBackgroundLayout();
    }
}

#include "MenuBar.h"

#include "ui/LayoutLoader.h"

namespace Ghurund::UI {
    MenuBar::MenuBar(Ghurund::ResourceContext& context, LayoutLoader& loader, MenuBarLayout* layout):Widget(layout) {
        auto provider = ghnew AdapterChildrenProvider<MenuItem*, Control>(*Layout->RecyclerView);
        provider->Adapters.add(ghnew ButtonMenuBarAdapter(context, loader));
        provider->Items = ghnew ListItemSource<MenuItem*>(items);
        Layout->RecyclerView->childrenProvider = provider;
        PreferredSize.height = PreferredSize::Height::WRAP;
    }
}

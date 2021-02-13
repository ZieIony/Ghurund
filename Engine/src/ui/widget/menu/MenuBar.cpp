#include "MenuBar.h"

#include "ui/LayoutLoader.h"

namespace Ghurund::UI {
    MenuBar::MenuBar(LayoutLoader& loader) {
        adapter = ghnew ButtonMenuBarAdapter(loader);
    }

    void MenuBar::onLayoutChanged(){
        auto provider = ghnew AdapterChildrenProvider<MenuItem*, Control>(*Layout->RecyclerView);
        provider->Adapters.add(adapter);
        provider->Items = ghnew ListItemSource<MenuItem*>(items);
        Layout->RecyclerView->childrenProvider = provider;
        PreferredSize.height = PreferredSize::Height::WRAP;
    }
}

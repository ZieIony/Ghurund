#include "ghuipch.h"
#include "MenuBar.h"

#include "MenuBarItemAdapter.h"
#include "core/reflection/TypeBuilder.h"
#include "ui/layout/HorizontalLayoutManager.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& MenuBar::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<MenuBar>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
    
    inline void MenuBar::updateProperties() {
        if (adapterLayout) {
            adapterLayout->ItemAdapter = *itemAdapter;
        }
    }

    void MenuBar::onLayoutChanged() {
        __super::onLayoutChanged();
        Control* layoutControl = layout.get();
        if (layoutControl) {
            setPointer(adapterLayout, (Ghurund::UI::AdapterLayout*)layoutControl->find("adapterLayout"));
            updateProperties();
            if (adapterLayout) {
                adapterLayout->LayoutManager = std::make_unique<HorizontalLayoutManager>();
            }
        }
    }
}
